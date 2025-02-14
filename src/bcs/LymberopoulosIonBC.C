//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "LymberopoulosIonBC.h"

registerMooseObject("ZapdosApp", LymberopoulosIonBC);

InputParameters
LymberopoulosIonBC::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addParam<std::string>("field_property_name",
                               "field_solver_interface_property",
                               "Name of the solver interface material property.");
  params.addClassDescription("Simpified kinetic ion boundary condition"
                             " (Based on [!cite](Lymberopoulos1993))");
  return params;
}

LymberopoulosIonBC::LymberopoulosIonBC(const InputParameters & parameters)
  : ADIntegratedBC(parameters),

    _r_units(1. / getParam<Real>("position_units")),

    _electric_field(
        getADMaterialProperty<RealVectorValue>(getParam<std::string>("field_property_name"))),

    _mu(getADMaterialProperty<Real>("mu" + _var.name()))
{
}

ADReal
LymberopoulosIonBC::computeQpResidual()
{
  return _test[_i][_qp] * _r_units * _mu[_qp] * _electric_field[_qp] * _r_units *
         std::exp(_u[_qp]) * _normals[_qp];
}
