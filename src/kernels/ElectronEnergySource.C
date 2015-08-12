#include "ElectronEnergySource.h"

template<>
InputParameters validParams<ElectronEnergySource>()
{
  InputParameters params = validParams<Kernel>();

  params.addCoupledVar("Ars", "The excited state argon density in moles");
  params.addRequiredCoupledVar("em", "The electron density, most likely in #/m^3");

  return params;
}

ElectronEnergySource::ElectronEnergySource(const InputParameters & parameters) :
  Kernel(parameters),

  // Input Parameters

  // Material Properties
  _Ar(getMaterialProperty<Real>("Ar")),
  _el_energy_gain_excitation(getMaterialProperty<Real>("el_energy_gain_excitation")),
  _el_energy_gain_deexcitation(getMaterialProperty<Real>("el_energy_gain_deexcitation")),
  _el_energy_gain_ionization(getMaterialProperty<Real>("el_energy_gain_ionization")),
  _el_energy_gain_meta_ionization(getMaterialProperty<Real>("el_energy_gain_meta_ionization")),
  _m_em(getMaterialProperty<Real>("m_em")),
  _mAr(getMaterialProperty<Real>("mAr")),

  // Coupled Variables
  _Ars(isCoupled("Ars") ? coupledValue("Ars") : _zero),
  _Ars_id(isCoupled("Ars") ? coupled("Ars") : 0),
  _em(coupledValue("em")),
  _em_id(coupled("em")),

  // Unique to kernel

  _T_e(0.0),
  _k1(0.0),
  _k2(0.0),
  _k3(0.0),
  _k4(0.0),
  _k5(0.0),
  _dk1_dTe(0.0),
  _dk2_dTe(0.0),
  _dk3_dTe(0.0),
  _dk4_dTe(0.0),
  _dk5_dTe(0.0)
{
  ArsCoupling = isCoupled("Ars");
}

ElectronEnergySource::~ElectronEnergySource()
{}

Real
ElectronEnergySource::computeQpResidual()
{
  _T_e = std::max(_u[_qp],0.0);
  //  _k1 = 2.336e-14*std::pow(std::max(_T_e,1e-6),1.609)*std::exp(0.0618*std::pow(std::log(std::max(_T_e,1e-6)),2)-0.1171*std::pow(std::log(std::max(_T_e,1e-6)),3));
  //  _k1 = 0.0;
  //  _k4 = 2.34e-14*std::pow(std::max(_T_e,1e-6),0.59)*std::exp(-17.44/(_T_e+1e-6));
  _k1 = 1e-13;
  _k4 = 5e-14*std::exp(-15.76/(std::max(_T_e,1e-16)));

  if (ArsCoupling)
    {
      _k2 = 5.0e-15*std::pow(std::max(_T_e,1e-6),0.74)*std::exp(-11.56/(_T_e+1e-6)); // Electron impact excitation of ground state argon to create Ars (Ar(4s) in Liebermans text)
      _k3 = 4.3e-16*std::pow(std::max(_T_e,1e-6),0.74); // Electron impact dexcitation of Ars (Ar(4s) in Liebermans text)
      _k5 = 6.8e-15*std::pow(std::max(_T_e,1e-6),0.67)*std::exp(-4.20/(_T_e+1e-6));
    }
  else
    {
      _k2 = 0.0;
      _k3 = 0.0;
      _k5 = 0.0;
    }

  return -_test[_i][_qp]*(_k2*std::max(std::max(_em[_qp],1.0),0.0)*_Ar[_qp]*_el_energy_gain_excitation[_qp]+_k3*std::max(std::max(_em[_qp],1.0),0.0)*std::max(_Ars[_qp],0.0)*_el_energy_gain_deexcitation[_qp]+_k4*std::max(std::max(_em[_qp],1.0),0.0)*_Ar[_qp]*_el_energy_gain_ionization[_qp]+_k5*std::max(std::max(_em[_qp],1.0),0.0)*std::max(_Ars[_qp],0.0)*_el_energy_gain_meta_ionization[_qp]-_k1*std::max(std::max(_em[_qp],1.0),0.0)*_Ar[_qp]*3.0*_m_em[_qp]/_mAr[_qp]*std::max(_u[_qp],0.0));
}

