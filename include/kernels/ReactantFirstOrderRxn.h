//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef REACTANTFIRSTORDERRXN_H
#define REACTANTFIRSTORDERRXN_H

#include "Kernel.h"

// Forward Declaration
class ReactantFirstOrderRxn;

template <>
InputParameters validParams<ReactantFirstOrderRxn>();

class ReactantFirstOrderRxn : public Kernel
{
public:
  ReactantFirstOrderRxn(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  // The reaction coefficient
  const MaterialProperty<Real> & _reaction_coeff;
};
#endif // REACTANTFIRSTORDERRXN_H
