#include "ArpSource.h"

template<>
InputParameters validParams<ArpSource>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredCoupledVar("em", "The electron density");
  params.addRequiredCoupledVar("Ars", "The excited state argon density in moles");
  params.addRequiredCoupledVar("mean_electron_energy", "The mean electron energy");

  return params;
}

ArpSource::ArpSource(const std::string & name, InputParameters parameters) :
  Kernel(name, parameters),

  // Input Parameters

  // Material Properties
  _Ar(getMaterialProperty<Real>("Ar")),

  // Coupled Variables
  _em(coupledValue("em")),
  _em_id(coupled("em")),
  _Ars(coupledValue("Ars")),
  _Ars_id(coupled("Ars")),
  _mean_electron_energy(coupledValue("mean_electron_energy")),
  _mean_electron_energy_id(coupled("mean_electron_energy")),

  // Unique to kernel

  _T_e(0.0),
  _k_4(0.0),
  _k_5(0.0),
  _dk4_dTe(0.0),
  _dk5_dTe(0.0),
  _dTe_d_em(0.0),
  _dTe_d_mean_el_energy(0.0)
{
}

ArpSource::~ArpSource()
{}

Real
ArpSource::computeQpResidual()
{
  // Clean expression for reading:
  //   return -_test[_i][_qp]*(_k_4*_em[_qp]*_Ar[_qp]+_k_5*_em[_qp]*_Ars[_qp]);
  _T_e = _mean_electron_energy[_qp]*2.0/(3.0*_em[_qp]);
  _k_4 = 2.34e-14*std::pow(_T_e,0.59)*std::exp(-17.44/(_T_e+1e-6));
  _k_5 = 6.8e-15*std::pow(_T_e,0.67)*std::exp(-4.20/(_T_e+1e-6));

  return -_test[_i][_qp]*(_k_4*std::max(_em[_qp],0.0)*std::max(_Ar[_qp],0.0)+_k_5*std::max(_em[_qp],0.0)*std::max(_Ars[_qp],0.0));
}

Real
ArpSource::computeQpJacobian()
{
  return 0.0;
}

Real
ArpSource::computeQpOffDiagJacobian(unsigned int jvar)
{
  _T_e = _mean_electron_energy[_qp]*2.0/(3.0*_em[_qp]);
  _k_4 = 2.34e-14*std::pow(_T_e,0.59)*std::exp(-17.44/(_T_e+1e-6));
  _k_5 = 6.8e-15*std::pow(_T_e,0.67)*std::exp(-4.20/(_T_e+1e-6));
  _dk4_dTe = 4.08096e-13*std::pow(_T_e,-1.41)*std::exp(-17.44/(_T_e+1e-6))+1.3806e-14*std::pow(_T_e,-0.41)*std::exp(-17.44/(_T_e+1e-6));
  _dk5_dTe = 2.856e-14*std::pow(_T_e,-1.33)*std::exp(-4.2/(_T_e+1e-6))+4.556e-15*std::pow(_T_e,-0.33)*std::exp(-4.2/(_T_e+1e-6));
  _dTe_d_em = -2.0*_mean_electron_energy[_qp]/(3.0*std::pow(_em[_qp],2));
  _dTe_d_mean_el_energy = 2.0/(3.0*_em[_qp]);  

  if (jvar == _em_id)
    {
      return -_test[_i][_qp]*(_k_4*_phi[_j][_qp]*_Ar[_qp]+_em[_qp]*_Ar[_qp]*_dk4_dTe*_dTe_d_em*_phi[_j][_qp]+_k_5*_phi[_j][_qp]*_Ars[_qp]+_em[_qp]*_Ars[_qp]*_dk5_dTe*_dTe_d_em*_phi[_j][_qp]);
    }
  else if (jvar == _Ars_id)
    {
      return -_test[_i][_qp]*(_k_5*_em[_qp]*_phi[_j][_qp]);
    }
  else if (jvar == _mean_electron_energy_id)
    {
      return -_test[_i][_qp]*(_em[_qp]*_Ar[_qp]*_dk4_dTe*_dTe_d_mean_el_energy*_phi[_j][_qp]+_em[_qp]*_Ars[_qp]*_dk5_dTe*_dTe_d_mean_el_energy*_phi[_j][_qp]);
    }
  else
    {
      return 0.0;
    }
}
