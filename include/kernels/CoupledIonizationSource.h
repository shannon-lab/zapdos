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

#ifndef COUPLEDIONIZATIONSOURCE_H
#define COUPLEDIONIZATIONSOURCE_H

#include "Kernel.h"

// Forward Declaration
class CoupledIonizationSource;

template<>
InputParameters validParams<CoupledIonizationSource>();

class CoupledIonizationSource : public Kernel
{
public:
  CoupledIonizationSource(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);
  
  Real _ionization_coeff;
  
  unsigned int _potential_id;
  unsigned int _electrons_id;
  VariableValue & _electron_density;
  
private:
  
  VariableGradient & _grad_potential;

};
#endif //COUPLEDIONIZATIONSOURCE_H
