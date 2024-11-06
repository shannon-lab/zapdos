//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "SakiyamaIonAdvectionBC.h"

registerMooseObject("ZapdosApp", SakiyamaIonAdvectionBC);

InputParameters
SakiyamaIonAdvectionBC::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  params.addRequiredCoupledVar("potential", "The electric potential");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addClassDescription("Kinetic advective ion boundary condition"
                             " (Based on [!cite](sakiyama2006corona))");
  return params;
}

SakiyamaIonAdvectionBC::SakiyamaIonAdvectionBC(const InputParameters & parameters)
  : ADIntegratedBC(parameters),

    _r_units(1. / getParam<Real>("position_units")),

    // Coupled Variables
    _grad_potential(adCoupledGradient("potential")),

    _mu(getADMaterialProperty<Real>("mu" + _var.name())),
    _sgn(getMaterialProperty<Real>("sgn" + _var.name())),
    _a(0.5)
{
}

ADReal
SakiyamaIonAdvectionBC::computeQpResidual()
{
  if (_normals[_qp] * _sgn[_qp] * -_grad_potential[_qp] > 0.0)
  {
    _a = 1.0;
  }
  else
  {
    _a = 0.0;
  }

  return _test[_i][_qp] * _r_units *
         (_a * _sgn[_qp] * _mu[_qp] * -_grad_potential[_qp] * _r_units * std::exp(_u[_qp]) *
          _normals[_qp]);
}
