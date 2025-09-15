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
#include "SplineInterpolation.h"

class GasBase : public ADMaterial
{
public:
  GasBase(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual void computeQpProperties() override;

  /// Spline Interpolation function for the ionization Townsend coefficient
  SplineInterpolation _alpha_interpolation;
  /// Spline Interpolation function for the excitation Townsend coefficient
  SplineInterpolation _alphaEx_interpolation;
  /// Spline Interpolation function for the elastic Townsend coefficient
  SplineInterpolation _alphaEl_interpolation;
  /// Spline Interpolation function for the electron mobility coefficient
  SplineInterpolation _mu_interpolation;
  /// Spline Interpolation function for the diffusion mobility coefficient
  SplineInterpolation _diff_interpolation;

  /// Position units
  const Real _r_units;
  /// True if interpolating transport coefficients as a function of the mean energy
  const bool _interp_trans_coeffs;
  /// True if interpolating the elastic collision townsend coefficient as a function of the mean energy
  const bool _interp_elastic_coeff;
  /// True if ramping the non-linearity of coming from the electron energy dependence of the transport coefficients
  const bool _ramp_trans_coeffs;
  /// Scaling units for the potential (V or kV)
  const std::string _potential_units;
  /// Scaling value for the potential
  Real _voltage_scaling;
  /// User defined secondary electron coefficient
  const Real _user_se_coeff;
  /// User defined work function
  const Real _user_work_function;
  /// User defined field enhancement factor
  const Real _user_field_enhancement;
  /// User defined Richardson coefficient
  const Real _user_Richardson_coefficient;
  /// User defined cathode temperature
  const Real _user_cathode_temperature;
  /// User defined neutral gas and ion temperature
  const Real _user_T_gas;
  /// User defined neutral gas pressure
  const Real _user_p_gas;
  /// True if molar density is used
  const bool _use_moles;

  /// AD electron mobility coefficient
  ADMaterialProperty<Real> & _muem;
  /// AD electron diffusion coefficient
  ADMaterialProperty<Real> & _diffem;
  /// Energy threshold for argon ionization
  MaterialProperty<Real> & _Eiz;
  /// Energy threshold for argon excitation
  MaterialProperty<Real> & _Eex;
  /// AD electron energy mobility coefficient
  ADMaterialProperty<Real> & _mumean_en;
  /// AD electron energy diffusion coefficient
  ADMaterialProperty<Real> & _diffmean_en;
  /// Constant elastic collision rate coefficient
  MaterialProperty<Real> & _rate_coeff_elastic;
  /// Mass of electrons
  MaterialProperty<Real> & _massem;
  /// Mass of argon neutrals
  MaterialProperty<Real> & _massGas;
  /// Secondary electron coefficient
  MaterialProperty<Real> & _se_coeff;
  /// Work function
  MaterialProperty<Real> & _work_function;
  /// Field enhancement coefficient
  MaterialProperty<Real> & _field_enhancement;
  /// Richardson coefficient
  MaterialProperty<Real> & _Richardson_coefficient;
  /// Cathode termperature
  MaterialProperty<Real> & _cathode_temperature;
  /// Secondary electron energy
  MaterialProperty<Real> & _se_energy;

  /// Avogadro's number
  MaterialProperty<Real> & _Avogadro;
  /*
   *  Curve fitting for ionization coefficients dependent
   *  on the electric field based on bolos simulations
   */
  ///@{
  MaterialProperty<Real> & _iz_coeff_efield_a;
  MaterialProperty<Real> & _iz_coeff_efield_b;
  MaterialProperty<Real> & _iz_coeff_efield_c;
  ///@}
  /*
   *  Curve fitting for ionization coefficients dependent
   *  on the electron energy based on bolos simulations
   */
  ///@{
  MaterialProperty<Real> & _iz_coeff_energy_a;
  MaterialProperty<Real> & _iz_coeff_energy_b;
  MaterialProperty<Real> & _iz_coeff_energy_c;
  ///@}
  /*
   *  Curve fitting for elastic coefficients dependent
   *  on the electron energy based on bolos simulations
   */
  ///@{
  MaterialProperty<Real> & _el_coeff_energy_a;
  MaterialProperty<Real> & _el_coeff_energy_b;
  MaterialProperty<Real> & _el_coeff_energy_c;
  ///@}
  /// AD Ionization Townsend coefficient
  ADMaterialProperty<Real> & _alpha_iz;
  /// AD Excitation Townsend coefficient
  ADMaterialProperty<Real> & _alpha_ex;
  /// AD Elastic Townsend coefficient
  ADMaterialProperty<Real> & _alpha_el;
  /// Charge sign of electrons
  MaterialProperty<Real> & _sgnem;
  /// Charge sign of electron energy density
  MaterialProperty<Real> & _sgnmean_en;
  /// Potential diffusion coefficient (material permittivity)
  ADMaterialProperty<Real> & _diffpotential;
  /// Electron energy
  ADMaterialProperty<Real> & _actual_mean_energy;
  /// Electron temperature
  ADMaterialProperty<Real> & _Tem;
  /// Argon neutral gas temperature
  MaterialProperty<Real> & _T_gas;
  /// Argon neutral gas pressure
  MaterialProperty<Real> & _p_gas;
  /// Argon neutral gas density
  MaterialProperty<Real> & _n_gas;
  /// Argon ionization rate coefficient
  ADMaterialProperty<Real> & _kiz;
  /// Argon excitation rate coefficient
  ADMaterialProperty<Real> & _kex;
  /*
   *  Argon excitation rate coefficient
   *  TODO: _kArp is defined the same as _kex.
   *        These material properties should be
   *        consolidated.
   */
  ADMaterialProperty<Real> & _kArp;
  /// Argon elastic rate coefficient
  ADMaterialProperty<Real> & _kel;
  /// Electron temperatuer in eV
  ADMaterialProperty<Real> & _TemVolts;

  /// Coupled electron density
  const ADVariableValue & _em;
  /// Coupled electron energy density
  const ADVariableValue & _mean_en;
};
