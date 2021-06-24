#include "FaradayCurrentBC.h"

registerMooseObject("ZapdosApp", FaradayCurrentBC);

InputParameters
FaradayCurrentBC::validParams()
{
  InputParameters params = ADVectorIntegratedBC::validParams();
  params.addRequiredParam<FunctionName>("applied_current_dot", "Applied current first time derivative vector function.");
  params.addRequiredParam<Real>("driving_frequency", "System driving frequency.");
  return params;
}

FaradayCurrentBC::FaradayCurrentBC(const InputParameters & parameters)
  : ADVectorIntegratedBC(parameters),
  _mu(12.56637e-7),
  _frequency(getParam<Real>("driving_frequency")),
  _current_dot(getFunction("applied_current_dot"))
{
}

ADReal
FaradayCurrentBC::computeQpResidual()
{
  Real omega = 2 * libMesh::pi * _frequency;
  Real bc_const = _mu * omega / (2 * libMesh::pi * _q_point[_qp](0));

  return _test[_i][_qp] * _normals[_qp].cross(-bc_const * _current_dot.vectorValue(_t, _q_point[_qp]));
}
