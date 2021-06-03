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
#include "LinearInterpolation.h"
#include "SplineInterpolation.h"

class Gas : public ADMaterial
{
public:
  static InputParameters validParams();
  Gas(const InputParameters & parameters);

protected:
  virtual void computeQpProperties() override;

  SplineInterpolation _alpha_interpolation;
  SplineInterpolation _alphaEx_interpolation;
  SplineInterpolation _alphaEl_interpolation;
  SplineInterpolation _mu_interpolation;
  SplineInterpolation _diff_interpolation;
  /*
  LinearInterpolation _alpha_interpolation;
  LinearInterpolation _alphaEx_interpolation;
  LinearInterpolation _alphaEl_interpolation;
  LinearInterpolation _mu_interpolation;
  LinearInterpolation _diff_interpolation;
  */

  /* LinearInterpolation _d_alpha_d_actual_mean_energy_interpolation; */

  /* bool _townsend; */
  bool _interp_trans_coeffs;
  bool _interp_elastic_coeff;
  bool _ramp_trans_coeffs;
  std::string _potential_units;
  Real _voltage_scaling;
  Real _user_se_coeff;
  Real _user_work_function;
  Real _user_field_enhancement;
  Real _user_Richardson_coefficient;
  Real _user_cathode_temperature;
  Real _user_T_gas;
  Real _user_p_gas;
  bool _use_moles;

  ADMaterialProperty<Real> & _muem;
  ADMaterialProperty<Real> & _diffem;
  ADMaterialProperty<Real> & _muArp;
  ADMaterialProperty<Real> & _diffArp;
  MaterialProperty<Real> & _Eiz;
  MaterialProperty<Real> & _Eex;
  MaterialProperty<Real> & _Ar;
  ADMaterialProperty<Real> & _mumean_en;
  ADMaterialProperty<Real> & _diffmean_en;
  MaterialProperty<Real> & _rate_coeff_elastic;
  MaterialProperty<Real> & _massem;
  MaterialProperty<Real> & _massGas;
  MaterialProperty<Real> & _massArp;
  MaterialProperty<Real> & _se_coeff;
  MaterialProperty<Real> & _work_function;
  MaterialProperty<Real> & _field_enhancement;
  MaterialProperty<Real> & _Richardson_coefficient;
  MaterialProperty<Real> & _cathode_temperature;
  MaterialProperty<Real> & _se_energy;
  MaterialProperty<Real> & _e;
  MaterialProperty<Real> & _eps;
  MaterialProperty<Real> & _k_boltz;
  MaterialProperty<Real> & _Avogadro;
  MaterialProperty<Real> & _vthermal_em;
  MaterialProperty<Real> & _vthermal_ip;
  MaterialProperty<Real> & _iz_coeff_efield_a;
  MaterialProperty<Real> & _iz_coeff_efield_b;
  MaterialProperty<Real> & _iz_coeff_efield_c;
  MaterialProperty<Real> & _iz_coeff_energy_a;
  MaterialProperty<Real> & _iz_coeff_energy_b;
  MaterialProperty<Real> & _iz_coeff_energy_c;
  MaterialProperty<Real> & _N_A;
  MaterialProperty<Real> & _el_coeff_energy_a;
  MaterialProperty<Real> & _el_coeff_energy_b;
  MaterialProperty<Real> & _el_coeff_energy_c;
  ADMaterialProperty<Real> & _alpha_iz;
  ADMaterialProperty<Real> & _alpha_ex;
  ADMaterialProperty<Real> & _alpha_el;
  MaterialProperty<Real> & _sgnem;
  MaterialProperty<Real> & _sgnmean_en;
  MaterialProperty<Real> & _sgnArp;
  ADMaterialProperty<Real> & _diffpotential;
  ADMaterialProperty<Real> & _actual_mean_energy;
  ADMaterialProperty<Real> & _TArp;
  ADMaterialProperty<Real> & _Tem;
  MaterialProperty<Real> & _T_gas;
  MaterialProperty<Real> & _p_gas;
  MaterialProperty<Real> & _n_gas;
  ADMaterialProperty<Real> & _kiz;
  ADMaterialProperty<Real> & _kex;
  ADMaterialProperty<Real> & _kel;
  ADMaterialProperty<Real> & _TemVolts;

  const ADVariableValue & _em;
  const ADVariableValue & _mean_en;
};
