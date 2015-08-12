#include "ElectronEnergyKernel.h"

template<>
InputParameters validParams<ElectronEnergyKernel>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredCoupledVar("em", "The electron density");
  params.addRequiredCoupledVar("potential","The electric potential");

  return params;
}

ElectronEnergyKernel::ElectronEnergyKernel(const InputParameters & parameters) :
  Kernel(parameters),

  _em(coupledValue("em")),
  _grad_em(coupledGradient("em")),
  _grad_potential(coupledGradient("potential")),

  _muel(0.16*5.0/3),
  _muem(0.16),
  _diff(.05),
  _diffel(.05*5.0/3),
  _Ar(1.01e5/(300*1.38e-23)),
  _mem(9.11e-31),
  _mAr(40*1.66e-27),
  _k4_const(5e-14),
  _k1_const(1e-13),
  _Eiz(12.78),
  _alpha(0.0),
  _Pe(0.0),
  _vd_mag(0.0),
  _delta(0.0),
  _a0(2.36e11), // Parameters for computing Townsend coeff
  _b0(-3.11), // Parameters for computing Townsend coeff
  _c0(6.63e1) // Parameters for computing Townsend coeff
{}

ElectronEnergyKernel::~ElectronEnergyKernel()
{}

Real
ElectronEnergyKernel::computeQpResidual()
{
  _vd_mag = std::abs(_muel*_grad_potential[_qp].size());
  _Pe = _vd_mag*_current_elem->hmax()/_diffel;
  _alpha = std::min(1.0,_Pe/6.0);
  _delta = _alpha*_vd_mag*_current_elem->hmax()/2.0;
  
  return -_grad_test[_i][_qp]*std::exp(_u[_qp])*(-_muel*-_grad_potential[_qp] // Advective motion
						 -_diffel*_grad_u[_qp]) // Diffusive motion
         +_test[_i][_qp]*-_grad_potential[_qp]*(-_muem*std::exp(_em[_qp])*-_grad_potential[_qp] // Joule Heating
						 -_diff*std::exp(_em[_qp])*_grad_em[_qp]) // Joule Heating
	 // -_test[_i][_qp]*(_k4_const*std::exp(-_Eiz/(2.0/3*std::exp(_u[_qp]-_em[_qp])))*_Ar*std::exp(_em[_qp])*-_Eiz // Energy loss from ionization. Reaction rate formulation
    -_test[_i][_qp]*_a0*std::pow(std::exp(_u[_qp]-_em[_qp]),_b0)*std::exp(-_c0/std::exp(_u[_qp]-_em[_qp]))*std::exp(_em[_qp])*(-_muem*-_grad_potential[_qp]-_diff*_grad_em[_qp]).size()*-_Eiz // Reaction. Townsend coefficient formulation
    -_test[_i][_qp]*-_k1_const*_Ar*std::exp(_em[_qp])*3.0*_mem/_mAr*2.0/3*std::exp(_u[_qp]-_em[_qp]) // Energy loss from elastic collisions
	 -_grad_test[_i][_qp]*(-_delta*std::exp(_u[_qp])*_grad_u[_qp]); // Diffusion stabilization
}

Real
ElectronEnergyKernel::computeQpJacobian()
{
  _vd_mag = std::abs(_muel*_grad_potential[_qp].size());
  _Pe = _vd_mag*_current_elem->hmax()/_diffel;
  _alpha = std::min(1.0,_Pe/6.0);
  _delta = _alpha*_vd_mag*_current_elem->hmax()/2.0;
  
  return -_grad_test[_i][_qp]*(-_muel*-_grad_potential[_qp]*std::exp(_u[_qp])*_phi[_j][_qp] // Advective motion
						 -_diffel*_grad_phi[_j][_qp]*std::exp(_u[_qp])-_diffel*_grad_u[_qp]*std::exp(_u[_qp])*_phi[_j][_qp]) // Diffusive motion
	 // -_test[_i][_qp]*(_k4_const*3.0/2*_Eiz*std::exp(-_Eiz/(2.0/3*std::exp(_u[_qp]-_em[_qp])))*std::exp(_em[_qp]-_u[_qp])*_phi[_j][_qp]*_Ar*std::exp(_em[_qp])*-_Eiz // Energy loss from ionization
    -_test[_i][_qp]*(_a0*(_b0 + _c0*std::exp(_em[_qp]-_u[_qp]))*std::exp(-_c0*std::exp(_em[_qp]-_u[_qp]))*std::pow(std::exp(-_em[_qp]+_u[_qp]),_b0))*_phi[_j][_qp]*(-_muem*-_grad_potential[_qp]*std::exp(_em[_qp])-_diff*std::exp(_em[_qp])*_grad_em[_qp]).size()
    -_test[_i][_qp]*-_k1_const*_Ar*std::exp(_em[_qp])*3.0*_mem/_mAr*2.0/3*std::exp(_u[_qp]-_em[_qp])*_phi[_j][_qp] // Energy loss from elastic collisions
	 -_grad_test[_i][_qp]*(-_delta*(std::exp(_u[_qp])*_grad_phi[_j][_qp]+std::exp(_u[_qp])*_phi[_j][_qp]*_grad_u[_qp])); // Diffusion stabilization
}

