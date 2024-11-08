//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "SakiyamaIonAdvectionWithEffEfieldBC.h"

registerMooseObject("ZapdosApp", SakiyamaIonAdvectionWithEffEfieldBC);

InputParameters
SakiyamaIonAdvectionWithEffEfieldBC::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  params.addRequiredCoupledVar("Ex", "The EField in the x-direction");
  params.addCoupledVar("Ey", 0, "The EField in the y-direction"); // only required in 2D and 3D
  params.addCoupledVar("Ez", 0, "The EField in the z-direction"); // only required in 3D
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addClassDescription("Kinetic advective ion boundary condition"
                             " (Based on [!cite](sakiyama2006corona))");
  return params;
}

SakiyamaIonAdvectionWithEffEfieldBC::SakiyamaIonAdvectionWithEffEfieldBC(const InputParameters & parameters)
  : ADIntegratedBC(parameters),

    _r_units(1. / getParam<Real>("position_units")),

    // Coupled Variables
    _Ex(adCoupledValue("Ex")),
    _Ey(adCoupledValue("Ey")),
    _Ez(adCoupledValue("Ez")),

    _mu(getADMaterialProperty<Real>("mu" + _var.name())),
    _sgn(getMaterialProperty<Real>("sgn" + _var.name())),
    _a(0.5)
{
}

ADReal
SakiyamaIonAdvectionWithEffEfieldBC::computeQpResidual()
{
  ADRealVectorValue EField(_Ex[_qp], _Ey[_qp], _Ez[_qp]);

  if (_normals[_qp] * _sgn[_qp] * EField >= 0.0)
  {
    _a = 1.0;
  }
  else
  {
    _a = 0.0;
  }

  //return _test[_i][_qp] * _r_units *
  //       (_a * _sgn[_qp] * _mu[_qp] * -_grad_potential[_qp] * _r_units * std::exp(_u[_qp]) *
  //        _normals[_qp]);

  return _test[_i][_qp] * _r_units *
         (_a * _sgn[_qp] * _mu[_qp] * EField * _r_units * std::exp(_u[_qp]) *
          _normals[_qp]);
}
