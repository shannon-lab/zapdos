//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "AnalyticalDiffIndicator.h"
#include "Function.h"

registerMooseObject("ZapdosApp", AnalyticalDiffIndicator);

InputParameters
AnalyticalDiffIndicator::validParams()
{
  InputParameters params = ElementIntegralIndicator::validParams();
  params.addRequiredParam<FunctionName>("function", "The analytic solution to compare against");
  params.addClassDescription("Returns the difference between the function of the analytic solution "
                             "vs the computed solution");
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
