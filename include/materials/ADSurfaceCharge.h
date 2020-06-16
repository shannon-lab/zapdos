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

#include "ADMaterial.h"
#include "DerivativeMaterialPropertyNameInterface.h"

class ADSurfaceCharge : public ADMaterial, public DerivativeMaterialPropertyNameInterface
{
public:
  static InputParameters validParams();
  ADSurfaceCharge(const InputParameters & parameters);

protected:
  virtual void computeQpProperties() override;
  virtual void initQpStatefulProperties() override;

  void computeHagelaarFlux();
  void computeSakiyamaFlux();
  void computeLymberopoulosFlux();
  void computeComsolFlux();

  int _bc_type;
  ADMaterialProperty<Real> & _sigma;
  const MaterialProperty<Real> & _sigma_old;

  const bool _include_secondary_electrons;

  const ADMaterialProperty<Real> & _muem;
  const MaterialProperty<Real> & _massem;

  Real _r_units;
  Real _r_ion;
  Real _r_electron;
  const MaterialProperty<Real> & _kb;
  ADReal _v_thermal;
  ADReal _ve_thermal;
  const MaterialProperty<Real> & _e;
  Real _se_coeff;
  const std::string _potential_units;
  Real _a;
  Real _b;

  const ADVariableGradient & _grad_potential;
  const ADVariableValue & _mean_en;
  const ADVariableValue & _em;
  const ADVariableGradient & _grad_em;

  unsigned int _num_ions;
  std::vector<const ADVariableValue *> _ions;
  std::vector<const ADVariableGradient *> _grad_ions;
  std::vector<const ADMaterialProperty<Real> *> _mu_ions;
  std::vector<const MaterialProperty<Real> *> _sgn_ions;
  std::vector<const MaterialProperty<Real> *> _mass_ions;
  std::vector<const ADMaterialProperty<Real> *> _T_ions;

  // Recombination coefficient for Lymberopoulos-style BCs
  Real _ks;

  ADReal _ion_flux;
  ADReal _single_ion_flux;
  ADReal _ion_charge_flux;
  ADReal _n_gamma;

  ADReal _actual_mean_energy;
  ADReal _electron_flux;

  Real _voltage_scaling;
  Real _q_times_NA;
  Real _r_factor_ion;
  Real _r_factor_electron;
};
