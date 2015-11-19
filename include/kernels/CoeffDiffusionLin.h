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

#ifndef COEFFDIFFUSIONLIN_H
#define COEFFDIFFUSIONLIN_H

#include "Diffusion.h"

class CoeffDiffusionLin;

template<>
InputParameters validParams<CoeffDiffusionLin>();

// This diffusion kernel should only be used with species whose values are in the logarithmic form.

class CoeffDiffusionLin : public Diffusion
{
public:
  CoeffDiffusionLin(const InputParameters & parameters);
  virtual ~CoeffDiffusionLin();

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  const MaterialProperty<Real> & _diffusivity;
};


#endif /* COEFFDIFFUSIONLIN_H */
