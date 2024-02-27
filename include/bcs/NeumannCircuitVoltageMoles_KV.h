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

#include "ADIntegratedBC.h"
#include "ProvideMobility.h"

class NeumannCircuitVoltageMoles_KV : public ADIntegratedBC
{
public:
  static InputParameters validParams();

  NeumannCircuitVoltageMoles_KV(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// The function being used for setting the value
  const Real _r_units;
  const Function & _V_bat;
  const ProvideMobility & _data;

  std::vector<const ADVariableValue *> _ip;
  std::vector<const ADVariableGradient *> _grad_ip;
  std::vector<unsigned int> _ip_id;
  const ADVariableValue & _mean_en;
  const ADVariableValue & _em;
  const std::vector<std::string> _se_coeff_names;
  std::vector<const ADMaterialProperty<Real> *> _se_coeff;
  std::vector<const ADMaterialProperty<Real> *> _muip;
  const MaterialProperty<Real> & _eps;
  const MaterialProperty<Real> & _N_A;
  std::vector<const MaterialProperty<Real> *> _sgnip;
  std::vector<const ADMaterialProperty<Real> *> _Dip;
  const ADMaterialProperty<Real> & _muem;
  const MaterialProperty<Real> & _e;
  const MaterialProperty<Real> & _massem;
  std::vector<const ADMaterialProperty<Real> *> _T_heavy;
  const MaterialProperty<Real> & _kb;
  std::vector<const MaterialProperty<Real> *> _mass;

  const std::string & _potential_units;
  const Real & _r;

  ADRealVectorValue _ion_flux;
  ADReal _n_gamma;
  ADReal _actual_mean_en;
  ADReal _v_e_th;
  ADReal _v_i_th;
  Real _a;
  Real _b;
  ADReal _numerator;
  ADReal _denominator;

  Real _voltage_scaling;

  ADReal _ion_drift;
  ADReal _secondary_ion;
  const unsigned int _num_ions;
};
