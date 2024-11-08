//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "EffectiveEField.h"

registerADMooseObject("ZapdosApp", EffectiveEField);


InputParameters
EffectiveEField::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addRequiredParam<Real>("nu", "The momentum-transfer frequency of the ion.");
  params.addRequiredParam<unsigned>("component", "The Efield component that this is applied to.");
  params.addParam<std::string>("field_property_name",
                               "field_solver_interface_property",
                               "Name of the solver interface material property.");
  params.addClassDescription("Supplies the source term of the time derivative calculation of the effective electric field for ions.");
  return params;
}

EffectiveEField::EffectiveEField(const InputParameters & parameters)
  : ADKernel(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _nu(getParam<Real>("nu")),
    _component(getParam<unsigned>("component")),
    _electric_field(
        getADMaterialProperty<RealVectorValue>(getParam<std::string>("field_property_name")))
{
}

ADReal
EffectiveEField::computeQpResidual()
{
  return -_test[_i][_qp] * _nu * (_electric_field[_qp](_component) - _u[_qp]);
}
