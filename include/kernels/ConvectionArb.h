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

#ifndef CONVECTIONARB_H
#define CONVECTIONARB_H

#include "Kernel.h"
#include "MooseParsedVectorFunction.h"
#include "MaterialProperty.h"

// Forward Declaration
class ConvectionArb;

template<>
InputParameters validParams<ConvectionArb>();

/**
 * Simple class to demonstrate off diagonal Jacobian contributions.
 */
class ConvectionArb : public Kernel
{
public:
  ConvectionArb(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();

  virtual Real computeQpJacobian();

  // virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  Function & _velocity;

};

#endif //CONVECTIONARB_H
