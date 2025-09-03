//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "PotentialSurfaceCharge.h"

registerMooseObject("ZapdosApp", PotentialSurfaceCharge);

InputParameters
PotentialSurfaceCharge::validParams()
{
  InputParameters params = ADInterfaceKernel::validParams();
  params.addParam<Real>("position_units", 1.0, "The units of position.");
  params.addParam<Real>("neighbor_position_units", 1.0, "The units of position.");
  params.addClassDescription(
      "Enforces the dielectric boundary condition on a potential variable at an interface, "
      "where the surface charge is provided as an ADMaterialProperty.");
  return params;
}

PotentialSurfaceCharge::PotentialSurfaceCharge(const InputParameters & parameters)
  : ADInterfaceKernel(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _r_neighbor_units(1. / getParam<Real>("neighbor_position_units")),
    _D(getADMaterialProperty<Real>("diff" + _var.name())),
    _D_neighbor(getNeighborADMaterialProperty<Real>("diff" + _neighbor_var.name())),
    _sigma(getADMaterialProperty<Real>("surface_charge"))
{
}

ADReal
PotentialSurfaceCharge::computeQpResidual(Moose::DGResidualType type)
{
  ADReal r = 0;

  switch (type)
  {
    case Moose::Element:
      r = -_test[_i][_qp] * _r_units *
          (_D_neighbor[_qp] * _grad_neighbor_value[_qp] * _r_neighbor_units * _normals[_qp] +
           _sigma[_qp]);
      break;

    case Moose::Neighbor:
      r = _test_neighbor[_i][_qp] * _r_neighbor_units *
          (_D[_qp] * _grad_u[_qp] * _r_units * _normals[_qp] - _sigma[_qp]);
      break;
  }

  return r;
}
