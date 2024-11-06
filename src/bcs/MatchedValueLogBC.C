//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "MatchedValueLogBC.h"

registerMooseObject("ZapdosApp", MatchedValueLogBC);

InputParameters
MatchedValueLogBC::validParams()
{
  InputParameters params = ADNodalBC::validParams();
  params.addRequiredParam<Real>("H", "The ratio of liquid phase density to gas phase density");
  params.addRequiredCoupledVar("v", "The variable whose value we are to match.");
  params.addClassDescription(
      "Henry’s Law like thermodynamic boundary condition for specifying a species"
      " concentration ratio at the gas-liquid interface");
  return params;
}

MatchedValueLogBC::MatchedValueLogBC(const InputParameters & parameters)
  : ADNodalBC(parameters), _v(adCoupledValue("v")), _H(getParam<Real>("H"))
{
}

ADReal
MatchedValueLogBC::computeQpResidual()
{
  return _H * std::exp(_u) - std::exp(_v[_qp]);
}
