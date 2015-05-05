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
  ArtificialDiff(const std::string & name, InputParameters parameters);
  virtual ~ArtificialDiff();

protected:

  virtual Real computeQpResidual();

  virtual Real computeQpJacobian();
  
  // Input Parameters

  const bool & _crosswind;
  const Real & _epsilon;
  
  // Material Properties
  
  MaterialProperty<RealVectorValue> & _velocity;
  MaterialProperty<Real> & _tau;
  
  // Coupled variables

  // VariableGradient & _grad_potential;
};


#endif /* ARTIFICIALDIFF_H */
