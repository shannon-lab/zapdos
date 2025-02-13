//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "InterfaceLogDiffusionElectrons.h"

registerMooseObject("ZapdosApp", InterfaceLogDiffusionElectrons);

InputParameters
InterfaceLogDiffusionElectrons::validParams()
{
  InputParameters params = ADInterfaceKernel::validParams();
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addRequiredParam<Real>("neighbor_position_units",
                                "The units of position in the neighboring domain.");
  params.addClassDescription(
      "Used to include the diffusive flux of species into or out of a neighboring"
      "subdomain. Currently specific to electrons.");
  return params;
}

InterfaceLogDiffusionElectrons::InterfaceLogDiffusionElectrons(const InputParameters & parameters)
  : ADInterfaceKernel(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _r_neighbor_units(1. / getParam<Real>("neighbor_position_units")),

    _diffem(getNeighborADMaterialProperty<Real>("diffem"))
{
  if (!parameters.isParamValid("boundary"))
  {
    mooseError("In order to use the InterfaceLogDiffusionElectrons dgkernel, you must specify a "
               "boundary where it will live.");
  }
}

ADReal
InterfaceLogDiffusionElectrons::computeQpResidual(Moose::DGResidualType type)
{
  ADReal r = 0;

  switch (type)
  {
    case Moose::Element:
      r = -_diffem[_qp] * std::exp(_neighbor_value[_qp]) * _grad_neighbor_value[_qp] *
          _r_neighbor_units * _normals[_qp] * _test[_i][_qp] * _r_units;
      break;

    case Moose::Neighbor:
      r = 0.;
      break;
  }

  return r;
}
