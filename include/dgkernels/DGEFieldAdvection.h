//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ADDGKernel.h"

/**
 * The discontinuous Galerkin form of the generic electric 
 * field driven advection term
 */
class DGEFieldAdvection : public ADDGKernel
{
public:
  static InputParameters validParams();

  DGEFieldAdvection(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual(Moose::DGResidualType type) override;

  /// Mobility coefficient of current cell
  const ADMaterialProperty<Real> & _mu;
  /// Charge sign of the species in current cell
  const MaterialProperty<Real> & _sgn;
  /// Mobility coefficient of neighboring cell
  const ADMaterialProperty<Real> & _mu_neighbor;
  /// Charge sign of the species in neighboring cell
  const MaterialProperty<Real> & _sgn_neighbor;

  /// Coupled Potential variable
  MooseVariable & _potential_var;
  /// Gradient of coupled potential in current cell
  const ADVariableGradient & _grad_potential;
  /// Gradient of coupled potential in neighboring cell
  const ADVariableGradient & _grad_potential_neighbor;
};
