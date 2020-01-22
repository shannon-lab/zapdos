//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "AbsValueAux.h"

registerMooseObject("ZapdosApp", AbsValueAux);

template <>
InputParameters
validParams<AbsValueAux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("u", "Variable we want absolute value of.");
  params.addClassDescription("Returns the absolute value of variable");
  return params;
}

AbsValueAux::AbsValueAux(const InputParameters & parameters)
  : AuxKernel(parameters), _u(coupledValue("u"))
{
}

Real
AbsValueAux::computeValue()
{
  return std::abs(_u[_qp]);
}
