//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef LOGSTABILIZATIONMOLES_H
#define LOGSTABILIZATIONMOLES_H

#include "Kernel.h"

class LogStabilizationMoles;

template <>
InputParameters validParams<LogStabilizationMoles>();

class LogStabilizationMoles : public Kernel
{
public:
  LogStabilizationMoles(const InputParameters & parameters);
  virtual ~LogStabilizationMoles();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  Real _offset;
};

#endif /* LOGSTABILIZATIONMOLES_H */
