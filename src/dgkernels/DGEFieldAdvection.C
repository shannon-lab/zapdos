//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "DGEFieldAdvection.h"

registerMooseObject("ZapdosApp", DGEFieldAdvection);

InputParameters
DGEFieldAdvection::validParams()
{
  InputParameters params = ADDGKernel::validParams();
  params.addParam<std::string>(
      "field_property_name",
      "field_solver_interface_property",
      "Name of the solver interface material property on the primary side of the interface.");
  params.addParam<std::string>(
      "neighbor_field_property_name",
      "field_solver_interface_property",
      "Name of the solver interface material property on the neighbor side of the interface.");
  params.addClassDescription(
      "The discontinuous Galerkin form of the generic electric field driven advection term"
      "(Densities must be in log form)");
  return params;
}

DGEFieldAdvection::DGEFieldAdvection(const InputParameters & parameters)
  : ADDGKernel(parameters),

    _mu(getADMaterialProperty<Real>("mu" + _var.name())),
    _sgn(getMaterialProperty<Real>("sgn" + _var.name())),
    _mu_neighbor(getNeighborADMaterialProperty<Real>("mu" + _var.name())),
    _sgn_neighbor(getNeighborMaterialProperty<Real>("sgn" + _var.name())),

    _electric_field(
        getADMaterialProperty<RealVectorValue>(getParam<std::string>("field_property_name"))),
    _electric_field_neighbor(getNeighborADMaterialProperty<RealVectorValue>(
        getParam<std::string>("neighbor_field_property_name")))
{
}

ADReal
DGEFieldAdvection::computeQpResidual(Moose::DGResidualType type)
{
  ADReal r = 0;
  ADRealVectorValue _velocity = _mu[_qp] * _sgn[_qp] * _electric_field[_qp];
  ADRealVectorValue _velocity_neighbor =
      _mu_neighbor[_qp] * _sgn_neighbor[_qp] * _electric_field_neighbor[_qp];
  ADRealVectorValue _velocity_average = 0.5 * (_velocity + _velocity_neighbor);

  switch (type)
  {
    case Moose::Element:
      if ((_velocity_average * _normals[_qp]) >= 0.0)
        r += (_velocity_average * _normals[_qp]) * std::exp(_u[_qp]) * _test[_i][_qp];
      else
        r += (_velocity_average * _normals[_qp]) * std::exp(_u_neighbor[_qp]) * _test[_i][_qp];
      break;

    case Moose::Neighbor:
      if ((_velocity_average * _normals[_qp]) >= 0.0)
        r += -(_velocity_average * _normals[_qp]) * std::exp(_u[_qp]) * _test_neighbor[_i][_qp];
      else
        r += -(_velocity_average * _normals[_qp]) * std::exp(_u_neighbor[_qp]) *
             _test_neighbor[_i][_qp];
      break;
  }
  return r;
}
