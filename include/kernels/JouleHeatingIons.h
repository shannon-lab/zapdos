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

class JouleHeatingIons : public ADKernel
{
public:
  static InputParameters validParams();

  JouleHeatingIons(const InputParameters & parameters);

protected:
  // virtual ADRealVectorValue precomputeQpResidual() override;
  virtual ADReal computeQpResidual() override;

  //  // using ADKernelGrad::getPostprocessorValue;

private:
  /// Position units
  const Real _r_units;
  std::string _potential_units;

  /// The diffusion coefficient (either constant or mixture-averaged)
  const ADVariableGradient & _grad_potential;

  std::vector<const ADMaterialProperty<Real> *> _diff;
  std::vector<const ADMaterialProperty<Real> *> _mu;
  std::vector<const ADVariableValue *> _ion;
  std::vector<const MaterialProperty<Real> *> _sign;
  std::vector<const ADVariableGradient *> _grad_ion;

  Real _voltage_scaling;
  unsigned int _num_ions;
};
