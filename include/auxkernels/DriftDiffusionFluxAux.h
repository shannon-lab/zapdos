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

#include "AuxKernel.h"

/**
 *  Returns the drift-diffusion flux of the specified species
 */
class DriftDiffusionFluxAux : public AuxKernel
{
public:
  DriftDiffusionFluxAux(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeValue() override;

private:
  /// Charge sign of the coupled species
  const Real _sgn;
  /// Gradient of the coupled potential
  const VariableGradient & _grad_potential;
  /// Value of the coupled density variable
  const VariableValue & _u;
  /// Gradient of the coupled density variable
  const VariableGradient & _grad_u;
  /// Component of the flux
  const int _component;
};
