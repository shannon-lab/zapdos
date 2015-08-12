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

#ifndef DIVFREECONVECTION_H
#define DIVFREECONVECTION_H

#include "Kernel.h"

class DivFreeConvection;

template<>
InputParameters validParams<DivFreeConvection>();

class DivFreeConvection : public Kernel
{
public:

  DivFreeConvection(const InputParameters & parameters);

protected:

  virtual Real computeQpResidual();

  virtual Real computeQpJacobian();
  
  // virtual Real computeQpOffDiagJacobian(unsigned int jvar);
  
  // Material Properties
  
  /*  const MaterialProperty<Real> & _velocity_coeff;
      const MaterialProperty<Real> & _potential_mult; */

  const MaterialProperty<RealVectorValue> & _velocity;
  
  // Coupled variables
  
  /*  unsigned int _some_variable_id;

private:

VariableGradient & _grad_some_variable; */

};

#endif //DIVFREECONVECTION_H
