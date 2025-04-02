//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "SchottkyEmissionBC.h"

registerMooseObject("ZapdosApp", SchottkyEmissionBC);

InputParameters
SchottkyEmissionBC::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  params.addRequiredParam<Real>("r", "The reflection coefficient");
  params.addRequiredCoupledVar("electron_energy", "The mean electron energy density in log form");
  params.addRequiredCoupledVar("ions", "A list of ion densities in log form");
  params.addRequiredParam<std::vector<std::string>>(
      "emission_coeffs",
      "A list of species-dependent secondary electron "
      "emission coefficients for each species in `ions`");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addRequiredParam<std::string>("potential_units", "The potential units.");
  params.addParam<Real>("tau", 1e-9, "The time constant for ramping the boundary condition.");
  params.addParam<bool>("relax", false, "Use relaxation for emission.");
  params.addParam<std::string>("field_property_name",
                               "field_solver_interface_property",
                               "Name of the solver interface material property.");
  params.addClassDescription(
      "The electron flux boundary condition due to field ehanced thermionic emission (Schottky "
      "emission)"
      " (Based on [!cite](go2012theoretical))");
  return params;
}

SchottkyEmissionBC::SchottkyEmissionBC(const InputParameters & parameters)
  : ADIntegratedBC(parameters),

    _r_units(1. / getParam<Real>("position_units")),
    _r(getParam<Real>("r")),
    _num_ions(coupledComponents("ions")),
    _se_coeff_names(getParam<std::vector<std::string>>("emission_coeffs")),
    // Coupled Variables
    _mean_en(adCoupledValue("electron_energy")),

    _massem(getMaterialProperty<Real>("massem")),
    _e(getMaterialProperty<Real>("e")),
    _work_function(getMaterialProperty<Real>("work_function")),
    _field_enhancement(getMaterialProperty<Real>("field_enhancement")),
    _Richardson_coefficient(getMaterialProperty<Real>("Richardson_coefficient")),
    _cathode_temperature(getMaterialProperty<Real>("cathode_temperature")),
    _a(0.5),
    _v_thermal(0),
    _ion_flux(0, 0, 0),
    _tau(getParam<Real>("tau")),
    _relax(getParam<bool>("relax")),
    _potential_units(getParam<std::string>("potential_units")),
    _electric_field(
        getADMaterialProperty<RealVectorValue>(getParam<std::string>("field_property_name")))

{
  if (_se_coeff_names.size() != _num_ions)
    mooseError("SchottkyEmissionBC with name ",
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

  _dPhi_over_F =
      3.7946865E-5 * std::sqrt(_voltage_scaling); // eV*sqrt(m/kV) (if _voltage_scaling = 1000)

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
SchottkyEmissionBC::computeQpResidual()
{
  _v_thermal =
      std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_mean_en[_qp] - _u[_qp]) / (M_PI * _massem[_qp]));

  if (_normals[_qp] * -1.0 * _electric_field[_qp] > 0.0)
  {
    _a = 1.0;
    return 0;
  }
  else
  {
    _a = 0.0;

    _ion_flux.zero();
    for (unsigned int i = 0; i < _num_ions; ++i)
    {
      _ion_flux += (*_se_coeff[i])[_qp] *
                   ((*_sgnip[i])[_qp] * (*_muip[i])[_qp] * _electric_field[_qp] * _r_units *
                        std::exp((*_ip[i])[_qp]) -
                    (*_Dip[i])[_qp] * std::exp((*_ip[i])[_qp]) * (*_grad_ip[i])[_qp] * _r_units);
    }

    // Schottky emission
    // je = AR * T^2 * exp(-(wf - dPhi) / (kB * T))
    // dPhi = _dPhi_over_F * sqrt(F) // eV

    F = -(1 - _a) * _field_enhancement[_qp] * _normals[_qp] * -_electric_field[_qp] * _r_units;

    kB = 8.617385E-5; // eV/K
    dPhi = _dPhi_over_F * std::sqrt(F);

    jRD = _Richardson_coefficient[_qp] * std::pow(_cathode_temperature[_qp], 2) *
          std::exp(-(_work_function[_qp] - dPhi) / (kB * _cathode_temperature[_qp]));
    jSE = _e[_qp] * 6.02E23 * _ion_flux * _normals[_qp];

    if (_relax)
    {
      _relaxation_Expr = std::tanh(_t / _tau);
    }
    else
    {
      _relaxation_Expr = 1.0;
    }

    return _relaxation_Expr * _test[_i][_qp] * _r_units * 2. / (1. + _r) * (1 - _a) * (-jRD - jSE) /
           (_e[_qp] * 6.02E23);
  }
}
