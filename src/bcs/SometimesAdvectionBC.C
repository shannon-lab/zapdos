#include "SometimesAdvectionBC.h"
#include "Function.h"

template<>
InputParameters validParams<SometimesAdvectionBC>()
{
    InputParameters params = validParams<IntegratedBC>();
    params.addRequiredParam<FunctionName>("velocity_function", "the name of the velocity function to utilize");    
    return params;
}

SometimesAdvectionBC::SometimesAdvectionBC(const InputParameters & parameters) :
  IntegratedBC(parameters),

  // Parameters
  _velocity(getFunction("velocity_function")),

  // Unique variables
  _a(0.0)
{}

Real
SometimesAdvectionBC::computeQpResidual()
{
  if ( _velocity.vectorValue(_t,_qp)*_normals[_qp] > 0.0 ) {
    _a = 1.0;
  }
  else {
    _a = 0.0;
  }
  return _test[_i][_qp]*(_a*_u[_qp]*_velocity.vectorValue(_t,_qp)*_normals[_qp]+_u[_qp]);
}

Real
SometimesAdvectionBC::computeQpJacobian()
{
  if ( _velocity.vectorValue(_t,_qp)*_normals[_qp] > 0.0 ) {
    _a = 1.0;
  }
  else {
    _a = 0.0;
  }
  return _test[_i][_qp]*(_a*_phi[_j][_qp]*_velocity.vectorValue(_t,_qp)*_normals[_qp]+_phi[_j][_qp]);
} 
