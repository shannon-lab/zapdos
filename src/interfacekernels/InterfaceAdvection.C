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
  params.addRequiredCoupledVar("potential_neighbor",
                               "The potential on the slave side of the interface.");
  params.addRequiredCoupledVar("mean_en_neighbor",
                               "The log of the product of the mean energy and "
                               "electron density on the slave side of the "
                               "interface.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addRequiredParam<Real>("neighbor_position_units",
                                "The units of position in the neighboring domain.");
  params.addClassDescription(
      "Used to include the electric field driven advective flux of species"
      "into or out of a neighboring subdomain. Currently this interface kernel"
      "is specific to electrons because the transport coefficients are assumed"
      "to be a function of the mean electron energy. A generic interface"
      "kernel with constant transport coefficients will have a much simpler Jacobian");
  return params;
}

InterfaceAdvection::InterfaceAdvection(const InputParameters & parameters)
  : ADInterfaceKernel(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _r_neighbor_units(1. / getParam<Real>("neighbor_position_units")),

    _potential_neighbor_var(*getVar("potential_neighbor", 0)),
    _grad_potential_neighbor(_potential_neighbor_var.adGradSlnNeighbor()),
    _mean_en_neighbor_var(*getVar("mean_en_neighbor", 0)),
    _mean_en_neighbor(_mean_en_neighbor_var.adSlnNeighbor()),

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
      r = _mu_neighbor[_qp] * _sgn_neighbor[_qp] * -_grad_potential_neighbor[_qp] *
          _r_neighbor_units * std::exp(_neighbor_value[_qp]) * _normals[_qp] * _test[_i][_qp] *
          _r_units;
      break;

    case Moose::Neighbor:
      r = 0.;
      break;
  }

  return r;
}
