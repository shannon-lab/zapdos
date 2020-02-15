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

template <ComputeStage compute_stage>
class ADJouleHeating : public ADKernel<compute_stage>
{
public:
  static InputParameters validParams();

  ADJouleHeating(const InputParameters & parameters);

protected:
  //virtual ADRealVectorValue precomputeQpResidual() override;
  virtual ADReal computeQpResidual() override;
  
  //usingKernelGradMembers;
  //using ADKernelGrad<compute_stage>::getPostprocessorValue;
  usingKernelMembers;

private:
  /// Position units
  const Real _r_units;
  std::string _potential_units;

  /// The diffusion coefficient (either constant or mixture-averaged)
  const ADMaterialProperty(Real) & _diff;
  const ADMaterialProperty(Real) & _mu;
  const ADVariableGradient & _grad_potential;
  const ADVariableValue & _em;
  const ADVariableGradient & _grad_em;

  Real _voltage_scaling;
};
