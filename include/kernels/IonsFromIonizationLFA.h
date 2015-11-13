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

#ifndef IONSFROMIONIZATIONLFA_H
#define IONSFROMIONIZATIONLFA_H

#include "Kernel.h"

class IonsFromIonizationLFA;

template<>
InputParameters validParams<IonsFromIonizationLFA>();

class IonsFromIonizationLFA : public Kernel
{
public:
  IonsFromIonizationLFA(const InputParameters & parameters);
  virtual ~IonsFromIonizationLFA();

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  const MaterialProperty<Real> & _diffem;
  const MaterialProperty<Real> & _muem;
  const MaterialProperty<Real> &  _iz_coeff_efield_a;
  const MaterialProperty<Real> &  _iz_coeff_efield_b;
  const MaterialProperty<Real> &  _iz_coeff_efield_c;

  VariableGradient & _grad_potential;
  VariableValue & _em;
  VariableGradient & _grad_em;
  unsigned int _potential_id;
  unsigned int _em_id;
};


#endif /* IONSFROMIONIZATIONLFA_H */
