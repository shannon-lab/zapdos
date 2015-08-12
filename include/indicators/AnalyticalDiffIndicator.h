/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef ANALYTICALDIFFINDICATOR_H
#define ANALYTICALDIFFINDICATOR_H

#include "ElementIntegralIndicator.h"

class AnalyticalDiffIndicator;

template<>
InputParameters validParams<AnalyticalDiffIndicator>();

class AnalyticalDiffIndicator :
  public ElementIntegralIndicator
{
public:
  AnalyticalDiffIndicator(const InputParameters & parameters);
  virtual ~AnalyticalDiffIndicator(){};

protected:
  virtual Real computeQpIntegral();

  Function & _func;
};

#endif /* ANALYTICALDIFFINDICATOR_H */
