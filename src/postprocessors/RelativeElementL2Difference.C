//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "RelativeElementL2Difference.h"
#include "Function.h"

registerMooseObject("ZapdosApp", RelativeElementL2Difference);

InputParameters
RelativeElementL2Difference::validParams()
{
  InputParameters params = ElementIntegralVariablePostprocessor::validParams();
  params.addRequiredCoupledVar("other_variable", "The variable to compare to");

  params.addClassDescription("Computes the element-wise relative L2 difference between "
                             "the current variable and a coupled variable: i.e. ||u-v||/||u||");
  return params;
}

RelativeElementL2Difference::RelativeElementL2Difference(const InputParameters & parameters)
  : ElementIntegralVariablePostprocessor(parameters), _other_var(coupledValue("other_variable"))
{
}

PostprocessorValue
RelativeElementL2Difference::getValue() const
{
  return std::sqrt(ElementIntegralPostprocessor::getValue());
}

Real
RelativeElementL2Difference::computeQpIntegral()
{
  Real diff = (_u[_qp] - _other_var[_qp]) / _u[_qp];
  return diff * diff;
}
