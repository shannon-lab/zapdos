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
#include "NoCouplingAir.h"

template<>
InputParameters validParams<NoCouplingAir>()
{
  InputParameters params = validParams<Material>();

  // Add a parameter to get the radius of the balls in the column (used later to interpolate permeability).
  params.addParam<Real>("velocity_multiplier", 1.0, "This multiplies the velocity coefficient in case you want to modify the magnitude of the velocity.");
  params.addParam<Real>("relative_permittivity", 1.0, "Multiplies the permittivity of free space.");
  params.addParam<Real>("ionization_multiplier",1.0,"This multiplies the ionization coefficient in case you want to modify the magnitude of ionization.");
  params.addParam<Real>("user_potential_mult",1.0e4,"Scaling for potential");
  params.addParam<Real>("user_density_mult",1.0e19,"Scaling for densities");
  params.addParam<Real>("user_diffusivity",0.1,"Diffusivity specified by the user");
  params.addParam<Real>("delta",0.5,"Scaling parameter for artificial diffusivity");
  params.addParam<bool>("consistent",false,"Whether to use consistent stabilization vs. inconsistent isotropic diffusion");  
  //  params.addParam<bool>("coupling",true,"Whether the velocity is determined by a user function or through a coupling variable");
  params.addParam<FunctionName>("velocity_function", "name of velocity function to utilize");
  params.addCoupledVar("potential", "The potential for calculating the electron velocity");
  return params;
}


NoCouplingAir::NoCouplingAir(const InputParameters & parameters) :
    Material(parameters),

    // Input parameters
    _velocity_multiplier(getParam<Real>("velocity_multiplier")),
    _relative_permittivity(getParam<Real>("relative_permittivity")),
    _ionization_multiplier(getParam<Real>("ionization_multiplier")),
    _user_potential_mult(getParam<Real>("user_potential_mult")),
    _user_density_mult(getParam<Real>("user_density_mult")),
    _user_diffusivity(getParam<Real>("user_diffusivity")),
    _delta(getParam<Real>("delta")),
    _consistent(getParam<bool>("consistent")),
    //    _coupling(getParam<bool>("coupling")),
    
    // Coupled variables
    
    _grad_potential(isCoupled("potential") ? coupledGradient("potential") : _grad_zero),
    
// Functions
    
  _velocity_function(getFunction("velocity_function")),

// Declare material properties.  This returns references that we
// hold onto as member variables
  _velocity_coeff(declareProperty<Real>("velocity_coeff")),
  _permittivity(declareProperty<Real>("permittivity")),
  _coulomb_charge(declareProperty<Real>("coulomb_charge")),
  _ionization_coeff(declareProperty<Real>("ionization_coeff")),
  _ion_activation_energy(declareProperty<Real>("ion_activation_energy")),
  _potential_mult(declareProperty<Real>("potential_mult")),
  _density_mult(declareProperty<Real>("density_mult")),
  _peclet_num(declareProperty<Real>("peclet_num")),
  _alpha(declareProperty<Real>("alpha")),
  _velocity(declareProperty<RealVectorValue>("velocity")),
  _velocity_norm(declareProperty<RealVectorValue>("velocity_norm")),
  _diffusivity(declareProperty<Real>("diffusivity")),
  _tau(declareProperty<Real>("tau"))
{
  if (isCoupled("potential"))
    {
      _coupling = true;
    }
  else
    {
      _coupling = false;
    }
}

void
NoCouplingAir::computeQpProperties()
{

  // Paper is Morrow numerical modelling paper

  /* Real mobility_from_morrow = (.0382+2.9e5/760)/(1.0e4);
  Real mobility_from_jannis = 0.03;
  Real free_space_perm = 8.85e-12;
  Real ionization_from_paper = 0.35;

  _velocity_coeff[_qp] = _velocity_multiplier*mobility_from_jannis;
  _permittivity[_qp] = free_space_perm*_relative_permittivity;
  _coulomb_charge[_qp] = 1.6e-19;
  _ionization_coeff[_qp] = _ionization_multiplier*ionization_from_paper;
  _ion_activation_energy[_qp] = 1.65e7; // From Morrow paper
  _potential_mult[_qp] = _user_potential_mult;
  _density_mult[_qp] = _user_density_mult; */
  
  _diffusivity[_qp] = _user_diffusivity;
  if (_coupling)
    {
      _velocity[_qp] = _grad_potential[_qp];
    }
  else
    { 
      _velocity[_qp] = _velocity_function.vectorValue(_t,_qp);
    }
  _velocity_norm[_qp] = _velocity[_qp] / _velocity[_qp].size();  
  _peclet_num[_qp] = _current_elem->hmax() * _velocity[_qp].size() / (2.0 * _diffusivity[_qp]);
  _alpha[_qp] = 1.0 / std::tanh(_peclet_num[_qp]) - 1.0 / _peclet_num[_qp];
  
  if (_consistent)
  {
    // Consistent diffusion formulation of tau
    _tau[_qp] = _delta * _current_elem->hmax() * _alpha[_qp] / _velocity[_qp].size();
  }
  else if (!_consistent)
  {
    // Isotropic diffusion formulation of tau

    _tau[_qp] = _delta * _current_elem->hmax() / _velocity[_qp].size();
  }
}
