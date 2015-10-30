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

#ifndef COUPLEDDIFFUSION_H
#define COUPLEDDIFFUSION_H

// Including the "Diffusion" Kernel here so we can extend it
#include "Diffusion.h"

class CoupledDiffusion;

template<>
InputParameters validParams<CoupledDiffusion>();

class CoupledDiffusion : public Diffusion
{
public:
  CoupledDiffusion(const InputParameters & parameters);
  virtual ~CoupledDiffusion();

protected:

  virtual Real computeQpResidual();


  virtual Real computeQpJacobian();
  const MaterialProperty<Real> & _diffusivity;
  const MaterialProperty<Real> & _d_diffusivity_d_u;
};


#endif /* COUPLEDDIFFUSION_H */
