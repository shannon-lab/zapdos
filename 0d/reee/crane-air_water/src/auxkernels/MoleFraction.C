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

#include "MoleFraction.h"

registerMooseObject("CraneApp", MoleFraction);

template <>
InputParameters
validParams<MoleFraction>()
{
  InputParameters params = validParams<AuxScalarKernel>();
  params.addCoupledVar("neutral_density", "The neutral gas density (calculated by VariableSum).");
  params.addCoupledVar("species_density", "The species density (nonlinear variable).");
  return params;
}

MoleFraction::MoleFraction(const InputParameters & parameters)
  : AuxScalarKernel(parameters),
    _neutral_density(coupledScalarValue("neutral_density")),
    _species_density(coupledScalarValue("species_density"))
{
}

Real
MoleFraction::computeValue()
{
  return _species_density[_i] / _neutral_density[_i];
}
