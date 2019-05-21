//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef PROCRATE_H
#define PROCRATE_H

#include "AuxKernel.h"

class ProcRate;

template <>
InputParameters validParams<ProcRate>();

class ProcRate : public AuxKernel
{
public:
  ProcRate(const InputParameters & parameters);

  virtual ~ProcRate() {}
  virtual Real computeValue();

protected:
  Real _r_units;

  const VariableValue & _em;
  const VariableGradient & _grad_em;
  const VariableGradient & _grad_potential;
  const MaterialProperty<Real> & _muem;
  const MaterialProperty<Real> & _sgnem;
  const MaterialProperty<Real> & _diffem;
  const MaterialProperty<Real> & _alpha;

  RealVectorValue _em_current;
};

#endif // PROCRATE_H
