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

#ifndef CONSTTIMESDIFFUSION_H
#define CONSTTIMESDIFFUSION_H

// Including the "Diffusion" Kernel here so we can extend it
#include "Diffusion.h"

class ConstTimesDiffusion;

template<>
InputParameters validParams<ConstTimesDiffusion>();

class ConstTimesDiffusion : public Diffusion
{
public:
  ConstTimesDiffusion(const std::string & name, InputParameters parameters);
  virtual ~ConstTimesDiffusion();

protected:

  virtual Real computeQpResidual();


  virtual Real computeQpJacobian();

  MaterialProperty<Real> & _diffusivity;
};


#endif /* CONSTTIMESDIFFUSION_H */
