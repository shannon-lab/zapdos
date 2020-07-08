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

#include "ADIntegratedBC.h"

// Forward Declarations
class ADComsolIonBC;

declareADValidParams(ADComsolIonBC);

class ADComsolIonBC : public ADIntegratedBC
{
public:
  static InputParameters validParams();
  ADComsolIonBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  Real _r_units;
  Real _r;

  // Coupled variables

  const ADVariableGradient & _grad_potential;

  const ADMaterialProperty<Real> & _mu;
  const MaterialProperty<Real> & _e;
  const MaterialProperty<Real> & _sgn;
  const MaterialProperty<Real> & _kb;
  const ADMaterialProperty<Real> & _T;
  const MaterialProperty<Real> & _mass;

  Real _a;

  ADReal _v_thermal;
};
