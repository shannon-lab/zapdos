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

#ifndef ADVECTIVEFLUX_H
#define ADVECTIVEFLUX_H

#include "AuxKernel.h"

class AdvectiveFlux;

template<>
InputParameters validParams<AdvectiveFlux>();

class AdvectiveFlux : public AuxKernel
{
 public:

  AdvectiveFlux(const InputParameters & parameters);

 protected:

  virtual Real computeValue();
  
  // Input file scalars
  
  // Material properties

  const MaterialProperty<Real> & _mobility;
  const MaterialProperty<Real> & _electron_mult;
  const MaterialProperty<Real> & _potential_mult;
  
  // Coupled variables

 private:
  VariableValue & _electron_density;
  VariableGradient & _grad_potential;
};

#endif //ADVECTIVEFLUX_H
