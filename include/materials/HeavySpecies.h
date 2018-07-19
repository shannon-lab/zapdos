/****************************************************************/
/*                      DO NOT MODIFY THIS HEADER               */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*              (c) 2010 Battelle Energy Alliance, LLC          */
/*                      ALL RIGHTS RESERVED                     */
/*                                                              */
/*              Prepared by Battelle Energy Alliance, LLC       */
/*              Under Contract No. DE-AC07-05ID14517            */
/*              With the U. S. Department of Energy             */
/*                                                              */
/*              See COPYRIGHT for full restrictions             */
/****************************************************************/
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

  MaterialProperty<Real> & _massHeavy; // Replaces _massArp
  MaterialProperty<Real> & _temperatureHeavy; // Replaces _tempArp
  MaterialProperty<Real> & _sgnHeavy; // Replaces _sgnArp (unused though)
  MaterialProperty<Real> & _muHeavy;  // Replaces _muArp
  MaterialProperty<Real> & _diffHeavy; // Replaces _diffArp

  const MaterialProperty<Real> & _T_gas;
  const MaterialProperty<Real> & _p_gas;
};

#endif // HEAVYSPECIES_H_
