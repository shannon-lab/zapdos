//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ADHagelaarEnergyBC.h"

registerADMooseObject("ZapdosApp", ADHagelaarEnergyBC);

defineADLegacyParams(ADHagelaarEnergyBC);

template <ComputeStage compute_stage>
InputParameters
ADHagelaarEnergyBC<compute_stage>::validParams()
{
  InputParameters params = ADIntegratedBC<compute_stage>::validParams();
  params.addRequiredParam<Real>("r", "The reflection coefficient");
  params.addRequiredCoupledVar("potential", "The electric potential");
  params.addRequiredCoupledVar("em", "The electron density.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  return params;
}

template <ComputeStage compute_stage>
ADHagelaarEnergyBC<compute_stage>::ADHagelaarEnergyBC(const InputParameters & parameters)
  : ADIntegratedBC<compute_stage>(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _r(getParam<Real>("r")),

    // Coupled Variables
    _grad_potential(adCoupledGradient("potential")),
    _em(adCoupledValue("em")),

    _massem(getMaterialProperty<Real>("massem")),
    _e(getMaterialProperty<Real>("e")),
    _se_coeff(getMaterialProperty<Real>("se_coeff")),
    _se_energy(getMaterialProperty<Real>("se_energy")),
    _mumean_en(getADMaterialProperty<Real>("mumean_en"))
{
  _a = 0.5;
  _v_thermal = 0.0;
}

template <ComputeStage compute_stage>
ADReal
ADHagelaarEnergyBC<compute_stage>::computeQpResidual()
{
  if (_normals[_qp] * -1.0 * -_grad_potential[_qp] > 0.0)
  {
    _a = 1.0;
  }
  else
  {
    _a = 0.0;
  }
  _v_thermal =
      std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_u[_qp] - _em[_qp]) / (M_PI * _massem[_qp]));

  return _test[_i][_qp] * _r_units * (1. - _r) / (1. + _r) *
         (-(2. * _a - 1.) * _mumean_en[_qp] * -_grad_potential[_qp] * _r_units * _normals[_qp] +
          5. / 6. * _v_thermal) *
         std::exp(_u[_qp]);
}
