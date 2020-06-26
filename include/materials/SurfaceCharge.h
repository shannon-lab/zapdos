//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "Material.h"

class SurfaceCharge;

template <>
InputParameters validParams<SurfaceCharge>();

class SurfaceCharge : public Material
{
public:
  SurfaceCharge(const InputParameters & parameters);

protected:
  virtual void computeQpProperties() override;
  virtual void initQpStatefulProperties() override;

  void computeHagelaarFlux();
  void computeSakiyamaFlux();
  void computeLymberopoulosFlux();
  void computeComsolFlux();

  int _bc_type;
  MaterialProperty<Real> & _sigma;
  const MaterialProperty<Real> & _sigma_old;
  const MaterialProperty<Real> & _sigma_older;
  // const MaterialProperty<Real> & _d_sigma_d_potential_old;
  // const MaterialProperty<Real> & _d_sigma_d_em_old;
  // const MaterialProperty<Real> & _d_sigma_d_mean_en_old;
  MaterialProperty<Real> & _d_sigma_d_potential;
  MaterialProperty<Real> & _d_sigma_d_em;
  MaterialProperty<Real> & _d_sigma_d_mean_en;
  MaterialProperty<std::vector<Real>> & _d_sigma_d_ion;
  MaterialProperty<Real> & _ion_current;
  MaterialProperty<Real> & _electron_current;
  const MaterialProperty<Real> & _ion_current_old;
  const MaterialProperty<Real> & _electron_current_old;
  /*
  MaterialProperty<Real> & _d_electron_flux_d_potential;
  MaterialProperty<Real> & _d_ion_flux_d_potential;
  MaterialProperty<Real> & _d_ion_charge_flux_d_potential;
  MaterialProperty<Real> & _d_n_gamma_d_potential;
  */
  Real _d_electron_flux_d_potential;
  Real _d_ion_flux_d_potential;
  Real _d_ion_charge_flux_d_potential;
  Real _d_n_gamma_d_potential;
  std::vector<Real> _d_ion_flux_d_ion;
  std::vector<Real> _d_ion_charge_flux_d_ion;
  std::vector<Real> _d_n_gamma_d_ion;
  std::vector<Real> _d_electron_flux_d_ion;

  Real _d_electron_flux_d_em;
  Real _d_n_gamma_d_em;

  Real _d_electron_flux_d_mean_en;
  Real _d_n_gamma_d_mean_en;

  const bool _include_secondary_electrons;

  const MaterialProperty<Real> & _muem;
  const MaterialProperty<Real> & _d_muem_d_actual_mean_en;
  const MaterialProperty<Real> & _massem;
  // const MaterialProperty<Real> & _diffem;

  Real _r_units;
  Real _r_ion;
  Real _r_electron;
  const MaterialProperty<Real> & _kb;
  Real _v_thermal;
  Real _ve_thermal;
  Real _d_ve_thermal_d_em;
  Real _d_ve_thermal_d_mean_en;
  Real _user_velocity;
  const MaterialProperty<Real> & _e;
  Real _se_coeff;
  const std::string _potential_units;
  Real _a;
  Real _b;

  const VariableGradient & _grad_potential;
  const VariableValue & _mean_en;
  const VariableValue & _em;
  const VariableGradient & _grad_em;

  unsigned int _num_ions;
  std::vector<const VariableValue *> _ions;
  std::vector<const VariableGradient *> _grad_ions;
  std::vector<const MaterialProperty<Real> *> _mu_ions;
  // std::vector<const MaterialProperty<Real> *> _diff_ions;
  std::vector<const MaterialProperty<Real> *> _sgn_ions;
  std::vector<const MaterialProperty<Real> *> _mass_ions;
  std::vector<const MaterialProperty<Real> *> _T_ions;

  // Recombination coefficient for Lymberopoulos-style BCs
  Real _ks;

  Real _ion_flux;
  Real _positive_ion_flux;
  Real _single_ion_flux;
  Real _ion_charge_flux;
  Real _n_gamma;

  // Real _d_ion_flux_d_potential;
  // Real _d_electron_flux_d_potential;
  // Real _d_ion_charge_flux_d_potential;
  // Real _d_n_gamma_d_potential;

  Real _actual_mean_energy;
  Real _electron_flux;
  Real _voltage_scaling;
  Real _q_times_NA;
  Real _r_factor_ion;
  Real _r_factor_electron;
};

