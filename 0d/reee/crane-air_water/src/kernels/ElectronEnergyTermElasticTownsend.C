//* This file is part of CRANE, an open-source
//* application for the simulation of plasmas
//* https://github.com/lcpp-org/crane
//*
//* CRANE is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ElectronEnergyTermElasticTownsend.h"

registerMooseObject("CraneApp", ElectronEnergyTermElasticTownsend);

template <>
InputParameters
validParams<ElectronEnergyTermElasticTownsend>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("potential", "The potential.");
  params.addRequiredCoupledVar("electron_species", "The electron density.");
  params.addRequiredCoupledVar("target_species", "The target species variable.");
  params.addRequiredParam<std::string>("reaction",
                                       "Stores the name of the reaction (townsend) coefficient, "
                                       "unique to each individual reaction.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  return params;
}

ElectronEnergyTermElasticTownsend::ElectronEnergyTermElasticTownsend(
    const InputParameters & parameters)
  : Kernel(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _diffem(getMaterialProperty<Real>("diffem")),
    _muem(getMaterialProperty<Real>("muem")),
    _alpha(getMaterialProperty<Real>("alpha_" + getParam<std::string>("reaction"))),
    _d_iz_d_actual_mean_en(getMaterialProperty<Real>("d_iz_d_actual_mean_en")),
    _d_muem_d_actual_mean_en(getMaterialProperty<Real>("d_muem_d_actual_mean_en")),
    _d_diffem_d_actual_mean_en(getMaterialProperty<Real>("d_diffem_d_actual_mean_en")),
    //    _massem(getMaterialProperty<Real>("mass" + (*getVar("electron_species",0)).name())),
    _massGas(getMaterialProperty<Real>("mass" + (*getVar("target_species", 0)).name())),
    //_d_el_d_actual_mean_en(getMaterialProperty<Real>("d_el_d_actual_mean_en")),
    _d_el_d_actual_mean_en(getMaterialProperty<Real>("d_alpha_d_en_"+getParam<std::string>("reaction"))),
    _grad_potential(coupledGradient("potential")),
    _em(coupledValue("electron_species")),
    _grad_em(coupledGradient("electron_species")),
    _potential_id(coupled("potential")),
    _em_id(coupled("electron_species"))
{
  _massem = 9.11e-31;
}

ElectronEnergyTermElasticTownsend::~ElectronEnergyTermElasticTownsend() {}

Real
ElectronEnergyTermElasticTownsend::computeQpResidual()
{
  Real electron_flux_mag = (-_muem[_qp] * -_grad_potential[_qp] * _r_units * std::exp(_em[_qp]) -
                            _diffem[_qp] * std::exp(_em[_qp]) * _grad_em[_qp] * _r_units)
                               .norm();
  Real Eel = -3.0 * _massem / _massGas[_qp] * 2.0 / 3 * std::exp(_u[_qp] - _em[_qp]);
  Real el_term = _alpha[_qp] * electron_flux_mag * Eel;

  return -_test[_i][_qp] * el_term;
}

Real
ElectronEnergyTermElasticTownsend::computeQpJacobian()
{
  Real d_actual_mean_en_d_mean_en = std::exp(_u[_qp] - _em[_qp]) * _phi[_j][_qp];
  Real d_el_d_mean_en = _d_el_d_actual_mean_en[_qp] * d_actual_mean_en_d_mean_en;
  Real d_muem_d_mean_en = _d_muem_d_actual_mean_en[_qp] * d_actual_mean_en_d_mean_en;
  Real d_diffem_d_mean_en = _d_diffem_d_actual_mean_en[_qp] * d_actual_mean_en_d_mean_en;

  RealVectorValue electron_flux =
      -_muem[_qp] * -_grad_potential[_qp] * _r_units * std::exp(_em[_qp]) -
      _diffem[_qp] * std::exp(_em[_qp]) * _grad_em[_qp] * _r_units;
  RealVectorValue d_electron_flux_d_mean_en =
      -d_muem_d_mean_en * -_grad_potential[_qp] * _r_units * std::exp(_em[_qp]) -
      d_diffem_d_mean_en * std::exp(_em[_qp]) * _grad_em[_qp] * _r_units;
  Real electron_flux_mag = electron_flux.norm();
  Real d_electron_flux_mag_d_mean_en = electron_flux * d_electron_flux_d_mean_en /
                                       (electron_flux_mag + std::numeric_limits<double>::epsilon());

  Real Eel = -3.0 * _massem / _massGas[_qp] * 2.0 / 3 * std::exp(_u[_qp] - _em[_qp]);
  Real d_Eel_d_mean_en =
      -3.0 * _massem / _massGas[_qp] * 2.0 / 3 * std::exp(_u[_qp] - _em[_qp]) * _phi[_j][_qp];
  Real d_el_term_d_mean_en =
      (electron_flux_mag * d_el_d_mean_en + _alpha[_qp] * d_electron_flux_mag_d_mean_en) * Eel +
      electron_flux_mag * _alpha[_qp] * d_Eel_d_mean_en;

  return -_test[_i][_qp] * d_el_term_d_mean_en;
}

Real
ElectronEnergyTermElasticTownsend::computeQpOffDiagJacobian(unsigned int jvar)
{
  Real d_actual_mean_en_d_em = -std::exp(_u[_qp] - _em[_qp]) * _phi[_j][_qp];
  Real d_el_d_em = _d_el_d_actual_mean_en[_qp] * d_actual_mean_en_d_em;
  Real d_muem_d_em = _d_muem_d_actual_mean_en[_qp] * d_actual_mean_en_d_em;
  Real d_diffem_d_em = _d_diffem_d_actual_mean_en[_qp] * d_actual_mean_en_d_em;

  RealVectorValue electron_flux =
      -_muem[_qp] * -_grad_potential[_qp] * _r_units * std::exp(_em[_qp]) -
      _diffem[_qp] * std::exp(_em[_qp]) * _grad_em[_qp] * _r_units;
  RealVectorValue d_electron_flux_d_potential =
      -_muem[_qp] * -_grad_phi[_j][_qp] * _r_units * std::exp(_em[_qp]);
  RealVectorValue d_electron_flux_d_em =
      -d_muem_d_em * -_grad_potential[_qp] * _r_units * std::exp(_em[_qp]) -
      _muem[_qp] * -_grad_potential[_qp] * _r_units * std::exp(_em[_qp]) * _phi[_j][_qp] -
      d_diffem_d_em * std::exp(_em[_qp]) * _grad_em[_qp] * _r_units -
      _diffem[_qp] * std::exp(_em[_qp]) * _phi[_j][_qp] * _grad_em[_qp] * _r_units -
      _diffem[_qp] * std::exp(_em[_qp]) * _grad_phi[_j][_qp] * _r_units;
  Real electron_flux_mag = electron_flux.norm();
  Real d_electron_flux_mag_d_potential =
      electron_flux * d_electron_flux_d_potential /
      (electron_flux_mag + std::numeric_limits<double>::epsilon());
  Real d_electron_flux_mag_d_em = electron_flux * d_electron_flux_d_em /
                                  (electron_flux_mag + std::numeric_limits<double>::epsilon());

  Real Eel = -3.0 * _massem / _massGas[_qp] * 2.0 / 3 * std::exp(_u[_qp] - _em[_qp]);
  Real d_Eel_d_em =
      -3.0 * _massem / _massGas[_qp] * 2.0 / 3 * std::exp(_u[_qp] - _em[_qp]) * -_phi[_j][_qp];
  Real d_Eel_d_potential = 0.0;
  Real d_el_term_d_em =
      (electron_flux_mag * d_el_d_em + _alpha[_qp] * d_electron_flux_mag_d_em) * Eel +
      electron_flux_mag * _alpha[_qp] * d_Eel_d_em;
  Real d_el_term_d_potential = (_alpha[_qp] * d_electron_flux_mag_d_potential) * Eel +
                               electron_flux_mag * _alpha[_qp] * d_Eel_d_potential;

  if (jvar == _potential_id)
    return -_test[_i][_qp] * d_el_term_d_potential;

  else if (jvar == _em_id)
    return -_test[_i][_qp] * d_el_term_d_em;

  else
    return 0.0;
}
