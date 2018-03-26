#include "ElectronTimeDerivative.h"

registerMooseObject("ZapdosApp", ElectronTimeDerivative);

template <>
InputParameters
validParams<ElectronTimeDerivative>()
{
  InputParameters params = validParams<TimeKernel>();
  params.addParam<bool>("lumping", false, "True for mass matrix lumping, false otherwise");
  return params;
}

ElectronTimeDerivative::ElectronTimeDerivative(const InputParameters & parameters)
  : TimeKernel(parameters), _lumping(getParam<bool>("lumping"))

{
}

Real
ElectronTimeDerivative::computeQpResidual()
{
  return _test[_i][_qp] * std::exp(_u[_qp]) * _u_dot[_qp];
}

Real
ElectronTimeDerivative::computeQpJacobian()
{
  return _test[_i][_qp] * (std::exp(_u[_qp]) * _phi[_j][_qp] * _u_dot[_qp] +
                           std::exp(_u[_qp]) * _du_dot_du[_qp] * _phi[_j][_qp]);
}
