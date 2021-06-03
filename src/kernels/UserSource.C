//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "UserSource.h"

registerMooseObject("ZapdosApp", UserSource);

InputParameters
UserSource::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addRequiredParam<Real>("source_magnitude", "The numerical value of the source magnitude.");
  params.addClassDescription("User defined source term");
  return params;
}

UserSource::UserSource(const InputParameters & parameters)
  : ADKernel(parameters), _source(getParam<Real>("source_magnitude"))
{
}

ADReal
UserSource::computeQpResidual()
{
  return -_test[_i][_qp] * _source;
}
