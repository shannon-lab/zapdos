#include "ReactantAARxn.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("ZapdosApp", ReactantAARxn);

template <>
InputParameters
validParams<ReactantAARxn>()
{
  InputParameters params = validParams<Kernel>();
  return params;
}

ReactantAARxn::ReactantAARxn(const InputParameters & parameters)
  : Kernel(parameters),

    _reaction_coeff(getMaterialProperty<Real>("k" + _var.name() + _var.name()))
{
}

Real
ReactantAARxn::computeQpResidual()
{
  return -_test[_i][_qp] * (-2.) * _reaction_coeff[_qp] * std::exp(_u[_qp]) * std::exp(_u[_qp]);
}

Real
ReactantAARxn::computeQpJacobian()
{
  return -_test[_i][_qp] * (-2.) * _reaction_coeff[_qp] * 2. * std::exp(_u[_qp]) *
         std::exp(_u[_qp]) * _phi[_j][_qp];
}
