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

/*
 *  Returns the average nodal differences between two variables
 */
class AverageNodalDifference : public NodalVariablePostprocessor
{
public:
  AverageNodalDifference(const InputParameters & parameters);

  static InputParameters validParams();

  virtual void initialize() override;
  virtual void execute() override;
  using Postprocessor::getValue;
  virtual PostprocessorValue getValue() const override;
  virtual void finalize() override;
  virtual void threadJoin(const UserObject & y) override;

protected:
  /// The coupled variable used to determined the difference
  const VariableValue & _other_var;
  /// The sum of the square of the difference
  Real _sum_of_squared_diff;
  /// The sample size
  Real _n;
  /// The root mean squared of the difference
  Real _value;
};
