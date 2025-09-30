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

#include "Density.h"

/**
 *  Returns physical densities in units of #/m^3
 */
class DensityMoles : public Density
{
public:
  DensityMoles(const InputParameters & parameters);

  static InputParameters validParams();

  virtual ~DensityMoles() {}

protected:
  virtual Real computeValue() override;

  /// True if molar density is used
  const bool _convert_moles;
};
