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

#include "ADKernel.h"

/*
 *  Effective electric field driven advection term. The effective electric
 *  field is supplied as scalar components of the field
 */
class EffectiveEFieldAdvection : public ADKernel
{
public:
  static InputParameters validParams();

  EffectiveEFieldAdvection(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual();

private:
  /// Position units
  const Real _r_units;

  /// Mobility coefficient
  const ADMaterialProperty<Real> & _mu;
  /// Charge sign of the species
  const MaterialProperty<Real> & _sign;
  /// x-component of the electric field
  const ADVariableValue & _u_Efield;
  /// y-component of the electric field
  const ADVariableValue & _v_Efield;
  /// z-component of the electric field
  const ADVariableValue & _w_Efield;
};
