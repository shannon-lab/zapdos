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

// Forward Declarations
class AverageNodalDifference;

template <>
InputParameters validParams<AverageNodalDifference>();


class AverageNodalDifference : public NodalVariablePostprocessor
{
public:
  static InputParameters validParams();

  AverageNodalDifference(const InputParameters & parameters);

  virtual void initialize() override;
  virtual void execute() override;
  virtual Real getValue() override;
  virtual void threadJoin(const UserObject & y) override;

protected:

  const VariableValue & _other_var;
  Real _sum_of_squared_diff;
  Real _n;
};
