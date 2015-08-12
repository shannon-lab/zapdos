#include "AdvectionDoNothingBC.h"
#include "Function.h"

template<>
InputParameters validParams<AdvectionDoNothingBC>()
{
    InputParameters params = validParams<IntegratedBC>();
    params.addRequiredParam<FunctionName>("velocity_function", "the name of the velocity function to utilize");    
    return params;
}

AdvectionDoNothingBC::AdvectionDoNothingBC(const InputParameters & parameters) :
  IntegratedBC(parameters),

  // Parameters
  _velocity(getFunction("velocity_function"))
{}

Real
AdvectionDoNothingBC::computeQpResidual()
{
  return _test[_i][_qp]*(_u[_qp]*_velocity.vectorValue(_t,_qp)*_normals[_qp]+_u[_qp]);
}

Real
AdvectionDoNothingBC::computeQpJacobian()
{
  return _test[_i][_qp]*(_phi[_j][_qp]*_velocity.vectorValue(_t,_qp)*_normals[_qp]+_phi[_j][_qp]);
} 
