#include "UnitySource.h"

template<>
InputParameters validParams<UnitySource>()
{
  InputParameters params = validParams<Kernel>();
  return params;
}

UnitySource::UnitySource(const std::string & name, InputParameters parameters) :
  Kernel(name, parameters)
{
}

UnitySource::~UnitySource()
{}

Real
UnitySource::computeQpResidual()
{
  return -_test[_i][_qp]*1.0;
}

Real
UnitySource::computeQpJacobian()
{
  return 0.0;
}
