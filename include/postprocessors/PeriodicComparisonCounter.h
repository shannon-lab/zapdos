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

/*
 *  Compares two Postprocessors or values and keeps count
 *  of how many cycles in a row that comparision is true.
 */
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

  /// First variable for comparison
  const PostprocessorValue & _value1;
  /// Second variable for comparison
  const PostprocessorValue & _value2;
  /// The type of comparions to perform
  const ComparisonType _comparison_type;
  /// The period of the sample space
  Real _period;
  /// The FE problem base that stores the current simulation time
  FEProblemBase & _feproblem;
  /// The number of consecutive periods where the comparions type was true
  Real _counter;
  /// Total number of periods
  Real _period_counter;
};
