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
  params.addParam<Real>("velocity_multiplier", 1.0, "This multiplies the velocity coefficient in case you want to modify the magnitude of the convection term.");
  params.addParam<Real>("relative_permittivity", 1.0, "Multiplies the permittivity of free space.");

  return params;
}


Air::Air(const std::string & name, InputParameters parameters) :
    Material(name, parameters),

    // Get parameters from the input file
    _velocity_multiplier(getParam<Real>("velocity_multiplier")),
    _relative_permittivity(getParam<Real>("relative_permittivity")),

    // Declare material properties.  This returns references that we
    // hold onto as member variables
    _velocity_coeff(declareProperty<Real>("velocity_coeff")),
    _permittivity(declareProperty<Real>("permittivity")),
    _coulomb_charge(declareProperty<Real>("coulomb_charge"))
{}

void
Air::computeQpProperties()
{
  _velocity_coeff[_qp] = _velocity_multiplier*(.0382+2.9e5/760);
  _permittivity[_qp] = 8.85e-12*_relative_permittivity;
  _coulomb_charge[_qp] = 1.6e-19;
}
