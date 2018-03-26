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

#include "AnalyticalDiffIndicator.h"
#include "Function.h"

registerMooseObject("ZapdosApp", AnalyticalDiffIndicator);

template <>
InputParameters
validParams<AnalyticalDiffIndicator>()
{
  InputParameters params = validParams<ElementIntegralIndicator>();
  params.addRequiredParam<FunctionName>("function", "The analytic solution to compare against");
  return params;
}

AnalyticalDiffIndicator::AnalyticalDiffIndicator(const InputParameters & parameters)
  : ElementIntegralIndicator(parameters), _func(getFunction("function"))
{
}

Real
AnalyticalDiffIndicator::computeQpIntegral()
{
  Real diff = _u[_qp] - _func.value(_t, _q_point[_qp]);
  return diff;
}
