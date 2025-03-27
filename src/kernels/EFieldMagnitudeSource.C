//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "EFieldMagnitudeSource.h"

registerMooseObject("ZapdosApp", EFieldMagnitudeSource);

InputParameters
EFieldMagnitudeSource::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addParam<std::string>("field_property_name",
                               "field_solver_interface_property",
                               "Name of the solver interface material property.");
  params.addClassDescription("Electric field magnitude source term");
  return params;
}

EFieldMagnitudeSource::EFieldMagnitudeSource(const InputParameters & parameters)
  : ADKernel(parameters),
    _electric_field(
        getADMaterialProperty<RealVectorValue>(getParam<std::string>("field_property_name")))
{
}

ADReal
EFieldMagnitudeSource::computeQpResidual()
{
  return -_test[_i][_qp] * _electric_field[_qp].norm();
}
