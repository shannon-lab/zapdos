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

#include "GeneralPostprocessor.h"

class PeriodicComparisonCounter : public GeneralPostprocessor
{
public:
  PeriodicComparisonCounter(const InputParameters & parameters);

  static InputParameters validParams();

  virtual void initialize() override;
  virtual void execute() override;
  using Postprocessor::getValue;
  virtual PostprocessorValue getValue() const override;
  virtual void finalize() override;

protected:
  /// Comparison type
  enum class ComparisonType
  {
    EQUALS,
    GREATER_THAN_EQUALS,
    LESS_THAN_EQUALS,
    GREATER_THAN,
    LESS_THAN
  };

  const PostprocessorValue & _value1;
  const PostprocessorValue & _value2;
  const ComparisonType _comparison_type;
  Real _period;
  FEProblemBase & _feproblem;
  Real _counter;
  Real _period_counter;
};
