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
template <ComputeStage>
class ADDCIonBC;

declareADValidParams(ADDCIonBC);

template <ComputeStage compute_stage>
class ADDCIonBC : public ADIntegratedBC<compute_stage>
{
public:
  static InputParameters validParams();
  ADDCIonBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  Real _r_units;

  // Coupled variables
  const ADVariableGradient & _grad_potential;

  const ADMaterialProperty(Real) & _mu;
  const ADMaterialProperty(Real) & _sgn;

  Real _a;

  usingIntegratedBCMembers;
};
