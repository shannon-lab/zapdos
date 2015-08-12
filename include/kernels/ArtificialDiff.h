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

#ifndef ARTIFICIALDIFF_H
#define ARTIFICIALDIFF_H

// Including the "Diffusion" Kernel here so we can extend it
#include "Diffusion.h"

class ArtificialDiff;

template<>
InputParameters validParams<ArtificialDiff>();


class ArtificialDiff : public Diffusion
{
public:
  ArtificialDiff(const InputParameters & parameters);
  virtual ~ArtificialDiff();

protected:

  virtual Real computeQpResidual();

  virtual Real computeQpJacobian();
  
  // Input Parameters

  const bool & _crosswind;
  const Real & _epsilon;
  
  // Material Properties
  
  const MaterialProperty<RealVectorValue> & _velocity;
  const MaterialProperty<Real> & _tau;
  const MaterialProperty<Real> & _diffusivity;
  
  // Coupled variables

  // VariableGradient & _grad_potential;

  // Variables unique to the kernel

  RealVectorValue  _velocity_h;
  RealVectorValue  _d_velocity_h_d_uj;
  Real  _peclet_num_h;
  Real  _alpha_h;
  Real  _tau_h;
  Real  _sigma;
};


#endif /* ARTIFICIALDIFF_H */
