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
#include "WD.h"

template<>
InputParameters validParams<WD>()
{
  InputParameters params = validParams<Material>();

  params.addParam<Real>("user_diffusivity",0.1,"Diffusivity specified by the user");
  params.addParam<Real>("delta",0.5,"Scaling parameter for artificial diffusivity");
  params.addParam<bool>("consistent",false,"Whether to use consistent stabilization vs. inconsistent isotropic diffusion");  
  params.addParam<FunctionName>("velocity_function", "name of velocity function to utilize");
  params.addCoupledVar("potential", "The potential for calculating the electron velocity");
  params.addCoupledVar("atomic_ion_density", "The atomic ion density");
  params.addCoupledVar("molecular_ion_density", "The molecular ion density");
  params.addCoupledVar("r_velocity", "The velocity in the radial direction");
  params.addCoupledVar("z_velocity", "The velocity in the axial direction");
  return params;
}


WD::WD(const InputParameters & parameters) :
  Material(parameters),

  // Input parameters

  _user_diffusivity(getParam<Real>("user_diffusivity")),
  _delta(getParam<Real>("delta")),
  _consistent(getParam<bool>("consistent")),
    
  // Coupled variables
    
  _grad_potential(isCoupled("potential") ? coupledGradient("potential") : _grad_zero),
  _atomic_ion_density(isCoupled("atomic_ion_density") ? coupledValue("atomic_ion_density") : _zero),
  _molecular_ion_density(isCoupled("molecular_ion_density") ? coupledValue("molecular_ion_density"): _zero),
  _r_velocity(isCoupled("r_velocity") ? coupledValue("r_velocity") : _zero),
  _z_velocity(isCoupled("z_velocity") ? coupledValue("z_velocity") : _zero),
    
  // Functions
    
  _velocity_function(getFunction("velocity_function")),

  // Declare material properties. 
    
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
  _tau(declareProperty<Real>("tau")),
  _electron_density(declareProperty<Real>("electron_density")),
  _gamma_e(declareProperty<RealVectorValue>("gamma_e")),
  _eps_r(declareProperty<Real>("eps_r")),
  _rho(declareProperty<Real>("rho")),
  _atom_nt_num_density(declareProperty<Real>("atom_num_density")),
  _mass_velocity(declareProperty<RealVectorValue>("mass_velocity"))
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
WD::computeQpProperties()
{
  _electron_density[_qp] = _atomic_ion_density[_qp] + _molecular_ion_density[_qp];
  /*  _gamma_e[_qp] = -_diff_atomic_ions[_qp] * _grad_atomic_ion_density[_qp] -_diff_molecular_ions[_qp] * _grad_molecular_ion_density[_qp] + _electron_density[_qp] * _mass_velocity[_qp]
      _diffusivity[_qp] = _user_diffusivity; */
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
