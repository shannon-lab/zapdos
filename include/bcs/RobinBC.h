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

#ifndef ROBINBC_H
#define ROBINBC_H

#include "IntegratedBC.h"


class RobinBC;

template<>
InputParameters validParams<RobinBC>();

/**
 * Implements a simple constant Robin BC where grad(u)=value on the boundary.
 * Uses the term produced from integrating the diffusion operator by parts.
 */
class RobinBC : public IntegratedBC
{
public:
  /**
   * Factory constructor, takes parameters so that all derived classes can be built using the same
   * constructor.
   */
  RobinBC(const InputParameters & parameters);


protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  Real _vx;
};


#endif //ROBINBC_H
