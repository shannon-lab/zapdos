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

#ifndef ELECTRONENERGYTRANSPORT_H
#define ELECTRONENERGYTRANSPORT_H

#include "Kernel.h"

class ElectronEnergyTransport;

template<>
InputParameters validParams<ElectronEnergyTransport>();

class ElectronEnergyTransport : public Kernel
{
 public:

  ElectronEnergyTransport(const InputParameters & parameters);

 protected:

  virtual Real computeQpResidual();

  virtual Real computeQpJacobian();
  
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);
  
  // Input file scalars
  
  // Material properties

  const MaterialProperty<Real> & _muem;

  // Coupled variables
  
  unsigned int _potential_id;
  VariableGradient & _grad_potential;
  unsigned int _em_id;
  VariableValue & _em;
  VariableGradient & _grad_em;
};

#endif //ELECTRONENERGYTRANSPORT_H
