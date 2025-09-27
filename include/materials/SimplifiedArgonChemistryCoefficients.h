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

class SimplifiedArgonChemistryCoefficients : public ADMaterial
{
public:
  SimplifiedArgonChemistryCoefficients(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual void computeQpProperties() override;

  /// Spline Interpolation function for the ionization Townsend coefficient
  SplineInterpolation _alpha_interpolation;
  /// Spline Interpolation function for the excitation Townsend coefficient
  SplineInterpolation _alphaEx_interpolation;
  /// Spline Interpolation function for the elastic Townsend coefficient
  SplineInterpolation _alphaEl_interpolation;

  /// True if interpolating the elastic collision townsend coefficient as a function of the mean energy
  const bool _interp_elastic_coeff;

  /// User defined neutral gas and ion temperature
  const Real _user_T_gas;
  /// User defined neutral gas pressure
  const Real _user_p_gas;
  /// True if molar density is used
  const bool _use_moles;

  /// Energy threshold for argon ionization
  MaterialProperty<Real> & _Eiz;
  /// Energy threshold for argon excitation
  MaterialProperty<Real> & _Eex;
  /// Constant elastic collision rate coefficient
  MaterialProperty<Real> & _rate_coeff_elastic;
  /// Mass of argon neutrals
  MaterialProperty<Real> & _massGas;

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

  /// Electron temperature
  ADMaterialProperty<Real> & _Tem;

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
