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

/*
 *  Material properties of electron and ions for argon gas
 *  (Defines reaction properties with Townsend coefficients)
 */
class FieldEmissionCoefficients : public ADMaterial
{
public:
  static InputParameters validParams();
  FieldEmissionCoefficients(const InputParameters & parameters);

protected:
  virtual void computeQpProperties() override;

  /// User defined work function
  const Real _user_work_function;
  /// User defined field enhancement factor
  const Real _user_field_enhancement;
  /// User defined Richardson coefficient
  const Real _user_Richardson_coefficient;

  /// Work function
  MaterialProperty<Real> & _work_function;
  /// Field enhancement coefficient
  MaterialProperty<Real> & _field_enhancement;
  /// Richardson coefficient
  MaterialProperty<Real> & _Richardson_coefficient;
};
