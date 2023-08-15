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

#include "NodalVariablePostprocessor.h"

class AverageNodalDensity : public NodalVariablePostprocessor
{
public:
  AverageNodalDensity(const InputParameters & parameters);

  static InputParameters validParams();

  virtual void initialize() override;
  virtual void finalize() override;
  virtual void execute() override;
  using Postprocessor::getValue;
  virtual PostprocessorValue getValue() const override;
  virtual void threadJoin(const UserObject & y) override;

protected:
  Real _sum;
  unsigned int _n;
};
