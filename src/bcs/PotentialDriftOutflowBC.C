//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "PotentialDriftOutflowBC.h"

registerMooseObject("ZapdosApp", PotentialDriftOutflowBC);

InputParameters
PotentialDriftOutflowBC::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  MooseEnum charge_sign("positive=1 negative=-1", "positive");
  params.addRequiredCoupledVar(
      "potential", "The gradient of the potential will be used to compute the advection velocity.");
  params.addRequiredCoupledVar(
      "potential", "The gradient of the potential will be used to compute the advection velocity.");

  params.addParam<MooseEnum>("charge_sign", charge_sign, "The sign of the charged particle.");
  params.addClassDescription("The drift flux boundary condition");
  return params;
}

PotentialDriftOutflowBC::PotentialDriftOutflowBC(const InputParameters & parameters)
  : ADIntegratedBC(parameters),
    _charge_sign(getParam<MooseEnum>("charge_sign")),
    _grad_potential(adCoupledGradient("potential"))
{
}

ADReal
PotentialDriftOutflowBC::computeQpResidual()
{
  if (_charge_sign * -_grad_potential[_qp] * _normals[_qp] > 0.)
    return _charge_sign * -_grad_potential[_qp] * _normals[_qp] * _u[_qp];
  else
    return 0.;
}
