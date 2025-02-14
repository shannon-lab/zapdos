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
 *  Similar to AverageNodalVariableValue except meant to
 *  average variables expressed in logarithmic form
 */
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
  /// Sum of the exponential value of the variable
  Real _sum;
  /// The sample size
  unsigned int _n;
};
