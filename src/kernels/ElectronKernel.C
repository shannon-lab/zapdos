#include "ElectronKernel.h"

template<>
InputParameters validParams<ElectronKernel>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredCoupledVar("mean_en", "The electron temperature");
  params.addRequiredCoupledVar("potential","The electric potential");

  return params;
}

ElectronKernel::ElectronKernel(const std::string & name, InputParameters parameters) :
  Kernel(name, parameters),

  _mean_en(coupledValue("mean_en")),
  _grad_potential(coupledGradient("potential")),

  _muem(380.0/1e4),
  _k4_const(5e-14),
  _Ar(1.01e5/(300*1.38e-23))
{}

ElectronKernel::~ElectronKernel()
{}

Real
ElectronKernel::computeQpResidual()
{
  // Trying a logarithmic formulation
  return -_grad_test[_i][_qp]*std::exp(_u[_qp])*(-_muem*-_grad_potential[_qp]-_muem*2/3*std::exp(_mean_en[_qp]-_u[_qp])*_grad_u[_qp]);
         // -_test[_i][_qp]*_k4_const*_Ar*std::exp(-15.76/std::max(_mean_en[_qp],1e-16))*_u[_qp];
}

Real
ElectronKernel::computeQpJacobian()
{
  return -_grad_test[_i][_qp]*(std::exp(_u[_qp])*-_muem*2/3*(std::exp(_mean_en[_qp]-_u[_qp])*_grad_phi[_j][_qp] 
							     +_grad_u[_qp]*std::exp(_mean_en[_qp]-_u[_qp])*-_phi[_j][_qp])
			       +std::exp(_u[_qp])*_phi[_j][_qp]*(-_muem*-_grad_potential[_qp]
								 -_muem*2/3*std::exp(_mean_en[_qp]-_u[_qp])*_grad_u[_qp]));
         // -_test[_i][_qp]*_k4_const*_Ar*std::exp(-15.76/std::max(_mean_en[_qp],1e-16))*_phi[_j][_qp];
}
