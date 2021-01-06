//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef SIGMA_H
#define SIGMA_H

#include "AuxKernel.h"

class Sigma;

template <>
InputParameters validParams<Sigma>();

class Sigma : public AuxKernel
{
public:
  Sigma(const InputParameters & parameters);

  virtual ~Sigma() {}
  virtual Real computeValue() override;

protected:
  const VariableValue & _u_old;
  const VariableValue & _n;
  const VariableGradient & _grad_potential;
};

#endif // SIGMA_H
