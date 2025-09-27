//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "FieldEmissionCoefficients.h"
#include "MooseUtils.h"
#include "Zapdos.h"

registerADMooseObject("ZapdosApp", FieldEmissionCoefficients);

InputParameters
FieldEmissionCoefficients::validParams()
{
  InputParameters params = ADMaterial::validParams();

  params.addParam<Real>("user_work_function", 5.00, "The work function.");
  params.addParam<Real>("user_field_enhancement", 1, "The field enhancement factor.");

  params.addParam<Real>("user_Richardson_coefficient", 1.20173E6, "The Richardson coefficient.");
  params.addParam<Real>("user_cathode_temperature", 300, "The cathode temperature in Kelvin.");

  params.addClassDescription("The material coefficients for field emission");
  return params;
}

FieldEmissionCoefficients::FieldEmissionCoefficients(const InputParameters & parameters)
  : ADMaterial(parameters),
    _user_work_function(getParam<Real>("user_work_function")),
    _user_field_enhancement(getParam<Real>("user_field_enhancement")),

    _user_Richardson_coefficient(getParam<Real>("user_Richardson_coefficient")),
    _user_cathode_temperature(getParam<Real>("user_cathode_temperature")),

    _work_function(declareProperty<Real>("work_function")),
    _field_enhancement(declareProperty<Real>("field_enhancement")),

    _Richardson_coefficient(declareProperty<Real>("Richardson_coefficient")),
    _cathode_temperature(declareProperty<Real>("cathode_temperature"))
{
}

void
FieldEmissionCoefficients::computeQpProperties()
{
  _work_function[_qp] = _user_work_function;
  _field_enhancement[_qp] = _user_field_enhancement;

  _Richardson_coefficient[_qp] = _user_Richardson_coefficient;
  _cathode_temperature[_qp] = _user_cathode_temperature;
}
