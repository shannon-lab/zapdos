//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "InterfaceDiffusionTest.h"

// MOOSE includes
#include "MooseVariable.h"

#include <cmath>

registerMooseObject("ZapdosApp", InterfaceDiffusionTest);

InputParameters
InterfaceDiffusionTest::validParams()
{
  InputParameters params = ADInterfaceKernel::validParams();
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addRequiredParam<Real>("neighbor_position_units",
                                "The units of position in the neighboring domain.");
  params.addRequiredParam<Real>("h", "Henry's coefficient for this species.");
  params.addClassDescription(
      "Used to include the diffusive flux of species into or out of a neighboring"
      "subdomain. Currently specific to electrons.");
  return params;
}

InterfaceDiffusionTest::InterfaceDiffusionTest(const InputParameters & parameters)
  : ADInterfaceKernel(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _r_neighbor_units(1. / getParam<Real>("neighbor_position_units")),
    _henry_coeff(getParam<Real>("h")),

    _diff(getADMaterialProperty<Real>("diff" + _var.name())),
    _diff_neighbor(getNeighborADMaterialProperty<Real>("diff" + _neighbor_var.name()))
{
  if (!parameters.isParamValid("boundary"))
  {
    mooseError("In order to use the InterfaceDiffusionTest dgkernel, you must specify a "
               "boundary where it will live.");
  }
}

ADReal
InterfaceDiffusionTest::computeQpResidual(Moose::DGResidualType type)
{
  ADReal r = 0;
  switch (type)
  {
    case Moose::Element:
      r = _test[_i][_qp] * -_diff_neighbor[_qp] * std::exp(_neighbor_value[_qp]) *
          _grad_neighbor_value[_qp] * _normals[_qp];
      break;

    case Moose::Neighbor:
      r = _test_neighbor[_i][_qp] * _diff[_qp] * std::exp(_u[_qp]) * _grad_u[_qp] * _normals[_qp];
      break;
  }

  return r;
}
