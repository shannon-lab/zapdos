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

#include "ElementIntegralIndicator.h"

/**
 *  Returns the difference between the function of the analytic solution
 *  vs the computed solution
 */
class AnalyticalDiffIndicator : public ElementIntegralIndicator
{
public:
  AnalyticalDiffIndicator(const InputParameters & parameters);

  static InputParameters validParams();

  virtual ~AnalyticalDiffIndicator(){};

protected:
  virtual Real computeQpIntegral();

  /// Analytic solution to compare against
  const Function & _func;
};
