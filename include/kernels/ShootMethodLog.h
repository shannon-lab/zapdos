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

#include "Kernel.h"

class ShootMethodLog;

template <>
InputParameters validParams<ShootMethodLog>();

class ShootMethodLog : public Kernel
{
public:
  ShootMethodLog(const InputParameters & parameters);
  virtual ~ShootMethodLog();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  const VariableValue & _density_at_start_cycle;
  const VariableValue & _density_at_end_cycle;
  const VariableValue & _sensitivity;
  Real _limit;
  Real _acceleration;

};
