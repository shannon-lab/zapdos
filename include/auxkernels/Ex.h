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

#ifndef EX_H
#define EX_H

#include "AuxKernel.h"

//Forward Declarations
class Ex;

template<>
InputParameters validParams<Ex>();

/**
 * Constant auxiliary value
 */
class Ex : public AuxKernel
{
public:
  Ex(const InputParameters & parameters);

  virtual ~Ex() {}

protected:
  /**
   * AuxKernels MUST override computeValue.  computeValue() is called on
   * every quadrature point.  For Nodal Auxiliary variables those quadrature
   * points coincide with the nodes.
   */
  virtual Real computeValue();
  
  //int _component;

  /// The gradient of a coupled variable
  VariableGradient & _grad_potential;
};

#endif //EX_H
