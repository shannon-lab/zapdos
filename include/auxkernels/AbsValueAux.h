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

#include "AuxKernel.h"

/**
 *  Returns the absolute value of the specified variable.
 */
class AbsValueAux : public AuxKernel
{
public:
  AbsValueAux(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeValue() override;

private:

  /// The coupled variable in which to take to absolute value 
  const VariableValue & _u;
};
