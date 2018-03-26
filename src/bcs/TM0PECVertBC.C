#include "TM0PECVertBC.h"

registerMooseObject("ZapdosApp", TM0PECVertBC);

template <>
InputParameters
validParams<TM0PECVertBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  return params;
}

TM0PECVertBC::TM0PECVertBC(const InputParameters & parameters) : IntegratedBC(parameters) {}

Real
TM0PECVertBC::computeQpResidual()
{
  return _test[_i][_qp] * (-_u[_qp] / _q_point[_qp](0));
}

Real
TM0PECVertBC::computeQpJacobian()
{
  return _test[_i][_qp] * (-_phi[_j][_qp] / _q_point[_qp](0));
}
