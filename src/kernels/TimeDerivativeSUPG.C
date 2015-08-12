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

TimeDerivativeSUPG::TimeDerivativeSUPG(const InputParameters & parameters) :
    TimeKernel(parameters),
    _lumping(getParam<bool>("lumping")),
    _crosswind(getParam<bool>("crosswind")),
    _epsilon(getParam<Real>("epsilon")),

    // Material Properties

    _tau(getMaterialProperty<Real>("tau")),
    //    _velocity(getMaterialProperty<RealVectorValue>("velocity")),
    _velocity(getMaterialProperty<RealVectorValue>("velocity")),
    _diffusivity(getMaterialProperty<Real>("diffusivity")),

    // Kernel specific properties

    _velocity_h(0.0,0.0,0.0),
    _d_velocity_h_d_uj(0.0,0.0,0.0),
    _peclet_num_h(0.0),
    _alpha_h(0.0),
    _tau_h(0.0),
    _sigma(0.0)
{
}

Real
TimeDerivativeSUPG::computeQpResidual()
{
  if (_crosswind)
    {
      if (_grad_u[_qp].size() == 0.0)
	{
	  _velocity_h = _velocity[_qp];
	  _peclet_num_h = _current_elem->hmax() * _velocity_h.size() / (2.0 * _diffusivity[_qp]);
	  _alpha_h = 1.0 / std::tanh(_peclet_num_h) - 1.0 / _peclet_num_h;
	  _tau_h = _current_elem->hmax() * _alpha_h / (2.0*_velocity_h.size());
	  //	  _sigma = std::max(0.0,_tau_h-_tau[_qp]);
	  _sigma = _tau_h;
	  return (_tau[_qp]*_velocity[_qp]*_grad_test[_i][_qp] + _sigma*_velocity_h * _grad_test[_i][_qp] ) * _u_dot[_qp];
	}
      else
	{
	  _velocity_h = _velocity[_qp]*_grad_u[_qp] / ( _grad_u[_qp].size() * _grad_u[_qp].size() + _epsilon ) * _grad_u[_qp];
	  _peclet_num_h = _current_elem->hmax() * _velocity_h.size() / (2.0 * _diffusivity[_qp]);
	  _alpha_h = 1.0 / std::tanh(_peclet_num_h) - 1.0 / _peclet_num_h;
	  _tau_h = _current_elem->hmax() * _alpha_h / (2.0*_velocity_h.size());
	  //	  _sigma = std::max(0.0,_tau_h-_tau[_qp]);
	  _sigma = _tau_h;
	  return (_tau[_qp]*_velocity[_qp]*_grad_test[_i][_qp] + _sigma*_velocity_h * _grad_test[_i][_qp] )  * _u_dot[_qp];
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
	  _velocity_h = _velocity[_qp];
	  _peclet_num_h = _current_elem->hmax() * _velocity_h.size() / (2.0 * _diffusivity[_qp]);
	  _alpha_h = 1.0 / std::tanh(_peclet_num_h) - 1.0 / _peclet_num_h;
	  _tau_h = _current_elem->hmax() * _alpha_h / (2.0*_velocity_h.size());
	  //	  _sigma = std::max(0.0,_tau_h-_tau[_qp]);
	  _sigma = _tau_h;
	  return (_tau[_qp]*_velocity[_qp]*_grad_test[_i][_qp] + _sigma*_velocity_h * _grad_test[_i][_qp] ) * _phi[_j][_qp] * _du_dot_du[_qp];
	}
      else
	{

	  _velocity_h = _velocity[_qp]*_grad_u[_qp] / ( _grad_u[_qp].size() * _grad_u[_qp].size() + _epsilon ) * _grad_u[_qp];
	  _d_velocity_h_d_uj =  (std::pow(_grad_u[_qp].size(),2)* ( _velocity[_qp] * _grad_phi[_j][_qp])-(_velocity[_qp] * _grad_u[_qp] )* ( 2.0 * _grad_u[_qp] * _grad_phi[_j][_qp] ) ) / std::pow(_grad_u[_qp].size(),4)*_grad_u[_qp] + _velocity[_qp]*_grad_u[_qp] / std::pow(_grad_u[_qp].size(),2) * _grad_phi[_j][_qp];
	  _peclet_num_h = _current_elem->hmax() * _velocity_h.size() / (2.0 * _diffusivity[_qp]);
	  _alpha_h = 1.0 / std::tanh(_peclet_num_h) - 1.0 / _peclet_num_h;
	  _tau_h = _current_elem->hmax() * _alpha_h / (2.0*_velocity_h.size());
	  //	  _sigma = std::max(0.0,_tau_h-_tau[_qp]);
	  _sigma = _tau_h;

	  // First term is derivative of streamline test function times derivative of physics. Second term is derivative of crosswind test term times physics. Third term is crosswind test term times derivative of physics.

	  return _tau[_qp] * _velocity[_qp] * _grad_test[_i][_qp] * _phi[_j][_qp] * _du_dot_du[_qp] + _sigma*_d_velocity_h_d_uj*_grad_test[_i][_qp]*_u_dot[_qp] + _sigma*_velocity_h*_grad_test[_i][_qp]* _phi[_j][_qp] * _du_dot_du[_qp];

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
