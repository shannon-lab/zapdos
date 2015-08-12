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

#include "ArtificialDiff.h"


template<>
InputParameters validParams<ArtificialDiff>()
{
  // Start with the parameters from our parent
  InputParameters params = validParams<Diffusion>();

  // No parameters are necessary here because we're going to get
  // permeability and viscosity from the Material
  // so we just return params...
  
  // params.addRequiredCoupledVar("potential", "The electrical potential");

  params.addParam<bool>("crosswind",false,"Whether to use crosswind stabilization");
  params.addParam<Real>("epsilon",0.0,"Parameter to prevent non-zero denominators");
  return params;
}


ArtificialDiff::ArtificialDiff(const InputParameters & parameters) :
    Diffusion(parameters),
    
    // Input Parameters

    _crosswind(getParam<bool>("crosswind")),
    _epsilon(getParam<Real>("epsilon")),

    // Material Properties
   
    _velocity(getMaterialProperty<RealVectorValue>("velocity")),
    _tau(getMaterialProperty<Real>("tau")),
    _diffusivity(getMaterialProperty<Real>("diffusivity")),
 
    // Coupled Variables
    
    //_grad_potential(coupledGradient("potential"))

    // Variables unique to kernel

    _velocity_h(0.0,0.0,0.0),
    _d_velocity_h_d_uj(0.0,0.0,0.0),
    _peclet_num_h(0.0),
    _alpha_h(0.0),
    _tau_h(0.0),
    _sigma(0.0)
{
}

ArtificialDiff::~ArtificialDiff()
{
}

Real
ArtificialDiff::computeQpResidual()
{
  // Use the MaterialProperty references we stored earlier
  // return _delta*_current_elem->hmax()*_grad_potential[_qp].size()* Diffusion::computeQpResidual();
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
	  return (_tau[_qp]*_velocity[_qp]*_grad_test[_i][_qp] + _sigma*_velocity_h* _grad_test[_i][_qp]) * _velocity[_qp] * _grad_u[_qp];
	}
      else
	{
	  _velocity_h = _velocity[_qp]*_grad_u[_qp] / ( _grad_u[_qp].size() * _grad_u[_qp].size() + _epsilon ) * _grad_u[_qp];
	  _peclet_num_h = _current_elem->hmax() * _velocity_h.size() / (2.0 * _diffusivity[_qp]);
	  _alpha_h = 1.0 / std::tanh(_peclet_num_h) - 1.0 / _peclet_num_h;
	  _tau_h = _current_elem->hmax() * _alpha_h / (2.0*_velocity_h.size());
	  //	  _sigma = std::max(0.0,_tau_h-_tau[_qp]);
	  _sigma = _tau_h;
	  return (_tau[_qp]*_velocity[_qp]*_grad_test[_i][_qp] + _sigma * _velocity_h * _grad_test[_i][_qp] ) * _velocity[_qp] * _grad_u[_qp];
	} 
    }
  else
    {
      return _tau[_qp]*_velocity[_qp]*_grad_test[_i][_qp]*_velocity[_qp]*_grad_u[_qp];
    }
}

Real
ArtificialDiff::computeQpJacobian()
{
  // Use the MaterialProperty references we stored earlier
  // return _delta*_current_elem->hmax()*_grad_potential[_qp].size()*Diffusion::computeQpJacobian();
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
 	  return (_tau[_qp]*_velocity[_qp]*_grad_test[_i][_qp] + _sigma*_velocity_h* _grad_test[_i][_qp]) * _velocity[_qp] * _grad_phi[_j][_qp];
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

	  return _tau[_qp] * _velocity[_qp] * _grad_test[_i][_qp] * _velocity[_qp] * _grad_phi[_j][_qp] + _sigma*_d_velocity_h_d_uj*_grad_test[_i][_qp]*_velocity[_qp]*_grad_u[_qp] + _sigma*_velocity_h*_grad_test[_i][_qp]*_velocity[_qp]*_grad_phi[_j][_qp];
	}
    }
  else
    {
      return _tau[_qp]*_velocity[_qp]*_grad_test[_i][_qp]*_velocity[_qp]*_grad_phi[_j][_qp];
    }
}
