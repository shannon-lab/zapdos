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

#ifndef ELECTRONTEMPERATUREDIRICHLETBC_H
#define ELECTRONTEMPERATUREDIRICHLETBC_H

#include "NodalBC.h"

// Forward Declarations
class ElectronTemperatureDirichletBC;

template <>
InputParameters validParams<ElectronTemperatureDirichletBC>();

/**
 * Implements a simple coupled boundary condition where u=v on the boundary.
 */
class ElectronTemperatureDirichletBC : public NodalBC
{
public:
  ElectronTemperatureDirichletBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  const VariableValue & _em;
  unsigned int _em_id;
  Real _value;
  Real _penalty_value;
};

#endif // ElectronTemperatureDirichletBC_H
