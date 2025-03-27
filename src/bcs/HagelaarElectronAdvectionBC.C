//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "HagelaarElectronAdvectionBC.h"

registerMooseObject("ZapdosApp", HagelaarElectronAdvectionBC);

InputParameters
HagelaarElectronAdvectionBC::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  params.addRequiredParam<Real>("r", "The reflection coefficient");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addParam<std::string>("field_property_name",
                               "field_solver_interface_property",
                               "Name of the solver interface material property.");
  params.addClassDescription("Kinetic advective electron boundary condition"
                             " (Based on [!cite](hagelaar2000boundary))");
  return params;
}

HagelaarElectronAdvectionBC::HagelaarElectronAdvectionBC(const InputParameters & parameters)
  : ADIntegratedBC(parameters),

    _r_units(1. / getParam<Real>("position_units")),
    _r(getParam<Real>("r")),

    _muem(getADMaterialProperty<Real>("muem")),
    _a(0.5),

    _electric_field(
        getADMaterialProperty<RealVectorValue>(getParam<std::string>("field_property_name")))
{
}

ADReal
HagelaarElectronAdvectionBC::computeQpResidual()
{
  if (_normals[_qp] * -1.0 * _electric_field[_qp] > 0.0)
  {
    _a = 1.0;
  }
  else
  {
    _a = 0.0;
  }

  return _test[_i][_qp] * _r_units * (1. - _r) / (1. + _r) *
         (-(2 * _a - 1) * _muem[_qp] * _electric_field[_qp] * _r_units * std::exp(_u[_qp]) *
          _normals[_qp]);
}
