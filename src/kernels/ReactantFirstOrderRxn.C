#include "ReactantFirstOrderRxn.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("ZapdosApp", ReactantFirstOrderRxn);

template <>
InputParameters
validParams<ReactantFirstOrderRxn>()
{
  InputParameters params = validParams<Kernel>();
  return params;
}

ReactantFirstOrderRxn::ReactantFirstOrderRxn(const InputParameters & parameters)
  : Kernel(parameters),

    _reaction_coeff(getMaterialProperty<Real>("k" + _var.name()))
{
}

Real
ReactantFirstOrderRxn::computeQpResidual()
{
  return -_test[_i][_qp] * (-1.) * _reaction_coeff[_qp] * std::exp(_u[_qp]);
}

Real
ReactantFirstOrderRxn::computeQpJacobian()
{
  return -_test[_i][_qp] * (-1.) * _reaction_coeff[_qp] * std::exp(_u[_qp]) * _phi[_j][_qp];
}
