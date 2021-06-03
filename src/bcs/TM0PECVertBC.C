//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "TM0PECVertBC.h"

registerMooseObject("ZapdosApp", TM0PECVertBC);

InputParameters
TM0PECVertBC::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  return params;
}

TM0PECVertBC::TM0PECVertBC(const InputParameters & parameters) : ADIntegratedBC(parameters) {}

ADReal
TM0PECVertBC::computeQpResidual()
{
  return _test[_i][_qp] * (-_u[_qp] / _q_point[_qp](0));
}
