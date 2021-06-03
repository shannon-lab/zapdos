//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "FieldEmissionBC.h"

registerMooseObject("ZapdosApp", FieldEmissionBC);

InputParameters
FieldEmissionBC::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  params.addRequiredParam<Real>("r", "The reflection coefficient");
  params.addRequiredCoupledVar("potential", "The electric potential");
  params.addRequiredCoupledVar("mean_en", "The mean energy.");
  params.addRequiredCoupledVar("ip", "The ion density.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addRequiredParam<std::string>("potential_units", "The potential units.");
  params.addParam<Real>("tau", 1e-9, "The time constant for ramping the boundary condition.");
  params.addParam<bool>("relax", false, "Use relaxation for emission.");
  return params;
}

FieldEmissionBC::FieldEmissionBC(const InputParameters & parameters)
  : ADIntegratedBC(parameters),

    _r_units(1. / getParam<Real>("position_units")),
    _r(getParam<Real>("r")),

    // Coupled Variables
    _grad_potential(adCoupledGradient("potential")),
    _mean_en(adCoupledValue("mean_en")),
    _ip_var(*getVar("ip", 0)),
    _ip(adCoupledValue("ip")),
    _grad_ip(adCoupledGradient("ip")),

    _muem(getADMaterialProperty<Real>("muem")),
    _massem(getMaterialProperty<Real>("massem")),
    _e(getMaterialProperty<Real>("e")),
    _sgnip(getMaterialProperty<Real>("sgn" + _ip_var.name())),
    _muip(getADMaterialProperty<Real>("mu" + _ip_var.name())),
    _Dip(getADMaterialProperty<Real>("diff" + _ip_var.name())),
    _se_coeff(getMaterialProperty<Real>("se_coeff")),
    _work_function(getMaterialProperty<Real>("work_function")),
    _field_enhancement(getMaterialProperty<Real>("field_enhancement")),
    _a(0.5),
    _ion_flux(0, 0, 0),
    _tau(getParam<Real>("tau")),
    _relax(getParam<bool>("relax")),
    _potential_units(getParam<std::string>("potential_units"))
{
  if (_potential_units.compare("V") == 0)
  {
    _voltage_scaling = 1.;
  }
  else if (_potential_units.compare("kV") == 0)
  {
    _voltage_scaling = 1000;
  }

  FE_a = 1.541434E-6 * std::pow(_voltage_scaling, 2); // A eV/kV^2 (if _voltage_scaling == 1000)
  FE_b = 6.830890E9 / _voltage_scaling;          // kV/m-eV^1.5 (if _voltage_scaling == 1000)
  FE_c = 1.439964E-9 * _voltage_scaling;         // eV^2*m/kV (if _voltage_scaling == 1000)
}

ADReal
FieldEmissionBC::computeQpResidual()
{
  ADReal v;
  ADReal f;
  ADReal jFE;
  ADReal jSE;
  ADReal F;
  Real _relaxation_Expr;

  if (_normals[_qp] * -1.0 * -_grad_potential[_qp] > 0.0)
  {
    _a = 1.0;
    return 0;
  }
  else
  {
    _a = 0.0;

    _ion_flux = _sgnip[_qp] * _muip[_qp] * -_grad_potential[_qp] * _r_units * std::exp(_ip[_qp]) -
                _Dip[_qp] * std::exp(_ip[_qp]) * _grad_ip[_qp] * _r_units;

    // Fowler-Nordheim
    // jFE = (a / wf) * F^2 * exp(-v(f) * b * wf^1.5 / F)
    // a = 1.541434E-6 A eV/V^2
    // b = 6.830890E9 V/m-eV^1.5
    // c = 1.439964E-9 eV^2-m/V
    // v(f) = 1 - f + (f/6)*ln(f)
    // f = c*(F/wf^2)

    F = -(1 - _a) * _field_enhancement[_qp] * _normals[_qp] * _grad_potential[_qp] * _r_units;

    f = FE_c * F / std::pow(_work_function[_qp], 2);
    v = 1 - f + (f / 6) * std::log(f);

    jFE = (FE_a / (_work_function[_qp])) * std::pow(F, 2) *
          std::exp(-v * FE_b * std::pow(_work_function[_qp], 1.5) / F);
    jSE = _e[_qp] * 6.02E23 * _se_coeff[_qp] * _ion_flux * _normals[_qp];

    if (_relax == true)
      _relaxation_Expr = std::tanh(_t / _tau);
    else
      _relaxation_Expr = 1.0;

    return _relaxation_Expr * _test[_i][_qp] * _r_units * 2. / (1. + _r) * (1 - _a) * (-jFE - jSE) /
           (_e[_qp] * 6.02E23);
  }
}
