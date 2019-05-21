//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef REACTANTAARXN_H
#define REACTANTAARXN_H

#include "Kernel.h"

// Forward Declaration
class ReactantAARxn;

template <>
InputParameters validParams<ReactantAARxn>();

class ReactantAARxn : public Kernel
{
public:
  ReactantAARxn(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  // The reaction coefficient
  const MaterialProperty<Real> & _reaction_coeff;
};
#endif // REACTANTAARXN_H
