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

#include "AuxInitialConditionScalar.h"

registerMooseObject("CraneApp", AuxInitialConditionScalar);

template <>
InputParameters
validParams<AuxInitialConditionScalar>()
{
  InputParameters params = validParams<AuxScalarKernel>();
  params.addParam<Real>("initial_condition", 0, "The initial value of the auxiliary variable.");
  return params;
}

AuxInitialConditionScalar::AuxInitialConditionScalar(const InputParameters & parameters)
  : AuxScalarKernel(parameters),
    _value(getParam<Real>("initial_condition"))
{
}

Real
AuxInitialConditionScalar::computeValue()
{
  return _value;
}
