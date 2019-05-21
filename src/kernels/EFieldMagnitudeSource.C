//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "EFieldMagnitudeSource.h"

registerMooseObject("ZapdosApp", EFieldMagnitudeSource);

template <>
InputParameters
validParams<EFieldMagnitudeSource>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("potential", "The electric potential.");
  return params;
}

EFieldMagnitudeSource::EFieldMagnitudeSource(const InputParameters & parameters)
  : Kernel(parameters),
    _grad_potential(coupledGradient("potential")),
    _potential_id(coupled("potential"))
{
}

EFieldMagnitudeSource::~EFieldMagnitudeSource() {}

Real
EFieldMagnitudeSource::computeQpResidual()
{
  return -_test[_i][_qp] * _grad_potential[_qp] * _grad_potential[_qp];
}

Real
EFieldMagnitudeSource::computeQpJacobian()
{
  return 0.;
}

Real
EFieldMagnitudeSource::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id)
    return -_test[_i][_qp] * 2. * _grad_potential[_qp] * _grad_phi[_j][_qp];

  else
    return 0.;
}
