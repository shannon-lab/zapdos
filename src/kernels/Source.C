#include "Source.h"

template<>
InputParameters validParams<Source>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredParam<std::string>("var_name_string","The name of the kernel variable. Required to import the correct source and on-diagonal Jacobian term from the material properties file");
  return params;
}

Source::Source(const InputParameters & parameters) :
  Kernel(parameters),

  // Input Parameters

  // Material Properties

  _source(getMaterialProperty<Real>("s"+getParam<std::string>("var_name_string"))),
  _jacobian(getMaterialProperty<Real>("Jac_"+getParam<std::string>("var_name_string")))
{
}

Source::~Source()
{}

Real
Source::computeQpResidual()
{
  return -_test[_i][_qp]*_source[_qp];
}

Real
Source::computeQpJacobian()
{
  return -_test[_i][_qp]*_jacobian[_qp]*_phi[_j][_qp];
}
