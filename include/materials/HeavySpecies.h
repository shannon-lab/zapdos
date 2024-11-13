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
#include "SplineInterpolation.h"

/*
 *  Material properties of ions
 */
template <bool is_ad>
class HeavySpeciesTempl : public Material
{
public:
  HeavySpeciesTempl(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual void computeQpProperties() override;

  /// User defined ion mass
  Real _user_massHeavy;
  /// User defined charge sign of ion
  Real _user_sgnHeavy;
  /// Scaling units for the potential (V or kV)
  std::string _potential_units;
  /// Scaling value for the potential
  Real _voltage_scaling;

  /// Ion mass
  MaterialProperty<Real> & _massHeavy;
  /// Ion temperature                      
  GenericMaterialProperty<Real, is_ad> & _temperatureHeavy;
  /// Charge sign of ion
  MaterialProperty<Real> & _sgnHeavy;
  /// Ion mobility coefficient                   
  GenericMaterialProperty<Real, is_ad> & _muHeavy;
  /// Ion diffusion coefficient        
  GenericMaterialProperty<Real, is_ad> & _diffHeavy;        

  /// Neutal gas temperature
  const MaterialProperty<Real> & _T_gas;
  /// Neutal gas density
  const MaterialProperty<Real> & _p_gas;

  /// Time units
  Real _time_units;
  /// If true, calculate mobility coefficient assuming argon ions
  bool _calc_mobility;
  /// If true, calculate diffusion coefficient assuming argon ions
  bool _calc_diffusivity;
};

typedef HeavySpeciesTempl<false> HeavySpecies;
typedef HeavySpeciesTempl<true> ADHeavySpecies;
