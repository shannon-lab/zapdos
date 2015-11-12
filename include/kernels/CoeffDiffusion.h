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

#ifndef COEFFDIFFUSION_H
#define COEFFDIFFUSION_H

#include "Diffusion.h"

class CoeffDiffusion;

template<>
InputParameters validParams<CoeffDiffusion>();

// This diffusion kernel should only be used with species whose values are in the logarithmic form.

class CoeffDiffusion : public Diffusion
{
public:
  CoeffDiffusion(const InputParameters & parameters);
  virtual ~CoeffDiffusion();

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  const MaterialProperty<Real> & _diffusivity;
};


#endif /* COEFFDIFFUSION_H */
