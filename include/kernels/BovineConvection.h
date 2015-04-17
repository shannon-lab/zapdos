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

#ifndef BOVINECONVECTION_H
#define BOVINECONVECTION_H

#include "Kernel.h"

class BovineConvection;

template<>
InputParameters validParams<BovineConvection>();

class BovineConvection : public Kernel
{
public:

  BovineConvection(const std::string & name,
             InputParameters parameters);

protected:

  virtual Real computeQpResidual();

  virtual Real computeQpJacobian();
  
  //virtual Real computeQpOffDiagJacobian(unsigned int jvar);
  
  // Input file scalars
  
  // Material properties
  
  MaterialProperty<Real> & _velocity_coeff;
  MaterialProperty<Real> & _potential_mult;
  
  // Coupled variables
  
  unsigned int _some_variable_id;

private:

  VariableGradient & _grad_some_variable;
};

#endif //BOVINECONVECTION_H
