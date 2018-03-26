#include "UserSource.h"

registerMooseObject("ZapdosApp", UserSource);

template <>
InputParameters
validParams<UserSource>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<Real>("source_magnitude", "The numerical value of the source magnitude.");
  return params;
}

UserSource::UserSource(const InputParameters & parameters)
  : Kernel(parameters), _source(getParam<Real>("source_magnitude"))
{
}

UserSource::~UserSource() {}

Real
UserSource::computeQpResidual()
{
  return -_test[_i][_qp] * _source;
}

Real
UserSource::computeQpJacobian()
{
  return 0.;
}
