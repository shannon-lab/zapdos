//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ElectronTemperatureDirichletBC.h"

registerMooseObject("ZapdosApp", ElectronTemperatureDirichletBC);

InputParameters
ElectronTemperatureDirichletBC::validParams()
{
  InputParameters params = ADNodalBC::validParams();
  params.addRequiredParam<Real>("value", "Value of the BC");
  params.addRequiredCoupledVar("electrons", "The electron density in log form");
  params.addParam<Real>("penalty_value", 1.0, "The penalty value for the Dirichlet BC.");
  params.addClassDescription("Electron temperature boundary condition");
  return params;
}

ElectronTemperatureDirichletBC::ElectronTemperatureDirichletBC(const InputParameters & parameters)
  : ADNodalBC(parameters),
    _em(adCoupledValue("electrons")),
    _value(getParam<Real>("value")),
    _penalty_value(getParam<Real>("penalty_value"))
{
}

ADReal
ElectronTemperatureDirichletBC::computeQpResidual()
{
  return _penalty_value * (2.0 / 3 * std::exp(_u - _em[_qp]) - _value);
}
