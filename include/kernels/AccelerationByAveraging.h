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

class AccelerationByAveraging : public ADKernel
{
public:
  static InputParameters validParams();
  AccelerationByAveraging(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual();

  const ADVariableValue & _density_at_start_cycle;
  const ADVariableValue & _density_at_end_cycle;
  const Real & _time_average;
  const Real & _time_acceleration;
};