Real
ElectronEnergySource::computeQpJacobian()
{
  _T_e = std::max(_u[_qp],0.0);
  /*  _k1 = 2.336e-14*std::pow(std::max(_T_e,1e-6),1.609)*std::exp(0.0618*std::pow(std::log(std::max(_T_e,1e-6)),2)-0.1171*std::pow(std::log(std::max(_T_e,1e-6)),3));
  //  _k1 = 0.0;
  _k4 = 2.34e-14*std::pow(std::max(_T_e,1e-6),0.59)*std::exp(-17.44/(_T_e+1e-6));
  _dk1_dTe = 3.758624e-14*std::pow(std::max(_T_e,1e-6),0.609)*exp(-0.1171*std::pow(std::log(std::max(_T_e,1e-6)),3) + 0.0618*std::pow(std::log(std::max(_T_e,1e-6)),2)) + 2.336e-14*std::pow(std::max(_T_e,1e-6),1.609)*(-0.3513*std::pow(std::log(std::max(_T_e,1e-6)),2)/std::max(_T_e,1e-16) + 0.1236*std::log(std::max(_T_e,1e-6))/std::max(_T_e,1e-16))*exp(-0.1171*std::pow(std::log(std::max(_T_e,1e-6)),3) + 0.0618*std::pow(std::log(std::max(_T_e,1e-6)),2));
  _dk4_dTe = 4.08096e-13*std::pow(std::max(_T_e,1e-6),-1.41)*std::exp(-17.44/(_T_e+1e-6))+1.3806e-14*std::pow(std::max(_T_e,1e-6),-0.41)*std::exp(-17.44/(_T_e+1e-6));*/
  
  _k1 = 1e-13;
  _k4 = 5e-14*std::exp(-15.76/(std::max(_T_e,1e-16)));
  _dk1_dTe = 0.0;
  _dk4_dTe = 7.88e-13*std::exp(-15.76/std::max(_T_e,1e-16))/std::max(std::pow(_T_e,2),1e-16);

  if (ArsCoupling)
    {
      _k2 = 5.0e-15*std::pow(std::max(_T_e,1e-6),0.74)*std::exp(-11.56/(_T_e+1e-6)); // Electron impact excitation of ground state argon to create Ars (Ar(4s) in Liebermans text)
      _k3 = 4.3e-16*std::pow(std::max(_T_e,1e-6),0.74); // Electron impact dexcitation of Ars (Ar(4s) in Liebermans text)
      _k5 = 6.8e-15*std::pow(std::max(_T_e,1e-6),0.67)*std::exp(-4.20/(_T_e+1e-6));
      _dk2_dTe = 5.78e-14*std::pow(std::max(_T_e,1e-6),-1.26)*std::exp(-11.56/(_T_e+1e-6))+3.7e-15*std::pow(std::max(_T_e,1e-6),-0.26)*std::exp(-11.56/(_T_e+1e-6));
      _dk3_dTe = 3.182e-16*std::pow(std::max(_T_e,1e-6),-0.26);
      _dk5_dTe = 2.856e-14*std::pow(std::max(_T_e,1e-6),-1.33)*std::exp(-4.2/(_T_e+1e-6))+4.556e-15*std::pow(std::max(_T_e,1e-6),-0.33)*std::exp(-4.2/(_T_e+1e-6));
    }
  else
    {
      _k2 = 0.0;
      _k3 = 0.0;
      _k5 = 0.0;
      _dk2_dTe = 0.0;
      _dk3_dTe = 0.0;
      _dk5_dTe = 0.0;
    }

  return -_test[_i][_qp]*(_dk2_dTe*_phi[_j][_qp]*std::max(_em[_qp],1.0)*_Ar[_qp]*_el_energy_gain_excitation[_qp]+_dk3_dTe*_phi[_j][_qp]*std::max(_em[_qp],1.0)*_Ars[_qp]*_el_energy_gain_deexcitation[_qp]+_dk4_dTe*_phi[_j][_qp]*std::max(_em[_qp],1.0)*_Ar[_qp]*_el_energy_gain_ionization[_qp]+_dk5_dTe*_phi[_j][_qp]*std::max(_em[_qp],1.0)*_Ars[_qp]*_el_energy_gain_meta_ionization[_qp]-_dk1_dTe*_phi[_j][_qp]*std::max(_em[_qp],1.0)*_Ar[_qp]*3.0*_m_em[_qp]/_mAr[_qp]*std::max(_u[_qp],0.0)-_k1*std::max(_em[_qp],1.0)*_Ar[_qp]*3.0*_m_em[_qp]/_mAr[_qp]*_phi[_j][_qp]);
}

