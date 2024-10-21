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

#include "VariableSum.h"

registerMooseObject("CraneApp", VariableSum);

template <>
InputParameters
validParams<VariableSum>()
{
  InputParameters params = validParams<AuxScalarKernel>();
  params.addCoupledVar("args", "The variables to sum.");
  return params;
}

VariableSum::VariableSum(const InputParameters & parameters)
  : AuxScalarKernel(parameters),
    _nargs(coupledScalarComponents("args")),
    _args(_nargs)
{
}

Real
VariableSum::computeValue()
{
  Real variable_sum = 0;
  for (unsigned int i = 0; i < _nargs; ++i)
  {
    // variables += (i == 0 ? "" : ",") + getScalarVar("args", i)->name();
    // _args[i] = &coupledScalarValue("args", i);
    // std::cout << (*_args[i])[_i] << std::endl;
    variable_sum += coupledScalarValue("args", i)[_i];
  }
  return variable_sum;
}
