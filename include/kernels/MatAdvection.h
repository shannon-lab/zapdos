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

#ifndef MATADVECTION_H
#define MATADVECTION_H

#include "Kernel.h"

class MatAdvection;

template<>
InputParameters validParams<MatAdvection>();

class MatAdvection : public Kernel
{
public:

  MatAdvection(const InputParameters & parameters);

protected:

  virtual Real computeQpResidual();

  virtual Real computeQpJacobian();
  
  //virtual Real computeQpOffDiagJacobian(unsigned int jvar);
  
  // Input file scalars
  
  // Material properties
  
  const MaterialProperty<RealVectorValue> & _velocity;
  //  const MaterialProperty<Real> & _velocity_coeff;
  //  const MaterialProperty<Real> & _potential_mult;
  
  // Coupled variables
  
  /*  unsigned int _some_variable_id;

private:

VariableGradient & _grad_some_variable; */
};

#endif //MATADVECTION_H
