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

#ifndef POTENTIALDRIVENARTIFICIALDIFFENERGY_H
#define POTENTIALDRIVENARTIFICIALDIFFENERGY_H

// Including the "Diffusion" Kernel here so we can extend it
#include "Kernel.h"

class PotentialDrivenArtificialDiffEnergy;

template<>
InputParameters validParams<PotentialDrivenArtificialDiffEnergy>();


class PotentialDrivenArtificialDiffEnergy : public Kernel
{
public:
  PotentialDrivenArtificialDiffEnergy(const InputParameters & parameters);
  virtual ~PotentialDrivenArtificialDiffEnergy();

protected:

  virtual Real computeQpResidual();

  //  virtual Real computeQpJacobian();
  //  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // Input Parameters

  const bool & _consistent;
  const Real & _delta;
  
  // Coupled variables

  VariableGradient & _grad_potential;
  unsigned int _potential_id;
  VariableValue & _em;
  unsigned int _em_id;
  VariableGradient & _grad_em;
  
  // Material Properties
  
  const MaterialProperty<Real> & _mobility_em;

  // Variables unique to the kernel

  RealVectorValue  _advection_velocity;
  Real  _peclet_num;
  Real  _alpha;
  Real  _tau;
  Real _diffusivity;
  Real _mobility_el;
};


#endif /* POTENTIALDRIVENARTIFICIALDIFFENERGY_H */
