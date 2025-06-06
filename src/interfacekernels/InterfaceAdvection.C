//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "InterfaceAdvection.h"

registerMooseObject("ZapdosApp", InterfaceAdvection);

InputParameters
InterfaceAdvection::validParams()
{
  InputParameters params = ADInterfaceKernel::validParams();
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addRequiredParam<Real>("neighbor_position_units",
                                "The units of position in the neighboring domain.");
  params.addParam<std::string>(
      "neighbor_field_property_name",
      "field_solver_interface_property",
      "Name of the solver interface material property on the neighbor side of the interface.");
  params.addClassDescription(
      "Used to include the electric field driven advective flux of a species "
      "into or out of a neighboring subdomain.");
  return params;
}

InterfaceAdvection::InterfaceAdvection(const InputParameters & parameters)
  : ADInterfaceKernel(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _r_neighbor_units(1. / getParam<Real>("neighbor_position_units")),

    _electric_field_neighbor(getNeighborADMaterialProperty<RealVectorValue>(
        getParam<std::string>("neighbor_field_property_name"))),

    _mu_neighbor(getNeighborADMaterialProperty<Real>("mu" + _neighbor_var.name())),
    _sgn_neighbor(getNeighborMaterialProperty<Real>("sgn" + _neighbor_var.name()))
{
}

ADReal
InterfaceAdvection::computeQpResidual(Moose::DGResidualType type)
{
  ADReal r = 0;

  switch (type)
  {
    case Moose::Element:
      r = _mu_neighbor[_qp] * _sgn_neighbor[_qp] * _electric_field_neighbor[_qp] *
          _r_neighbor_units * std::exp(_neighbor_value[_qp]) * _normals[_qp] * _test[_i][_qp] *
          _r_units;
      break;

    case Moose::Neighbor:
      r = 0.;
      break;
  }

  return r;
}
