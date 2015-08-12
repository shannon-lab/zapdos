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

#ifndef NODIFFUSIVEFLUXBC_H
#define NODIFFUSIVEFLUXBC_H

#include "IntegratedBC.h"

class NoDiffusiveFlux;

template<>
InputParameters validParams<NoDiffusiveFlux>();

/**
 * Implements a simple constant NoDiffusiveFlux BC where grad(u)=value on the boundary.
 * Uses the term produced from integrating the diffusion operator by parts.
 */
class NoDiffusiveFlux : public IntegratedBC
{
public:
  /**
   * Factory constructor, takes parameters so that all derived classes can be built using the same
   * constructor.
   */
  NoDiffusiveFlux(const InputParameters & parameters);


protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  // Material Properties

  const MaterialProperty<RealVectorValue> & _velocity;
};


#endif //NODIFFUSIVEFLUXBC_H
