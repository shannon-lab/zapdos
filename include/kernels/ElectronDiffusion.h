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

#ifndef ELECTRONDIFFUSION_H
#define ELECTRONDIFFUSION_H

// Including the "Diffusion" Kernel here so we can extend it
#include "Diffusion.h"

class ElectronDiffusion;

template<>
InputParameters validParams<ElectronDiffusion>();

class ElectronDiffusion : public Diffusion
{
public:
  ElectronDiffusion(const InputParameters & parameters);
  virtual ~ElectronDiffusion();

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // Material Properties

  const MaterialProperty<Real> & _muem;

  // Coupled Variables

  VariableValue & _Te;
  unsigned int _Te_id;

  // Unique variables
};


#endif /* ELECTRONDIFFUSION_H */
