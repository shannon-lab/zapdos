#include "PotentialDrivenArtificialDiff.h"

template<>
InputParameters validParams<PotentialDrivenArtificialDiff>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredParam<std::string>("var_name_string","The name of the kernel variable. Required to import the correct mobility from the material properties file.");
  params.addRequiredCoupledVar("potential","The potential for calculating the advection velocity.");
  params.addParam<bool>("consistent",true,"Whether to use crosswind stabilization");
  params.addParam<Real>("delta",0.5,"Scaling parameter for artificial diffusivity");
  return params;
}

PotentialDrivenArtificialDiff::PotentialDrivenArtificialDiff(const std::string & name, InputParameters parameters) :
    Kernel(name, parameters),

    // Input parameters

    _consistent(getParam<bool>("consistent")),
    _delta(getParam<Real>("delta")),

    // Coupled variables

    _grad_potential(coupledGradient("potential")),

    // Material properties

    _mobility(getMaterialProperty<Real>("mu"+getParam<std::string>("var_name_string"))),
    _diffusivity(getMaterialProperty<Real>("D"+getParam<std::string>("var_name_string"))),

    // Variables unique to class
    
    _advection_velocity(0.0,0.0,0.0),
    _peclet_num(0.0),
    _alpha(0.0),
    _tau(0.0)
{
}

PotentialDrivenArtificialDiff::~PotentialDrivenArtificialDiff()
{
}

Real
PotentialDrivenArtificialDiff::computeQpResidual()
{
  _advection_velocity = _mobility[_qp]*-_grad_potential[_qp];
  _peclet_num = _current_elem->hmax() * _advection_velocity.size() / (2.0 * _diffusivity[_qp]);
  _alpha = 1.0 / std::tanh(_peclet_num) - 1.0 / _peclet_num;
  
  if (_consistent)
  {
    // Consistent diffusion formulation of tau
    _tau = _delta * _current_elem->hmax() * _alpha / _advection_velocity.size();
  }
  else if (!_consistent)
  {
    // Isotropic diffusion formulation of tau

    _tau = _delta * _current_elem->hmax() / _advection_velocity.size();
  }

  return _tau*_advection_velocity*_grad_test[_i][_qp]*_advection_velocity*_grad_u[_qp];    
}

Real
PotentialDrivenArtificialDiff::computeQpJacobian()
{
  _advection_velocity = _mobility[_qp]*-_grad_potential[_qp];
  _peclet_num = _current_elem->hmax() * _advection_velocity.size() / (2.0 * _diffusivity[_qp]);
  _alpha = 1.0 / std::tanh(_peclet_num) - 1.0 / _peclet_num;
  
  if (_consistent)
  {
    // Consistent diffusion formulation of tau
    _tau = _delta * _current_elem->hmax() * _alpha / _advection_velocity.size();
  }
  else if (!_consistent)
  {
    // Isotropic diffusion formulation of tau

    _tau = _delta * _current_elem->hmax() / _advection_velocity.size();
  }

  return _tau*_advection_velocity*_grad_test[_i][_qp]*_advection_velocity*_grad_phi[_j][_qp];    
}
