#include "Sigma.h"

registerMooseObject("ZapdosApp", Sigma);

template <>
InputParameters
validParams<Sigma>()
{
  InputParameters params = validParams<AuxKernel>();

  params.addRequiredCoupledVar("n", "The density of the ions.");
  params.addRequiredCoupledVar("potential", "The potential");
  return params;
}

Sigma::Sigma(const InputParameters & parameters)
  : AuxKernel(parameters),

    _n(coupledValue("n")),
    _grad_potential(coupledGradient("potential"))
{
}

Real
Sigma::computeValue()
{
  return _u_old[_qp] + _dt * -_grad_potential[_qp] * _n[_qp] * _var.normals()[_qp];
}
