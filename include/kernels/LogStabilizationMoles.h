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

#ifndef LOGSTABILIZATIONMOLES_H
#define LOGSTABILIZATIONMOLES_H

#include "Kernel.h"

class LogStabilizationMoles;

template <>
InputParameters validParams<LogStabilizationMoles>();

class LogStabilizationMoles : public Kernel
{
public:
  LogStabilizationMoles(const InputParameters & parameters);
  virtual ~LogStabilizationMoles();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  Real _offset;
};

#endif /* LOGSTABILIZATIONMOLES_H */
