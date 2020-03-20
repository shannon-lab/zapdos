//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ADDCIonBC.h"

// MOOSE includes
#include "MooseVariable.h"

registerADMooseObject("ZapdosApp", ADDCIonBC);

defineADLegacyParams(ADDCIonBC);

template <ComputeStage compute_stage>
InputParameters
ADDCIonBC<compute_stage>::validParams()
{
  InputParameters params = ADIntegratedBC<compute_stage>::validParams();
  params.addRequiredCoupledVar("potential", "The electric potential");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addClassDescription("Electric field driven outflow boundary condition"
                             "(Based on DOI:https://doi.org/10.1103/PhysRevE.62.1452)");
  return params;
}

template <ComputeStage compute_stage>
ADDCIonBC<compute_stage>::ADDCIonBC(const InputParameters & parameters)
  : ADIntegratedBC<compute_stage>(parameters),

    _r_units(1. / getParam<Real>("position_units")),

    // Coupled Variables
    _grad_potential(adCoupledGradient("potential")),

    _mu(getADMaterialProperty<Real>("mu" + _var.name())),
    _sgn(getADMaterialProperty<Real>("sgn" + _var.name()))
{
  _a = 0.0;
}

template <ComputeStage compute_stage>
ADReal
ADDCIonBC<compute_stage>::computeQpResidual()
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
         (_a * _mu[_qp] * _sgn[_qp] * -_grad_potential[_qp] * _r_units * std::exp(_u[_qp]) *
          _normals[_qp]);
}
