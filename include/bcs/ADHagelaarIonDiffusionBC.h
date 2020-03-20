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

// MOOSE includes
#include "MooseVariable.h"

// Forward Declarations
template <ComputeStage>
class ADHagelaarIonDiffusionBC;

declareADValidParams(ADHagelaarIonDiffusionBC);

template <ComputeStage compute_stage>
class ADHagelaarIonDiffusionBC : public ADIntegratedBC<compute_stage>
{
public:
  static InputParameters validParams();
  ADHagelaarIonDiffusionBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  Real _r_units;
  Real _r;

  const MaterialProperty<Real> & _kb;
  const ADMaterialProperty(Real) & _T;
  const MaterialProperty<Real> & _mass;

  ADReal _v_thermal;
  Real _user_velocity;

  usingIntegratedBCMembers;
};
