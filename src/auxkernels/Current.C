#include "Current.h"

template<>
InputParameters validParams<Current>()
{
  InputParameters params = validParams<AuxKernel>();

  params.addRequiredCoupledVar("density_log","The electron density");
  params.addRequiredCoupledVar("potential","The potential");

  return params;
}

Current::Current(const InputParameters & parameters) :
    AuxKernel(parameters),

    _density_var(*getVar("density_log",0)),
    _density_log(coupledValue("density_log")),
    _grad_density_log(coupledGradient("density_log")),
    _grad_potential(coupledGradient("potential")),
    _mu(getMaterialProperty<Real>("mu" + _density_var.name())),
    _sgn(getMaterialProperty<Real>("sgn" + _density_var.name())),
    _diff(getMaterialProperty<Real>("diff" + _density_var.name()))
{
}

Real
Current::computeValue()
{
  return _sgn[_qp] * 1.6e-19 * 6.02e23 * (_sgn[_qp] * _mu[_qp] * -_grad_potential[_qp](0) * std::exp(_density_log[_qp]) - _diff[_qp]* std::exp(_density_log[_qp]) * _grad_density_log[_qp](0));
}
