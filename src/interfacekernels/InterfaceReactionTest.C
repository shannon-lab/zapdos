//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "InterfaceReactionTest.h"

// MOOSE includes
#include "MooseVariable.h"

#include <cmath>

registerMooseObject("ZapdosApp", InterfaceReactionTest);

InputParameters
InterfaceReactionTest::validParams()
{
  InputParameters params = ADInterfaceKernel::validParams();
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addRequiredParam<Real>("neighbor_position_units",
                                "The units of position in the neighboring domain.");
  params.addRequiredParam<Real>("kf", "Henry's coefficient for this species.");
  params.addRequiredParam<Real>("kb", "Henry's coefficient for this species. MUST BE 1");
  params.addClassDescription(
      "Used to include the diffusive flux of species into or out of a neighboring"
      "subdomain. Currently specific to electrons.");
  return params;
}

InterfaceReactionTest::InterfaceReactionTest(const InputParameters & parameters)
  : ADInterfaceKernel(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _r_neighbor_units(1. / getParam<Real>("neighbor_position_units")),
    _kf(getParam<Real>("kf")),
    _kb(getParam<Real>("kb")),

    _diff(getADMaterialProperty<Real>("diff" + _var.name())),
    _diff_neighbor(getNeighborADMaterialProperty<Real>("diff" + _neighbor_var.name()))
{
  if (!parameters.isParamValid("boundary"))
  {
    mooseError("In order to use the InterfaceReactionTest dgkernel, you must specify a "
               "boundary where it will live.");
  }
}

ADReal
InterfaceReactionTest::computeQpResidual(Moose::DGResidualType type)
{
  ADReal r = 0;

  switch (type)
  {
    case Moose::Element:
      r = _test[_i][_qp] * (_kf * std::exp(_u[_qp]) - _kb * std::exp(_neighbor_value[_qp]));
      break;

    case Moose::Neighbor:
      r = -_test_neighbor[_i][_qp] *
          (_kf * std::exp(_u[_qp]) - _kb * std::exp(_neighbor_value[_qp]));
      break;
  }

  return r;
}
