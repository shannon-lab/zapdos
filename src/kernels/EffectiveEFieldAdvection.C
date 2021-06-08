//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "EffectiveEFieldAdvection.h"

registerADMooseObject("ZapdosApp", EffectiveEFieldAdvection);

InputParameters
EffectiveEFieldAdvection::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addRequiredCoupledVar("u", "x-Effective Efield");
  params.addCoupledVar("v", 0, "y-Effective Efield"); // only required in 2D and 3D
  params.addCoupledVar("w", 0, "z-Effective Efield"); // only required in 3D
  params.addRequiredParam<Real>("position_units", "Units of position.");
  return params;
}

EffectiveEFieldAdvection::EffectiveEFieldAdvection(const InputParameters & parameters)
  : ADKernel(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _mu(getADMaterialProperty<Real>("mu" + _var.name())),
    _sign(getMaterialProperty<Real>("sgn" + _var.name())),
    _u_Efield(adCoupledValue("u")),
    _v_Efield(adCoupledValue("v")),
    _w_Efield(adCoupledValue("w"))
{
}

ADReal
EffectiveEFieldAdvection::computeQpResidual()
{
  ADRealVectorValue Efield(_u_Efield[_qp], _v_Efield[_qp], _w_Efield[_qp]);

  return _mu[_qp] * _sign[_qp] * std::exp(_u[_qp]) * Efield * _r_units *
         -_grad_test[_i][_qp] * _r_units;
}
