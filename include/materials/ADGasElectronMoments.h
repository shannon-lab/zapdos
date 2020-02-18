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

template <ComputeStage compute_stage>
class ADGasElectronMoments : public ADMaterial<compute_stage>
{
public:
  static InputParameters validParams();
  ADGasElectronMoments(const InputParameters & parameters);

protected:
  virtual void computeQpProperties() override;

  //SplineInterpolation _mu_interpolation;
  //SplineInterpolation _diff_interpolation;
  ADLinearInterpolation _mu_interpolation;
  ADLinearInterpolation _diff_interpolation;

  /* bool _townsend; */
  std::string _potential_units;
  Real _voltage_scaling;

  // adding
  Real _time_units;
  Real _charge_units;

  bool _use_moles;

  ADMaterialProperty(Real) & _muem;
  ADMaterialProperty(Real) & _d_muem_d_actual_mean_en;
  ADMaterialProperty(Real) & _diffem;
  ADMaterialProperty(Real) & _d_diffem_d_actual_mean_en;
  // MaterialProperty<Real> & _muArp;
  // MaterialProperty<Real> & _diffArp;
  ADMaterialProperty(Real) & _mumean_en;

  ADMaterialProperty(Real) & _diffmean_en;
  ADMaterialProperty(Real) & _sgnmean_en;
  ADMaterialProperty(Real) & _sgnem;
  ADMaterialProperty(Real) & _d_mumean_en_d_actual_mean_en;
  ADMaterialProperty(Real) & _d_diffmean_en_d_actual_mean_en;
  //MaterialProperty<Real> & _massem;
  //MaterialProperty<Real> & _e;
  //MaterialProperty<Real> & _eps;
  // MaterialProperty<Real> & _TArp;
  const ADVariableValue & _em;
  const ADVariableValue & _mean_en;

  usingMaterialMembers;
  using ADMaterial<compute_stage>::_communicator;
};
