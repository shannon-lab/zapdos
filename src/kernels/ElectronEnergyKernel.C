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

  _muel(380.0/1e4*5/3),
  _muem(380.0/1e4),
  _Ar(1.01e5/(300*1.38e-23)),
  _mem(9.11e-31),
  _mAr(40*1.66e-27),
  _k4_const(5e-14),
  _k1_const(1e-13)
{}

ElectronEnergyKernel::~ElectronEnergyKernel()
{}

Real
ElectronEnergyKernel::computeQpResidual()
{
  return -_grad_test[_i][_qp]*std::exp(_u[_qp])*(-_muel*-_grad_potential[_qp] // Advective motion
						 -_muel*2/3*std::exp(_u[_qp]-_em[_qp])*_grad_u[_qp]); // Diffusive motion
         +_test[_i][_qp]*-_grad_potential[_qp]*(-_muem*std::exp(_em[_qp])*-_grad_potential[_qp] // Joule Heating
						 -_muem*2/3*std::exp(_u[_qp]-_em[_qp])*std::exp(_em[_qp]*_grad_em[_qp]) // Joule Heating
	 -_test[_i][_qp]*(_k4_const*std::exp(-15.76/(2.0/3*std::exp(_u[_qp]-_em[_qp])))*_Ar*std::exp(_em[_qp])*-15.76 // Energy loss from ionization
			  -_k1_const*_Ar*std::exp(_em[_qp])*3.0*_mem/_mAr*2/3*std::exp(_u[_qp]-_em[_qp])); // Energy loss from elastic collisions
}

Real
ElectronEnergyKernel::computeQpJacobian()
{
  return -_grad_test[_i][_qp]*(std::exp(_u[_qp])*_phi[_j][_qp]*(-_muel*-_grad_potential[_qp]
								-_muel*2/3*std::exp(_u[_qp]-_em[_qp])*_grad_u[_qp])
			       +std::exp(_u[_qp])*-_muel*2/3*(_grad_phi[_j][_qp]*std::exp(_u[_qp]-_em[_qp])
							      +_grad_u[_qp]*std::exp(_u[_qp]-_em[_qp])*_phi[_j][_qp]));
         // + _test[_i][_qp]*-_grad_potential[_qp]*(-_muem*_phi[_j][_qp]*_grad_em[_qp]) // Joule Heating
         // -_test[_i][_qp]*(_k4_const*15.76*std::exp(-15.76/std::max(_u[_qp],1e-16))/std::max(std::pow(_u[_qp],2),1e-16)*_phi[_j][_qp]*_Ar*_em[_qp]*-15.76 // Energy loss from ionization
			  // -_k1_const*_Ar*_em[_qp]*3.0*_mem/_mAr*_phi[_j][_qp]); // Energy loss from elastic collisions
}

