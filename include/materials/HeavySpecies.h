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

#include "Material.h"
/* #include "LinearInterpolation.h" */
#include "SplineInterpolation.h"

template <bool is_ad>
class HeavySpeciesTempl : public Material
{
public:
  HeavySpeciesTempl(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual void computeQpProperties();

  Real _user_massHeavy;
  Real _user_sgnHeavy;
  // Real _user_T_gas;
  // Real _user_p_gas;
  std::string _potential_units;
  Real _voltage_scaling;

  MaterialProperty<Real> & _massHeavy;                      // Replaces _massArp
  GenericMaterialProperty<Real, is_ad> & _temperatureHeavy; // Replaces _tempArp
  MaterialProperty<Real> & _sgnHeavy;                       // Replaces _sgnArp (unused though)
  GenericMaterialProperty<Real, is_ad> & _muHeavy;          // Replaces _muArp
  GenericMaterialProperty<Real, is_ad> & _diffHeavy;        // Replaces _diffArp

  const MaterialProperty<Real> & _T_gas;
  const MaterialProperty<Real> & _p_gas;

  Real _time_units;
  bool _calc_mobility;
  bool _calc_diffusivity;

  // MaterialProperty<Real> & _T_gas;
  // MaterialProperty<Real> & _p_gas;  // Replace with gas fraction?
  // MaterialProperty<Real> & _n_gas;
};

typedef HeavySpeciesTempl<false> HeavySpecies;
typedef HeavySpeciesTempl<true> ADHeavySpecies;
