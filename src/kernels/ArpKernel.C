#include "ArpKernel.h"

template<>
InputParameters validParams<ArpKernel>()
{
  InputParameters params = validParams<Kernel>();

  // params.addRequiredCoupledVar("potential", "The electric potential");
  params.addRequiredCoupledVar("em", "The electron density");
  // params.addRequiredCoupledVar("Te", "The electront temperature");
  return params;
}

ArpKernel::ArpKernel(const std::string & name, InputParameters parameters) :
  Kernel(name, parameters),

  _em(coupledValue("em")),
  // _grad_potential(coupledGradient("potential")),
  // _Te(coupledValue("Te")),

  _k4_const(5e-14),
  _Ar(1.01e5/(300*1.38e-23))
{}

ArpKernel::~ArpKernel()
{}

Real
ArpKernel::computeQpResidual()
{
  // return -_test[_i][_qp]*_k4_const*_Ar*_em[_qp]*std::exp(-15.76/std::max(_Te[_qp],1e-16));
  return 0.0;
}

Real
ArpKernel::computeQpJacobian()
{
  return 0.0;
}
