//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "Position.h"

registerMooseObject("ZapdosApp", Position);

template <>
InputParameters
validParams<Position>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addClassDescription(
      "Produces an elemental auxiliary variable useful for plotting against other"
      "elemental auxiliary variables. Mesh points automatically output by Zapdos only work"
      "for plotting nodal variables. Since almost all auxiliary variables are elemental, this"
      "AuxKernel is very important");
  return params;
}

Position::Position(const InputParameters & parameters)
  : AuxKernel(parameters), _r_units(1. / getParam<Real>("position_units"))
{
}

Real
Position::computeValue()
{
  if (isNodal())
    return (*_current_node)(0) / _r_units;
  else
    return _q_point[_qp](0) / _r_units;
}
