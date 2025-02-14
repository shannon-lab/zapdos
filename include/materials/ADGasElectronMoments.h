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
#include "DerivativeMaterialPropertyNameInterface.h"

/**
 *  Material properties of electrons
 *  (Defines reaction properties with rate coefficients)
 */
class ADGasElectronMoments : public ADMaterial, public DerivativeMaterialPropertyNameInterface
{
public:
  static InputParameters validParams();
  ADGasElectronMoments(const InputParameters & parameters);

protected:
  virtual void computeQpProperties() override;

  /// Spline Interpolation fuction for electron mobility coefficient
  SplineInterpolation _mu_interpolation;
  /// Spline Interpolation fuction for diffusion mobility coefficient
  SplineInterpolation _diff_interpolation;

  /// Scaling units for the potential (V or kV)
  std::string _potential_units;
  /// Scaling value for the potential
  Real _voltage_scaling;

  /// Time units
  Real _time_units;

  /// True if molar density is used
  bool _use_moles;

  /// Electron mobility coefficient
  ADMaterialProperty<Real> & _muem;
  /// Electron diffusion coefficient
  ADMaterialProperty<Real> & _diffem;
  /// Electron mean energy mobility coefficient
  ADMaterialProperty<Real> & _mumean_en;
  /// Electron mean energy diffusion coefficient
  ADMaterialProperty<Real> & _diffmean_en;
  /// Charge sign of electron mean energy density
  MaterialProperty<Real> & _sgnmean_en;
  /// Charge sign of electrons
  MaterialProperty<Real> & _sgnem;
  /// Electron density
  const ADVariableValue & _em;
  /// Electron mean energy density
  const ADVariableValue & _mean_en;
  /// Electron mean energy
  Real actual_mean_en;
};
