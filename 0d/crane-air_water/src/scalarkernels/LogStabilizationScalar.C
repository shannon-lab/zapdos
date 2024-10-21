#include "LogStabilizationScalar.h"

registerMooseObject("CraneApp", LogStabilizationScalar);

template <>
InputParameters
validParams<LogStabilizationScalar>()
{
  InputParameters params = validParams<ODEKernel>();
  params.addRequiredParam<Real>("offset",
                                "The offset parameter that goes into the exponential function");
  return params;
}

LogStabilizationScalar::LogStabilizationScalar(const InputParameters & parameters)
  : ODEKernel(parameters), _offset(getParam<Real>("offset"))
{
}

LogStabilizationScalar::~LogStabilizationScalar() {}

Real
LogStabilizationScalar::computeQpResidual()
{
  return -std::exp(-(_offset + _u[_i]));
}

Real
LogStabilizationScalar::computeQpJacobian()
{
  return std::exp(-(_offset + _u[_i]));
}
