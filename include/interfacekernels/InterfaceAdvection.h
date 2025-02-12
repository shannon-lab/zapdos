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

#include "ADInterfaceKernel.h"

/**
 * DG kernel for interfacing advection on adjacent blocks
 */
class InterfaceAdvection : public ADInterfaceKernel
{
public:
  static InputParameters validParams();

  InterfaceAdvection(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual(Moose::DGResidualType type) override;

  Real _r_units;
  Real _r_neighbor_units;

  const ADMaterialProperty<RealVectorValue> & _electric_field_neighbor;
  MooseVariable & _mean_en_neighbor_var;
  const ADVariableValue & _mean_en_neighbor;

  const ADMaterialProperty<Real> & _mu_neighbor;
  const MaterialProperty<Real> & _sgn_neighbor;
};
