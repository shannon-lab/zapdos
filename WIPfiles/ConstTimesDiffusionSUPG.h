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

#ifndef CONSTTIMESDIFFUSIONSUPG_H
#define CONSTTIMESDIFFUSIONSUPG_H

// Including the "Diffusion" Kernel here so we can extend it
#include "Diffusion.h"

class ConstTimesDiffusionSUPG;

template<>
InputParameters validParams<ConstTimesDiffusionSUPG>();

class ConstTimesDiffusionSUPG : public Diffusion
{
public:
  ConstTimesDiffusionSUPG(const InputParameters & parameters);
  virtual ~ConstTimesDiffusionSUPG();

protected:

  virtual Real computeQpResidual();


  virtual Real computeQpJacobian();

  MaterialProperty<Real> _alpha;
  MaterialProperty<RealVectorValue> _velocity_norm;
  MaterialProperty<Real> _diffusivity;
};


#endif /* CONSTTIMESDIFFUSIONSUPG_H */
