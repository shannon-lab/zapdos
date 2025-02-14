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
  params.addRequiredCoupledVar("ions", "A list of ion densities in log form");
  params.addRequiredParam<std::vector<std::string>>(
      "emission_coeffs",
      "The species dependent secondary electron emission coefficients for this boundary");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addRequiredParam<std::string>("potential_units", "The potential units.");
  params.addParam<Real>("tau", 1e-9, "The time constant for ramping the boundary condition.");
  params.addParam<bool>("relax", false, "Use relaxation for emission.");
  params.addParam<std::string>("field_property_name",
                               "field_solver_interface_property",
                               "Name of the solver interface material property.");
  params.addClassDescription(
      "The electron flux boundary condition due to field emission"
      " (Based on [!cite](forbes2006simple) and [!cite](forbes2008physics))");
  return params;
}

FieldEmissionBC::FieldEmissionBC(const InputParameters & parameters)
  : ADIntegratedBC(parameters),

    _r_units(1. / getParam<Real>("position_units")),
    _r(getParam<Real>("r")),
    _num_ions(coupledComponents("ions")),

    _muem(getADMaterialProperty<Real>("muem")),
    _massem(getMaterialProperty<Real>("massem")),
    _e(getMaterialProperty<Real>("e")),
    _se_coeff_names(getParam<std::vector<std::string>>("emission_coeffs")),
    _work_function(getMaterialProperty<Real>("work_function")),
    _field_enhancement(getMaterialProperty<Real>("field_enhancement")),

    _electric_field(
        getADMaterialProperty<RealVectorValue>(getParam<std::string>("field_property_name"))),

    _a(0.5),
    _ion_flux(0, 0, 0),
    _tau(getParam<Real>("tau")),
    _relax(getParam<bool>("relax")),
    _potential_units(getParam<std::string>("potential_units"))
{

  if (_se_coeff_names.size() != _num_ions)
    mooseError("FieldEmissionBC with name ",
               name(),
               ": The lengths of `ions` and `emission_coeffs` must be the same");

  if (_potential_units.compare("V") == 0)
  {
    _voltage_scaling = 1.;
  }
  else if (_potential_units.compare("kV") == 0)
  {
    _voltage_scaling = 1000;
  }

  FE_a = 1.541434E-6 * std::pow(_voltage_scaling, 2); // A eV/kV^2 (if _voltage_scaling == 1000)
  FE_b = 6.830890E9 / _voltage_scaling;               // kV/m-eV^1.5 (if _voltage_scaling == 1000)
  FE_c = 1.439964E-9 * _voltage_scaling;              // eV^2*m/kV (if _voltage_scaling == 1000)

  _ip.resize(_num_ions);
  _ip_var.resize(_num_ions);
  _grad_ip.resize(_num_ions);
  _sgnip.resize(_num_ions);
  _muip.resize(_num_ions);
  _Dip.resize(_num_ions);
  _se_coeff.resize(_num_ions);

  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    _ip_var[i] = getVar("ions", i);
    _ip[i] = &adCoupledValue("ions", i);
    _grad_ip[i] = &adCoupledGradient("ions", i);
    _sgnip[i] = &getMaterialProperty<Real>("sgn" + (*getVar("ions", i)).name());
    _muip[i] = &getADMaterialProperty<Real>("mu" + (*getVar("ions", i)).name());
    _Dip[i] = &getADMaterialProperty<Real>("diff" + (*getVar("ions", i)).name());
    _se_coeff[i] = &getADMaterialProperty<Real>(_se_coeff_names[i]);
  }
}

ADReal
FieldEmissionBC::computeQpResidual()
{
  if (_normals[_qp] * -1.0 * _electric_field[_qp] > 0.0)
  {
    _a = 1.0;
    return 0;
  }
  else
  {
    _a = 0.0;

    for (unsigned int i = 0; i < _num_ions; ++i)
    {

      _ion_flux = (*_sgnip[i])[_qp] * (*_muip[i])[_qp] * _electric_field[_qp] * _r_units *
                      std::exp((*_ip[i])[_qp]) -
                  (*_Dip[i])[_qp] * std::exp((*_ip[i])[_qp]) * (*_grad_ip[i])[_qp] * _r_units;
      jSE += _e[_qp] * 6.02E23 * _normals[_qp] * (*_se_coeff[i])[_qp] * _ion_flux;
    }

    // Fowler-Nordheim
    // jFE = (a / wf) * F^2 * exp(-v(f) * b * wf^1.5 / F)
    // a = 1.541434E-6 A eV/V^2
    // b = 6.830890E9 V/m-eV^1.5
    // c = 1.439964E-9 eV^2-m/V
    // v(f) = 1 - f + (f/6)*ln(f)
    // f = c*(F/wf^2)

    F = -(1 - _a) * _field_enhancement[_qp] * _normals[_qp] * -_electric_field[_qp] * _r_units;

    f = FE_c * F / std::pow(_work_function[_qp], 2);
    v = 1 - f + (f / 6) * std::log(f);

    jFE = (FE_a / (_work_function[_qp])) * std::pow(F, 2) *
          std::exp(-v * FE_b * std::pow(_work_function[_qp], 1.5) / F);

    if (_relax == true)
      _relaxation_Expr = std::tanh(_t / _tau);
    else
      _relaxation_Expr = 1.0;

    return _relaxation_Expr * _test[_i][_qp] * _r_units * 2. / (1. + _r) * (1 - _a) * (-jFE - jSE) /
           (_e[_qp] * 6.02E23);
  }
}
