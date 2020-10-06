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

class ADGasElectronMoments : public ADMaterial, public DerivativeMaterialPropertyNameInterface
{
public:
  static InputParameters validParams();
  ADGasElectronMoments(const InputParameters & parameters);

protected:
  virtual void computeQpProperties() override;

  SplineInterpolation _mu_interpolation;
  SplineInterpolation _diff_interpolation;

  /* bool _townsend; */
  std::string _potential_units;
  Real _voltage_scaling;

  Real _time_units;
  Real _charge_units;

  bool _use_moles;

  ADMaterialProperty<Real> & _muem;
  ADMaterialProperty<Real> & _diffem;
  ADMaterialProperty<Real> & _mumean_en;

  ADMaterialProperty<Real> & _diffmean_en;
  MaterialProperty<Real> & _sgnmean_en;
  MaterialProperty<Real> & _sgnem;

  const ADVariableValue & _em;
  const ADVariableValue & _mean_en;

  Real actual_mean_en;
};
