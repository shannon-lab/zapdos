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

#ifndef EFIELDARTDIFF_H
#define EFIELDARTDIFF_H

// Including the "Diffusion" Kernel here so we can extend it
#include "Kernel.h"

class EFieldArtDiff;

template<>
InputParameters validParams<EFieldArtDiff>();


class EFieldArtDiff : public Kernel
{
public:
  EFieldArtDiff(const InputParameters & parameters);
  virtual ~EFieldArtDiff();

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // Coupled variables

  VariableGradient & _grad_potential;
  unsigned int _potential_id;
  
  // Material Properties
  
  const MaterialProperty<Real> & _mu;
};


#endif /* EFIELDARTDIFF_H */
