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

#include "ADIntegratedBC.h"

/*
 *  A simple vertical antenna BC of the azimuthal component of the magnetizing field.
 */
class TM0AntennaVertBC : public ADIntegratedBC
{
public:
  static InputParameters validParams();

  TM0AntennaVertBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Angular frequency
  const Real _omega;
  /// Relative permittivity
  const Real _eps_r;
  /// Permittivity of free space
  const Real _eps0;
  /// True if the antenna oscillates in time
  const bool _time_dependent;
};
