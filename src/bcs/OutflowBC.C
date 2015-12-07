#include "OutflowBC.h"
#include "Function.h"

template<>
InputParameters validParams<OutflowBC>()
{
    InputParameters params = validParams<IntegratedBC>();
    params.addRequiredParam<Real>("vx", "The velocity in the x direction");
    return params;
}

OutflowBC::OutflowBC(const InputParameters & parameters) :
  IntegratedBC(parameters),

  // Parameters
  _vx(getParam<Real>("vx"))
{}

Real
OutflowBC::computeQpResidual()
{
  Real vy = 0.;
  Real vz = 0.;
  RealVectorValue velocity = (_vx, vy, vz);

  return _test[_i][_qp] * _u[_qp] * velocity * _normals[_qp];
}

Real
OutflowBC::computeQpJacobian()
{
  Real vy = 0.;
  Real vz = 0.;
  RealVectorValue velocity = (_vx, vy, vz);

  return _test[_i][_qp] * _phi[_j][_qp] * velocity * _normals[_qp];
}
