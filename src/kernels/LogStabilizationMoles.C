#include "LogStabilizationMoles.h"

registerMooseObject("ZapdosApp", LogStabilizationMoles);

template <>
InputParameters
validParams<LogStabilizationMoles>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<Real>("offset",
                                "The offset parameter that goes into the exponential function");
  return params;
}

LogStabilizationMoles::LogStabilizationMoles(const InputParameters & parameters)
  : Kernel(parameters), _offset(getParam<Real>("offset"))
{
}

LogStabilizationMoles::~LogStabilizationMoles() {}

Real
LogStabilizationMoles::computeQpResidual()
{
  return -_test[_i][_qp] * std::exp(-(_offset + _u[_qp]));
}

Real
LogStabilizationMoles::computeQpJacobian()
{
  return -_test[_i][_qp] * std::exp(-(_offset + _u[_qp])) * -_phi[_j][_qp];
}
