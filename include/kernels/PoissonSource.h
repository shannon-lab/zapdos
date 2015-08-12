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

#ifndef POISSONSOURCE_H
#define POISSONSOURCE_H

#include "Kernel.h"

// Forward Declaration
class PoissonSource;

template<>
InputParameters validParams<PoissonSource>();

class PoissonSource : public Kernel
{
public:
  PoissonSource(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);
  
  // Material properties
  
  const MaterialProperty<Real> & _permittivity;
  const MaterialProperty<Real> & _e;
  
  // Coupled variables
  
  VariableValue & _Arp;
  VariableValue & _em;
  
  // Coupling identifiers for variables
  
  unsigned int _Arp_id;
  unsigned int _em_id;

};
#endif //POISSONSOURCE_H
