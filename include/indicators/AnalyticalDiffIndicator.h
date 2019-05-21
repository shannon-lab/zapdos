//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef ANALYTICALDIFFINDICATOR_H
#define ANALYTICALDIFFINDICATOR_H

#include "ElementIntegralIndicator.h"

class AnalyticalDiffIndicator;

template <>
InputParameters validParams<AnalyticalDiffIndicator>();

class AnalyticalDiffIndicator : public ElementIntegralIndicator
{
public:
  AnalyticalDiffIndicator(const InputParameters & parameters);
  virtual ~AnalyticalDiffIndicator(){};

protected:
  virtual Real computeQpIntegral();

  Function & _func;
};

#endif /* ANALYTICALDIFFINDICATOR_H */
