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

/*
 *  Material properties of electrons and universal constants
 */
class GasElectronMoments : public ADMaterial
{
public:
  GasElectronMoments(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual void computeQpProperties() override;

  /// Spline Interpolation fuction for ionization Townsend coefficient
  SplineInterpolation _alpha_interpolation;
  /// Spline Interpolation fuction for excitation Townsend coefficient
  SplineInterpolation _alphaEx_interpolation;
  /// Spline Interpolation fuction for elastic Townsend coefficient
  SplineInterpolation _alphaEl_interpolation;
  /// Spline Interpolation fuction for electron mobility coefficient
  SplineInterpolation _mu_interpolation;
  /// Spline Interpolation fuction for diffusion mobility coefficient
  SplineInterpolation _diff_interpolation;

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

  /// Time units
  const Real _time_units;

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
  /// Coupled pressure variable
  const VariableValue & _user_p_gas;
  /// True if molar density is used
  const bool _use_moles;

  /// User defined electron mobility coefficient
  const Real _user_muem;
  /// User defined electron diffusion coefficient
  const Real _user_diffem;
  /// True is electron transport coefficients are pressure dependent
  const bool _pressure_dependent;

  /// AD electron mobility coefficient
  ADMaterialProperty<Real> & _muem;
  /// AD electron diffusion coefficient
  ADMaterialProperty<Real> & _diffem;
  /// Energy threshold for helium ionization
  MaterialProperty<Real> & _Eiz;
  /// Energy threshold for helium excitation
  MaterialProperty<Real> & _Eex;
  /// Argon density at atmospheric pressure
  MaterialProperty<Real> & _Ar;
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

  /// Elementary charge
  MaterialProperty<Real> & _e;
  /// Permittivity of free space
  MaterialProperty<Real> & _eps;

  /// Boltzmann constant
  MaterialProperty<Real> & _k_boltz;
  /// Avogadro's number
  MaterialProperty<Real> & _Avogadro;
  /// Avogadro's number (reduced significant figures)
  MaterialProperty<Real> & _N_A;

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
  /// Argon elastic rate coefficient
  ADMaterialProperty<Real> & _kel;
  /// Electron temperatuer in eV
  ADMaterialProperty<Real> & _TemVolts;

  /// Coupled electron density
  const ADVariableValue & _em;
  /// Coupled electron energy density
  const ADVariableValue & _mean_en;
};
