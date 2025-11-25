//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "LogDensityDirichletBC.h"

registerMooseObject("ZapdosApp", LogDensityDirichletBC);

InputParameters
LogDensityDirichletBC::validParams()
{
  InputParameters params = ADNodalBC::validParams();
  params.addRequiredParam<Real>("value", "Value of the BC");
  params.addClassDescription("Density Dirichlet boundary condition"
                             " (Densities must be in log form and in moles/m$^3$)");
  return params;
}

LogDensityDirichletBC::LogDensityDirichletBC(const InputParameters & parameters)
  : ADNodalBC(parameters), _value(getParam<Real>("value"))
{
}

ADReal
LogDensityDirichletBC::computeQpResidual()
{
  using std::exp;
  return (exp(_u) * 6.022e23) - _value;
}
