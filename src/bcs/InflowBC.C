#include "InflowBC.h"
#include "Function.h"

template<>
InputParameters validParams<InflowBC>()
{
    InputParameters params = validParams<IntegratedBC>();
    params.addRequiredParam<Real>("vx", "The velocity in the x direction");
    params.addRequiredParam<Real>("inlet_conc", "The inlet concentration");
    return params;
}

InflowBC::InflowBC(const InputParameters & parameters) :
  IntegratedBC(parameters),

  // Parameters
  _vx(getParam<Real>("vx")),
  _inlet_conc(getParam<Real>("inlet_conc"))
{}

Real
InflowBC::computeQpResidual()
{
  Real vy = 0.;
  Real vz = 0.;
  RealVectorValue velocity;
  velocity(0) = _vx;
  velocity(1) = vy;
  velocity(2) = vz;

  return _test[_i][_qp] * _inlet_conc * velocity * _normals[_qp];
}

Real
InflowBC::computeQpJacobian()
{
  return 0.;
}
