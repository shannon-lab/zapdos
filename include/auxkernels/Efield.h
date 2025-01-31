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
 * Constant auxiliary value
 */
class Efield : public AuxKernel
{
public:
  Efield(const InputParameters & parameters);

  static InputParameters validParams();

  virtual ~Efield() {}

protected:
  /**
   * AuxKernels MUST override computeValue.  computeValue() is called on
   * every quadrature point.  For Nodal Auxiliary variables those quadrature
   * points coincide with the nodes.
   */
  virtual Real computeValue() override;

  int _component;
  Real _r_units;
  std::string _potential_units;

  const ADMaterialProperty<RealVectorValue> & _electric_field;

  Real _voltage_scaling;
};
