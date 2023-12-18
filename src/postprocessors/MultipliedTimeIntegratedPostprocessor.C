//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "MultipliedTimeIntegratedPostprocessor.h"

registerMooseObject("ZapdosApp", MultipliedTimeIntegratedPostprocessor);

InputParameters
MultipliedTimeIntegratedPostprocessor::validParams()
{
  InputParameters params = GeneralPostprocessor::validParams();
  params.addClassDescription("Integrate a Postprocessor value over time using trapezoidal rule.");
  params.addParam<PostprocessorName>("value",
                                     "The name of the postprocessor you are integrating over time");
  params.addParam<Real>(
      "coefficient", 1, "The value to multiply the postprocessor by when integrating");
  return params;
}

MultipliedTimeIntegratedPostprocessor::MultipliedTimeIntegratedPostprocessor(
    const InputParameters & parameters)
  : GeneralPostprocessor(parameters),
    _value(0),
    _coeff(getParam<Real>("coefficient")),
    _value_old(getPostprocessorValueOldByName(name())),
    _pps_value(getPostprocessorValue("value")),
    _pps_value_old(getPostprocessorValueOld("value"))
{
}

void
MultipliedTimeIntegratedPostprocessor::execute()
{
  _value = _value_old + 0.5 * _coeff * (_pps_value + _pps_value_old) * _dt;
}

Real
MultipliedTimeIntegratedPostprocessor::getValue() const
{
  return _value;
}
