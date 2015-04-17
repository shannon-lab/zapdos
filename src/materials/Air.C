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
#include "Air.h"

template<>
InputParameters validParams<Air>()
{
  InputParameters params = validParams<Material>();

  // Add a parameter to get the radius of the balls in the column (used later to interpolate permeability).
  params.addParam<Real>("velocity_multiplier", 1.0, "This multiplies the velocity coefficient in case you want to modify the magnitude of the velocity.");
  params.addParam<Real>("relative_permittivity", 1.0, "Multiplies the permittivity of free space.");
  params.addParam<Real>("ionization_multiplier",1.0,"This multiplies the ionization coefficient in case you want to modify the magnitude of ionization.");
  params.addParam<Real>("user_potential_mult",1.0e4,"Scaling for potential");
  params.addParam<Real>("user_density_mult",1.0e19,"Scaling for densities");

  return params;
}


Air::Air(const std::string & name, InputParameters parameters) :
    Material(name, parameters),

    // Get parameters from the input file
    _velocity_multiplier(getParam<Real>("velocity_multiplier")),
    _relative_permittivity(getParam<Real>("relative_permittivity")),
    _ionization_multiplier(getParam<Real>("ionization_multiplier")),
    _user_potential_mult(getParam<Real>("user_potential_mult")),
    _user_density_mult(getParam<Real>("user_density_mult")),

    // Declare material properties.  This returns references that we
    // hold onto as member variables
    _velocity_coeff(declareProperty<Real>("velocity_coeff")),
    _permittivity(declareProperty<Real>("permittivity")),
    _coulomb_charge(declareProperty<Real>("coulomb_charge")),
    _ionization_coeff(declareProperty<Real>("ionization_coeff")),
    _ion_activation_energy(declareProperty<Real>("ion_activation_energy")),
    _potential_mult(declareProperty<Real>("potential_mult")),
    _density_mult(declareProperty<Real>("density_mult"))
{}

void
Air::computeQpProperties()
{

  // Paper is Morrow numerical modelling paper

  Real mobility_from_morrow = (.0382+2.9e5/760)/(1.0e4);
  Real mobility_from_jannis = 0.03;
  Real free_space_perm = 8.85e-12;
  Real ionization_from_paper = 0.35;

  _velocity_coeff[_qp] = _velocity_multiplier*mobility_from_jannis;
  _permittivity[_qp] = free_space_perm*_relative_permittivity;
  _coulomb_charge[_qp] = 1.6e-19;
  _ionization_coeff[_qp] = _ionization_multiplier*ionization_from_paper;
  _ion_activation_energy[_qp] = 1.65e7; // From Morrow paper
  _potential_mult[_qp] = _user_potential_mult;
  _density_mult[_qp] = _user_density_mult;
}
