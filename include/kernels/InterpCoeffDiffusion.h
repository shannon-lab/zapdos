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

#ifndef INTERPCOEFFDIFFUSION_H
#define INTERPCOEFFDIFFUSION_H

#include "Diffusion.h"
#include "SplineInterpolation.h"

class InterpCoeffDiffusion;

template<>
InputParameters validParams<InterpCoeffDiffusion>();

class InterpCoeffDiffusion : public Diffusion
{
public:
  InterpCoeffDiffusion(const InputParameters & parameters);
  virtual ~InterpCoeffDiffusion();

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  VariableValue & _v;
  unsigned int _v_id;

  const MaterialProperty<Real> & _diffusivity;
  const MaterialProperty<Real> & _d_diffusivity_d_v;

  // SplineInterpolation _interpolation;
};


#endif /* INTERPCOEFFDIFFUSION_H */
