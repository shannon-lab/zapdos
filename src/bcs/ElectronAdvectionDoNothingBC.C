//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ElectronAdvectionDoNothingBC.h"

registerMooseObject("ZapdosApp", ElectronAdvectionDoNothingBC);

InputParameters
ElectronAdvectionDoNothingBC::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  params.addRequiredParam<Real>("position_units", "The units of position.");
  params.addParam<std::string>("field_property_name",
                               "field_solver_interface_property",
                               "Name of the solver interface material property.");
  params.addClassDescription("Boundary condition where the electron advection flux at the boundary "
                             "is equal to the bulk electron advection equation");
  return params;
}

ElectronAdvectionDoNothingBC::ElectronAdvectionDoNothingBC(const InputParameters & parameters)
  : ADIntegratedBC(parameters),

    _position_units(1. / getParam<Real>("position_units")),

    _muem(getADMaterialProperty<Real>("muem")),
    _sign(getMaterialProperty<Real>("sgnem")),

    _electric_field(
        getADMaterialProperty<RealVectorValue>(getParam<std::string>("field_property_name")))
{
}

ADReal
ElectronAdvectionDoNothingBC::computeQpResidual()
{
  return _muem[_qp] * _sign[_qp] * std::exp(_u[_qp]) * _electric_field[_qp] * _position_units *
         _normals[_qp] * _test[_i][_qp] * _position_units;
}
