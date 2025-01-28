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
 *  Produces an elemental auxiliary variable useful for plotting against other
 *  elemental auxiliary variables. Mesh points automatically output by Zapdos only work
 *  for plotting nodal variables. Since almost all auxiliary variables are elemental, this
 *  AuxKernel is very important.
 */
class Position : public AuxKernel
{
public:
  Position(const InputParameters & parameters);

  static InputParameters validParams();

  virtual ~Position() {}

protected:
  /// Component of the position
  int _component;
  /// Scaling units for the position
  Real _r_units;

  virtual Real computeValue() override;
};
