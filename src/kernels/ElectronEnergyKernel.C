#include "ElectronEnergyKernel.h"

template<>
InputParameters validParams<ElectronEnergyKernel>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredCoupledVar("em", "The electron density");
  params.addRequiredCoupledVar("potential","The electric potential");

  return params;
}

ElectronEnergyKernel::ElectronEnergyKernel(const std::string & name, InputParameters parameters) :
  Kernel(name, parameters),

  _em(coupledValue("em")),
  _grad_em(coupledGradient("em")),
  _grad_potential(coupledGradient("potential")),

  // Material properties

  _muel(getMaterialProperty<Real>("muel")),
  _muem(getMaterialProperty<Real>("muem")),
  _diffem(getMaterialProperty<Real>("diffem")),
  _diffel(getMaterialProperty<Real>("diffel")),
  _Ar(getMaterialProperty<Real>("Ar")),
  _mem(getMaterialProperty<Real>("mem")),
  _mip(getMaterialProperty<Real>("mip")),
  _Eiz(getMaterialProperty<Real>("Eiz")),
  _rate_coeff_ion(getMaterialProperty<Real>("rate_coeff_ion")),
  _rate_coeff_elastic(getMaterialProperty<Real>("rate_coeff_elastic")),

// Kernel members

  _alpha(0.0),
  _Pe(0.0),
  _vd_mag(0.0),
  _delta(0.0)
{}

ElectronEnergyKernel::~ElectronEnergyKernel()
{}

Real
ElectronEnergyKernel::computeQpResidual()
{
  _vd_mag = std::abs(_muel[_qp]*_grad_potential[_qp].size());
  _Pe = _vd_mag*_current_elem->hmax()/_diffel[_qp];
  _alpha = std::min(1.0,_Pe/6.0);
  _delta = _alpha*_vd_mag*_current_elem->hmax()/2.0;
  
  return -_grad_test[_i][_qp]*std::exp(_u[_qp])*(-_muel[_qp]*-_grad_potential[_qp] // Advective motion
						 -_diffel[_qp]*_grad_u[_qp]) // Diffusive motion
         +_test[_i][_qp]*-_grad_potential[_qp]*(-_muem[_qp]*std::exp(_em[_qp])*-_grad_potential[_qp] // Joule Heating
						 -_diffem[_qp]*std::exp(_em[_qp])*_grad_em[_qp]) // Joule Heating
	 -_test[_i][_qp]*_rate_coeff_ion[_qp]*std::exp(-_Eiz[_qp]/(2.0/3*std::exp(_u[_qp]-_em[_qp])))*_Ar[_qp]*std::exp(_em[_qp])*-_Eiz[_qp] // Energy loss from ionization. Reaction rate formulation
         -_test[_i][_qp]*-_rate_coeff_elastic[_qp]*_Ar[_qp]*std::exp(_em[_qp])*3.0*_mem[_qp]/_mip[_qp]*2.0/3*std::exp(_u[_qp]-_em[_qp]) // Energy loss from elastic collisions
	 -_grad_test[_i][_qp]*(-_delta*std::exp(_u[_qp])*_grad_u[_qp]); // Diffusion stabilization
}

Real
ElectronEnergyKernel::computeQpJacobian()
{
  _vd_mag = std::abs(_muel[_qp]*_grad_potential[_qp].size());
  _Pe = _vd_mag*_current_elem->hmax()/_diffel[_qp];
  _alpha = std::min(1.0,_Pe/6.0);
  _delta = _alpha*_vd_mag*_current_elem->hmax()/2.0;
  
  return -_grad_test[_i][_qp]*(-_muel[_qp]*-_grad_potential[_qp]*std::exp(_u[_qp])*_phi[_j][_qp] // Advective motion
						 -_diffel[_qp]*_grad_phi[_j][_qp]*std::exp(_u[_qp])-_diffel[_qp]*_grad_u[_qp]*std::exp(_u[_qp])*_phi[_j][_qp]) // Diffusive motion
	 -_test[_i][_qp]*_rate_coeff_ion[_qp]*3.0/2*_Eiz[_qp]*std::exp(-_Eiz[_qp]/(2.0/3*std::exp(_u[_qp]-_em[_qp])))*std::exp(_em[_qp]-_u[_qp])*_phi[_j][_qp]*_Ar[_qp]*std::exp(_em[_qp])*-_Eiz[_qp] // Energy loss from ionization
         -_test[_i][_qp]*-_rate_coeff_elastic[_qp]*_Ar[_qp]*std::exp(_em[_qp])*3.0*_mem[_qp]/_mip[_qp]*2.0/3*std::exp(_u[_qp]-_em[_qp])*_phi[_j][_qp] // Energy loss from elastic collisions
	 -_grad_test[_i][_qp]*(-_delta*(std::exp(_u[_qp])*_grad_phi[_j][_qp]+std::exp(_u[_qp])*_phi[_j][_qp]*_grad_u[_qp])); // Diffusion stabilization
}

