//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef HEAVYSPECIES_H_
#define HEAVYSPECIES_H_

#include "Material.h"
/* #include "LinearInterpolation.h" */
#include "SplineInterpolation.h"

class HeavySpecies;

template <>
InputParameters validParams<HeavySpecies>();

class HeavySpecies : public Material
{
public:
  HeavySpecies(const InputParameters & parameters);

protected:
  virtual void computeQpProperties();

  Real _user_massHeavy;
  Real _user_sgnHeavy;

  std::string _potential_units;
  Real _voltage_scaling;

  MaterialProperty<Real> & _massHeavy;        // Replaces _massArp
  MaterialProperty<Real> & _temperatureHeavy; // Replaces _tempArp
  MaterialProperty<Real> & _sgnHeavy;         // Replaces _sgnArp (unused though)
  MaterialProperty<Real> & _muHeavy;          // Replaces _muArp
  MaterialProperty<Real> & _diffHeavy;        // Replaces _diffArp

  const MaterialProperty<Real> & _T_gas;
  const MaterialProperty<Real> & _p_gas;
};

#endif // HEAVYSPECIES_H_
