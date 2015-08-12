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

#include "VelocityH.h"

template<>
InputParameters validParams<VelocityH>()
{
  InputParameters params = validParams<AuxKernel>();
  
  //MooseEnum component("x y z");
  
  //params.addRequiredParam<MooseEnum>("component",component, "The desired component of potential gradient.");

  // Add a "coupling paramater" to get a variable from the input file.
  params.addRequiredCoupledVar("some_var", "The advected variable needed for determining tau.");

  return params;
}

VelocityH::VelocityH(const InputParameters & parameters) :
    AuxKernel(parameters),
    
    //_component(getParam<MooseEnum>("component")),

    // Initialize coupling variables

    _grad_some_var(coupledGradient("some_var")),
    _some_var(coupledValue("some_var")),

    // Get material properties

    _tau(getMaterialProperty<Real>("tau")),
    _velocity(getMaterialProperty<RealVectorValue>("velocity")),
    _diffusivity(getMaterialProperty<Real>("diffusivity")),

    // Class specific properties

    _velocity_h(0.0,0.0,0.0),
    _d_velocity_h_d_uj(0.0,0.0,0.0),
    _peclet_num_h(0.0),
    _alpha_h(0.0),
    _tau_h(0.0),
    _sigma(0.0)
{
}

Real
VelocityH::computeValue()
{
  if (_grad_some_var[_qp].size() == 0)
    {
      _velocity_h = _velocity[_qp];
      /*      _peclet_num_h = _current_elem->hmax() * _velocity_h.size() / (2.0 * _diffusivity[_qp]);
      _alpha_h = 1.0 / std::tanh(_peclet_num_h) - 1.0 / _peclet_num_h;
      _tau_h = _current_elem->hmax() * _alpha_h / (2.0*_velocity_h.size());
      _sigma = std::max(0.0,_tau_h-_tau[_qp]); */
      return _velocity_h.size();
    }
  else
    {
      _velocity_h = _velocity[_qp]*_grad_some_var[_qp] / std::pow(_grad_some_var[_qp].size(),2) * _grad_some_var[_qp];
      /*      _peclet_num_h = _current_elem->hmax() * _velocity_h.size() / (2.0 * _diffusivity[_qp]);
      _alpha_h = 1.0 / std::tanh(_peclet_num_h) - 1.0 / _peclet_num_h;
      _tau_h = _current_elem->hmax() * _alpha_h / (2.0*_velocity_h.size());
      _sigma = std::max(0.0,_tau_h-_tau[_qp]); */
      return _velocity_h.size();
    }
}
