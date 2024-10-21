#include "TimeDerivativeLog.h"

registerMooseObject("CraneApp", TimeDerivativeLog);

template <>
InputParameters
validParams<TimeDerivativeLog>()
{
  InputParameters params = validParams<TimeKernel>();
  params.addParam<bool>("lumping", false, "True for mass matrix lumping, false otherwise");
  return params;
}

TimeDerivativeLog::TimeDerivativeLog(const InputParameters & parameters)
  : TimeKernel(parameters), _lumping(getParam<bool>("lumping"))

{
}

Real
TimeDerivativeLog::computeQpResidual()
{
  return _test[_i][_qp] * std::exp(_u[_qp]) * _u_dot[_qp];
}

Real
TimeDerivativeLog::computeQpJacobian()
{
  return _test[_i][_qp] * (std::exp(_u[_qp]) * _phi[_j][_qp] * _u_dot[_qp] +
                           std::exp(_u[_qp]) * _du_dot_du[_qp] * _phi[_j][_qp]);
}
