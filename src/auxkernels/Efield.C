//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "Efield.h"

registerMooseObject("ZapdosApp", Efield);

InputParameters
Efield::validParams()
{
  InputParameters params = AuxKernel::validParams();

  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addRequiredParam<std::string>("potential_units", "The potential units.");
  params.addRequiredParam<int>("component",
                               "The component of the electric field to access. Accepts an integer");
  params.addParam<std::string>("field_property_name",
                               "field_solver_interface_property",
                               "Name of the solver interface material property.");
  params.addClassDescription(
      "Returns the defined component of the electric field (0 = x, 1 = y, 2 = z)");
  return params;
}

Efield::Efield(const InputParameters & parameters)
  : AuxKernel(parameters),

    _component(getParam<int>("component")),
    _r_units(1. / getParam<Real>("position_units")),
    _potential_units(getParam<std::string>("potential_units")),
    _electric_field(
        getADMaterialProperty<RealVectorValue>(getParam<std::string>("field_property_name")))
{
  if (_potential_units.compare("V") == 0)
    _voltage_scaling = 1.;
  else if (_potential_units.compare("kV") == 0)
    _voltage_scaling = 1000;
}

Real
Efield::computeValue()
{
  return MetaPhysicL::raw_value(_electric_field[_qp](_component)) * _r_units * _voltage_scaling;
}
