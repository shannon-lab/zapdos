//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "HphiRadialInterface.h"

registerMooseObject("ZapdosApp", HphiRadialInterface);

InputParameters
HphiRadialInterface::validParams()
{
  InputParameters params = ADInterfaceKernel::validParams();
  return params;
}

HphiRadialInterface::HphiRadialInterface(const InputParameters & parameters)
  : ADInterfaceKernel(parameters),
    _eps_r_neighbor(getNeighborADMaterialProperty<Real>("eps_r")),
    _eps_r(getADMaterialProperty<Real>("eps_r"))
{
  if (!parameters.isParamValid("boundary"))
  {
    mooseError("In order to use the HphiRadialInterface interface kernel, you must specify a "
               "boundary where it will live.");
  }
}

ADReal
HphiRadialInterface::computeQpResidual(Moose::DGResidualType type)
{
  ADReal r = 0;

  switch (type)
  {
    case Moose::Element:
      r = _test[_i][_qp] * _eps_r[_qp] / _eps_r_neighbor[_qp] *
              (_grad_neighbor_value[_qp] * _normals[_qp] +
               _neighbor_value[_qp] / _q_point[_qp](0)) -
          _test[_i][_qp] * _neighbor_value[_qp] / _q_point[_qp](0);
      break;

    case Moose::Neighbor:
      r = 0.;
      break;
  }

  return r;
}