Real
ElectronEnergySource::computeQpOffDiagJacobian(unsigned int jvar)
{
  _T_e = std::max(_u[_qp],0.0);
  /*  _k1 = 2.336e-14*std::pow(std::max(_T_e,1e-6),1.609)*std::exp(0.0618*std::pow(std::log(std::max(_T_e,1e-6)),2)-0.1171*std::pow(std::log(std::max(_T_e,1e-6)),3));
  //  _k1 = 0.0;
  _k4 = 2.34e-14*std::pow(std::max(_T_e,1e-6),0.59)*std::exp(-17.44/(_T_e+1e-6));
  _dk1_dTe = 3.758624e-14*std::pow(std::max(_T_e,1e-6),0.609)*exp(-0.1171*std::pow(std::log(std::max(_T_e,1e-6)),3) + 0.0618*std::pow(std::log(std::max(_T_e,1e-6)),2)) + 2.336e-14*std::pow(std::max(_T_e,1e-6),1.609)*(-0.3513*std::pow(std::log(std::max(_T_e,1e-6)),2)/std::max(_T_e,1e-16) + 0.1236*std::log(std::max(_T_e,1e-6))/std::max(_T_e,1e-16))*exp(-0.1171*std::pow(std::log(std::max(_T_e,1e-6)),3) + 0.0618*std::pow(std::log(std::max(_T_e,1e-6)),2));
  _dk4_dTe = 4.08096e-13*std::pow(std::max(_T_e,1e-6),-1.41)*std::exp(-17.44/(_T_e+1e-6))+1.3806e-14*std::pow(std::max(_T_e,1e-6),-0.41)*std::exp(-17.44/(_T_e+1e-6));*/

  _k1 = 1e-13;
  _k4 = 5e-14*std::exp(-15.76/(std::max(_T_e,1e-16)));
  _dk1_dTe = 0.0;
  _dk4_dTe = 7.88e-13*std::exp(-15.76/std::max(_T_e,1e-16))/std::max(std::pow(_T_e,2),1e-16);

  if (ArsCoupling)
    {
      _k2 = 5.0e-15*std::pow(std::max(_T_e,1e-6),0.74)*std::exp(-11.56/(_T_e+1e-6)); // Electron impact excitation of ground state argon to create Ars (Ar(4s) in Liebermans text)
      _k3 = 4.3e-16*std::pow(std::max(_T_e,1e-6),0.74); // Electron impact dexcitation of Ars (Ar(4s) in Liebermans text)
      _k5 = 6.8e-15*std::pow(std::max(_T_e,1e-6),0.67)*std::exp(-4.20/(_T_e+1e-6));
      _dk2_dTe = 5.78e-14*std::pow(std::max(_T_e,1e-6),-1.26)*std::exp(-11.56/(_T_e+1e-6))+3.7e-15*std::pow(std::max(_T_e,1e-6),-0.26)*std::exp(-11.56/(_T_e+1e-6));
      _dk3_dTe = 3.182e-16*std::pow(std::max(_T_e,1e-6),-0.26);
      _dk5_dTe = 2.856e-14*std::pow(std::max(_T_e,1e-6),-1.33)*std::exp(-4.2/(_T_e+1e-6))+4.556e-15*std::pow(std::max(_T_e,1e-6),-0.33)*std::exp(-4.2/(_T_e+1e-6));
    }
  else
    {
      _k2 = 0.0;
      _k3 = 0.0;
      _k5 = 0.0;
      _dk2_dTe = 0.0;
      _dk3_dTe = 0.0;
      _dk5_dTe = 0.0;
    }

  if (ArsCoupling && jvar == _Ars_id)
    {
      return -_test[_i][_qp]*(_k3*std::max(_em[_qp],1.0)*_phi[_j][_qp]*_el_energy_gain_deexcitation[_qp]+_k5*std::max(_em[_qp],1.0)*_phi[_j][_qp]*_el_energy_gain_meta_ionization[_qp]);
    }
  else if (jvar == _em_id)
    {
      return -_test[_i][_qp]*(_k2*_phi[_j][_qp]*_Ar[_qp]*_el_energy_gain_excitation[_qp]+_k3*_phi[_j][_qp]*_Ars[_qp]*_el_energy_gain_deexcitation[_qp]+_k4*_phi[_j][_qp]*_Ar[_qp]*_el_energy_gain_ionization[_qp]+_k5*_phi[_j][_qp]*_Ars[_qp]*_el_energy_gain_meta_ionization[_qp]-_k1*_Ar[_qp]*3.0*_m_em[_qp]/_mAr[_qp]*std::max(_u[_qp],0.0)*_phi[_j][_qp]);
    }
  else
    {
      return 0.0;
    }
}
