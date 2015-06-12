#include "ElectronEnergySource.h"

template<>
InputParameters validParams<ElectronEnergySource>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredCoupledVar("Ars", "The excited state argon density in moles");
  params.addRequiredCoupledVar("em", "The electron density, most likely in #/m^3");

  return params;
}

ElectronEnergySource::ElectronEnergySource(const std::string & name, InputParameters parameters) :
  Kernel(name, parameters),

  // Input Parameters

  // Material Properties
  _Ar(getMaterialProperty<Real>("Ar")),
  _el_energy_gain_excitation(getMaterialProperty<Real>("el_energy_gain_excitation")),
  _el_energy_gain_deexcitation(getMaterialProperty<Real>("el_energy_gain_deexcitation")),
  _el_energy_gain_ionization(getMaterialProperty<Real>("el_energy_gain_ionization")),
  _el_energy_gain_meta_ionization(getMaterialProperty<Real>("el_energy_gain_meta_ionization")),

  // Coupled Variables
  _Ars(coupledValue("Ars")),
  _Ars_id(coupled("Ars")),
  _em(coupledValue("em")),
  _em_id(coupled("em")),

  // Unique to kernel

  _k2(0.0),
  _k3(0.0),
  _k4(0.0),
  _k5(0.0)
  
{
}

ElectronEnergySource::~ElectronEnergySource()
{}

Real
ElectronEnergySource::computeQpResidual()
{
  // Clean expression for reading:
  // return -_test[_i][_qp]*(_k2*_em[_qp]*_Ar[_qp]*_el_energy_gain_excitation[_qp]+_k3*_em[_qp]*_Ars[_qp]*_el_energy_gain_deexcitation[_qp]+_k4*_em[_qp]*_Ar[_qp]*_el_energy_gain_ionization[_qp]+_k5*_em[_qp]*_Ars[_qp]*_el_energy_gain_meta_ionization[_qp]);

return -_test[_i][_qp]*(_k2*std::max(_em[_qp],0.0)*_Ar[_qp]*_el_energy_gain_excitation[_qp]+_k3*std::max(_em[_qp],0.0)*std::max(_Ars[_qp],0.0)*_el_energy_gain_deexcitation[_qp]+_k4*std::max(_em[_qp],0.0)*_Ar[_qp]*_el_energy_gain_ionization[_qp]+_k5*std::max(_em[_qp],0.0)*std::max(_Ars[_qp],0.0)*_el_energy_gain_meta_ionization[_qp]);
}

Real
ElectronEnergySource::computeQpJacobian()
{
  return 0.0;
}

Real
ElectronEnergySource::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _Ars_id)
    {
      return -_test[_i][_qp]*(_k3*_em[_qp]*_phi[_j][_qp]*_el_energy_gain_deexcitation[_qp]+_k5*_em[_qp]*_phi[_j][_qp]*_el_energy_gain_meta_ionization[_qp]);
    }
  else if (jvar == _em_id)
    {
      return -_test[_i][_qp]*(_k2*_phi[_j][_qp]*_Ar[_qp]*_el_energy_gain_excitation[_qp]+_k3*_phi[_j][_qp]*_Ars[_qp]*_el_energy_gain_deexcitation[_qp]+_k4*_phi[_j][_qp]*_Ar[_qp]*_el_energy_gain_ionization[_qp]+_k5*_phi[_j][_qp]*_Ars[_qp]*_el_energy_gain_meta_ionization[_qp]);
    }
  else
    {
      return 0.0;
    }
}
