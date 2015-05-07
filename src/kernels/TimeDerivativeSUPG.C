/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "TimeDerivativeSUPG.h"

template<>
InputParameters validParams<TimeDerivativeSUPG>()
{
  InputParameters params = validParams<TimeKernel>();
  params.addParam<bool>("lumping", false, "True for mass matrix lumping, false otherwise");
  params.addParam<bool>("crosswind",false,"True if you want to include crosswind diffusion");
  params.addParam<Real>("epsilon",0.0,"To prevent denominators from being zero");
  return params;
}

TimeDerivativeSUPG::TimeDerivativeSUPG(const std::string & name, InputParameters parameters) :
    TimeKernel(name, parameters),
    _lumping(getParam<bool>("lumping")),
    _crosswind(getParam<bool>("crosswind")),
    _epsilon(getParam<Real>("epsilon")),

    // Material Properties

    _tau(getMaterialProperty<Real>("tau")),
    //    _velocity(getMaterialProperty<RealVectorValue>("velocity"))
    _velocity(getMaterialProperty<RealVectorValue>("velocity"))

    // Kernel specific properties
    //    _velocity(1.0,0.0,0.0)
{
}

Real
TimeDerivativeSUPG::computeQpResidual()
{
  if (_crosswind)
    {
      if (_grad_u[_qp].size() == 0.0)
	{
	  return _tau[_qp]*(_velocity[_qp]*_grad_test[_i][_qp] + _velocity[_qp] * _grad_test[_i][_qp] ) * _u_dot[_qp];
	}
      else
	{
	  return _tau[_qp]*(_velocity[_qp]*_grad_test[_i][_qp] + _velocity[_qp]*_grad_u[_qp] / ( _grad_u[_qp].size() * _grad_u[_qp].size() + _epsilon ) * _grad_u[_qp] * _grad_test[_i][_qp] ) * _u_dot[_qp];
	}
    }
  else 
    {
      return _tau[_qp]*_velocity[_qp]*_grad_test[_i][_qp]*_u_dot[_qp];
    }
}

Real
TimeDerivativeSUPG::computeQpJacobian()
{
  if (_crosswind)
    {
      if (_grad_u[_qp].size() == 0.0)
	{
	  return _tau[_qp]*(_velocity[_qp]*_grad_test[_i][_qp] + _velocity[_qp] * _grad_test[_i][_qp] ) * _phi[_j][_qp] * _du_dot_du[_qp];
	}
      else
	{
      // First term is from taking the partial derivative with respect to the standard SUPG term. Second and third terms are from taking the partial derivative with respect to the shock-capturing term. In the second term the derivative is with respect to the shock-capturing version of the test function while keeping the physics (du / dt) constant. The third term is from keeping the shock-capturing test function constant while taking the derivative of the physics. 

	  return  _tau[_qp]*_velocity[_qp]*_grad_test[_i][_qp]*_phi[_j][_qp]*_du_dot_du[_qp] + _tau[_qp] * ((_grad_u[_qp] * _grad_test[_i][_qp] )*( ( ( _grad_u[_qp] * _grad_u[_qp] )* ( _velocity[_qp] * _grad_phi[_j][_qp])-(_velocity[_qp] * _grad_u[_qp] )* ( 2.0 * _grad_u[_qp] * _grad_phi[_j][_qp] ) ) / ( (_grad_u[_qp] * _grad_u[_qp] + _epsilon)*(_grad_u[_qp] * _grad_u[_qp] + _epsilon)))+(_velocity[_qp]*_grad_u[_qp]) * (_grad_test[_i][_qp]*_grad_phi[_j][_qp]) / (_grad_u[_qp]*_grad_u[_qp] + _epsilon) ) * _u_dot[_qp] + _tau[_qp] * _grad_u[_qp] * _grad_test[_i][_qp] * (_velocity[_qp] * _grad_u[_qp])/(_grad_u[_qp]*_grad_u[_qp] + _epsilon) * _phi[_j][_qp]*_du_dot_du[_qp];
	}
    }
  else
    {
      return _tau[_qp]*_velocity[_qp]*_grad_test[_i][_qp]*_phi[_j][_qp]*_du_dot_du[_qp];
    }
}

void
TimeDerivativeSUPG::computeJacobian()
{
  if (_lumping)
  {
    DenseMatrix<Number> & ke = _assembly.jacobianBlock(_var.number(), _var.number());

    for (_i = 0; _i < _test.size(); _i++)
      for (_j = 0; _j < _phi.size(); _j++)
        for (_qp = 0; _qp < _qrule->n_points(); _qp++)
        {
          ke(_i, _i) += _JxW[_qp] * _coord[_qp] * computeQpJacobian();
        }
  }
  else
    TimeKernel::computeJacobian();
}
