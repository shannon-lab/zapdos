//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef DRIFTDIFFUSIONFLUXAUX_H_
#define DRIFTDIFFUSIONFLUXAUX_H_

#include "AuxKernel.h"

class DriftDiffusionFluxAux;

template <>
InputParameters validParams<DriftDiffusionFluxAux>();

class DriftDiffusionFluxAux : public AuxKernel
{
public:
  DriftDiffusionFluxAux(const InputParameters & parameters);

protected:
  virtual Real computeValue();

private:
  const Real _sgn;
  const VariableGradient & _grad_potential;
  const VariableValue & _u;
  const VariableGradient & _grad_u;
  const int _component;
};

#endif // DRIFTDIFFUSIONFLUXAUX_H
