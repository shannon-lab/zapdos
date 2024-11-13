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

/**
 *  Generic second order reaction source term in which two molecules of 
 *  v are produced from two molecules of u 
 *  (Densities must be in logarithmic form)
 */
class ProductAABBRxn : public ADKernel
{
public:
  static InputParameters validParams();

  ProductAABBRxn(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Coupled species density variable
  MooseVariable & _coupled_var;
  /// Coupled species density value
  const ADVariableValue & _v;

  /// Reaction coefficient
  const ADMaterialProperty<Real> & _reaction_coeff;
};
