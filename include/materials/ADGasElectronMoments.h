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

  //LinearInterpolation _mu_interpolation;
  //LinearInterpolation _diff_interpolation;
  SplineInterpolation _mu_interpolation;
  SplineInterpolation _diff_interpolation;
  //std::unique_ptr<LinearInterpolation> _mu_interpolation2;
  //std::unique_ptr<LinearInterpolation> _diff_interpolation2;
  SplineInterpolation _mu_interpolation2;
  SplineInterpolation _diff_interpolation2;

  /* bool _townsend; */
  std::string _potential_units;
  Real _voltage_scaling;

  // adding
  Real _time_units;
  Real _charge_units;

  bool _use_moles;

  ADMaterialProperty<Real> & _muem;
  MaterialProperty<Real> & _d_muem_d_actual_mean_en;
  ADMaterialProperty<Real> & _diffem;
  MaterialProperty<Real> & _d_diffem_d_actual_mean_en;
  ADMaterialProperty<Real> & _mumean_en;

  ADMaterialProperty<Real> & _diffmean_en;
  MaterialProperty<Real> & _sgnmean_en;
  MaterialProperty<Real> & _sgnem;
  MaterialProperty<Real> & _d_mumean_en_d_actual_mean_en;
  MaterialProperty<Real> & _d_diffmean_en_d_actual_mean_en;
  const ADVariableValue & _em;
  const ADVariableValue & _mean_en;
};
