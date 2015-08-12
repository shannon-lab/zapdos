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

#ifndef IONIZATIONSOURCE_H
#define IONIZATIONSOURCE_H

#include "Kernel.h"

// Forward Declaration
class IonizationSource;

template<>
InputParameters validParams<IonizationSource>();

class IonizationSource : public Kernel
{
public:
  IonizationSource(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  //virtual Real computeQpOffDiagJacobian(unsigned int jvar);
  
  // Material properties
  
  const MaterialProperty<RealVectorValue> & _velocity;

  /*  const MaterialProperty<Real> & _ionization_coeff;
  const MaterialProperty<Real> & _velocity_coeff;
  const MaterialProperty<Real> & _ion_activation_energy;
  const MaterialProperty<Real> & _potential_mult; */
  
  // Coupled variables
  
  unsigned int _potential_id;
  
private:
  
  VariableGradient & _grad_potential;

};
#endif //IONIZATIONSOURCE_H
