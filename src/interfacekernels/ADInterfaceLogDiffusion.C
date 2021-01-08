//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ADInterfaceLogDiffusion.h"

// MOOSE includes
#include "MooseVariable.h"

#include <cmath>

registerMooseObject("ZapdosApp", ADInterfaceLogDiffusion);

InputParameters
ADInterfaceLogDiffusion::validParams()
{
  InputParameters params = ADInterfaceKernel::validParams();
  /*
  params.addRequiredCoupledVar("mean_en_neighbor",
                               "The log of the product of the mean energy and "
                               "electron density on the slave side of the "
                               "interface.");
                               */
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addRequiredParam<Real>("neighbor_position_units",
                                "The units of position in the neighboring domain.");
  params.addClassDescription(
      "Used to include the diffusive flux of species into or out of a neighboring"
      "subdomain. Currently specific to electrons.");
  return params;
}

ADInterfaceLogDiffusion::ADInterfaceLogDiffusion(const InputParameters & parameters)
  : ADInterfaceKernel(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _r_neighbor_units(1. / getParam<Real>("neighbor_position_units")),

    _diffem(getNeighborADMaterialProperty<Real>("diffem"))
    //_mean_en_neighbor_var(*getVar("mean_en_neighbor", 0)),
    //_mean_en_neighbor(_mean_en_neighbor_var.slnNeighbor())
{
  if (!parameters.isParamValid("boundary"))
  {
    mooseError("In order to use the ADInterfaceLogDiffusion dgkernel, you must specify a "
               "boundary where it will live.");
  }
}

ADReal
ADInterfaceLogDiffusion::computeQpResidual(Moose::DGResidualType type)
{
  // if (_diffem[_qp] < std::numeric_limits<double>::epsilon())
  //   mooseError("It doesn't appear that DG material properties got passed.");

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
