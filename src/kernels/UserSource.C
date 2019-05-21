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

template <>
InputParameters
validParams<UserSource>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<Real>("source_magnitude", "The numerical value of the source magnitude.");
  return params;
}

UserSource::UserSource(const InputParameters & parameters)
  : Kernel(parameters), _source(getParam<Real>("source_magnitude"))
{
}

UserSource::~UserSource() {}

Real
UserSource::computeQpResidual()
{
  return -_test[_i][_qp] * _source;
}

Real
UserSource::computeQpJacobian()
{
  return 0.;
}
