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

#ifndef POTENTIALDRIVENARTIFICIALDIFF_H
#define POTENTIALDRIVENARTIFICIALDIFF_H

// Including the "Diffusion" Kernel here so we can extend it
#include "Kernel.h"

class PotentialDrivenArtificialDiff;

template<>
InputParameters validParams<PotentialDrivenArtificialDiff>();


class PotentialDrivenArtificialDiff : public Kernel
{
public:
  PotentialDrivenArtificialDiff(const InputParameters & parameters);
  virtual ~PotentialDrivenArtificialDiff();

protected:

  virtual Real computeQpResidual();

  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);
  // Input Parameters

  const bool & _consistent;
  const Real & _delta;
  
  // Coupled variables

  VariableGradient & _grad_potential;
  unsigned int _potential_id;
  
  // Material Properties
  
  const MaterialProperty<Real> & _mobility;
  const MaterialProperty<Real> & _diffusivity;

  // Variables unique to the kernel

  RealVectorValue  _advection_velocity;
  Real  _peclet_num;
  Real  _alpha;
  Real  _tau;
};


#endif /* POTENTIALDRIVENARTIFICIALDIFF_H */
