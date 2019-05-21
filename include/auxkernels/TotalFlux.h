//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef TOTALFLUX_H
#define TOTALFLUX_H

#include "AuxKernel.h"

class TotalFlux;

template <>
InputParameters validParams<TotalFlux>();

class TotalFlux : public AuxKernel
{
public:
  TotalFlux(const InputParameters & parameters);

  virtual ~TotalFlux() {}
  virtual Real computeValue();

protected:
  MooseVariable & _density_var;
  const VariableValue & _density_log;
  const VariableGradient & _grad_density_log;
  const VariableGradient & _grad_potential;
  const MaterialProperty<Real> & _mu;
  const MaterialProperty<Real> & _sgn;
  const MaterialProperty<Real> & _diff;
};

#endif // TOTALFLUX_H
