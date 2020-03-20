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
class ADCoeffDiffusionElectrons : public ADKernel<compute_stage>
{
public:
  static InputParameters validParams();

  ADCoeffDiffusionElectrons(const InputParameters & parameters);

protected:
  // virtual ADRealVectorValue precomputeQpResidual() override;
  virtual ADReal computeQpResidual();

  // usingKernelGradMembers;
  // using ADKernelGrad<compute_stage>::getPostprocessorValue;
  usingKernelMembers;

private:
  /// Position units
  const Real _r_units;

  /// The diffusion coefficient (either constant or mixture-averaged)
  const ADMaterialProperty(Real) & _diffem;
};
