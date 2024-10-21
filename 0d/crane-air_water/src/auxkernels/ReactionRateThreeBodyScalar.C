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

#include "ReactionRateThreeBodyScalar.h"

registerMooseObject("CraneApp", ReactionRateThreeBodyScalar);

template <>
InputParameters
validParams<ReactionRateThreeBodyScalar>()
{
  InputParameters params = validParams<AuxScalarKernel>();
  params.addRequiredCoupledVar("v", "The first variable that is reacting to create u.");
  params.addRequiredCoupledVar("w", "The second variable that is reacting to create u.");
  params.addRequiredCoupledVar("z", "The second variable that is reacting to create u.");
  params.addCoupledVar("rate_coefficient", 0, "Coupled reaction coefficient (if equation-based).");
  params.addRequiredParam<Real>("coefficient", "The stoichiometric coeffient.");
  return params;
}

ReactionRateThreeBodyScalar::ReactionRateThreeBodyScalar(const InputParameters & parameters)
  : AuxScalarKernel(parameters),
    _v(coupledScalarValue("v")),
    _w(coupledScalarValue("w")),
    _z(coupledScalarValue("z")),
    _rate_coefficient(coupledScalarValue("rate_coefficient")),
    _stoichiometric_coeff(getParam<Real>("coefficient"))
{
}

Real
ReactionRateThreeBodyScalar::computeValue()
{
  return _stoichiometric_coeff * _rate_coefficient[_i] * _v[_i] * _w[_i] * _z[_i];
}
