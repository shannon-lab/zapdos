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
 *  An acceleration scheme based on averaging a density over a periodic cycle
 */
class AccelerationByAveraging : public ADKernel
{
public:
  static InputParameters validParams();
  AccelerationByAveraging(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual();

  /// Density value at the start of a periodic cycle
  const ADVariableValue & _density_at_start_cycle;
  /// Density value at the end of a periodic cycle
  const ADVariableValue & _density_at_end_cycle;
  /// The time of the period (units in s)
  const Real & _time_average;
  /// The time period of acceleration
  const Real & _time_acceleration;
};
