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

#ifndef LOGDENSITYDIRICHLETBC_H
#define LOGDENSITYDIRICHLETBC_H

#include "NodalBC.h"

// Forward Declarations
class LogDensityDirichletBC;

template <>
InputParameters validParams<LogDensityDirichletBC>();

/**
 * Implements a simple coupled boundary condition where u=v on the boundary.
 */
class LogDensityDirichletBC : public NodalBC
{
public:
  LogDensityDirichletBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  Real _value;
};

#endif // LogDensityDirichletBC_H
