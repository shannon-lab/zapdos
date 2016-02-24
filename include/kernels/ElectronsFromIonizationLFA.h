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

#ifndef ELECTRONSFROMIONIZATIONLFA_H
#define ELECTRONSFROMIONIZATIONLFA_H

#include "Kernel.h"

class ElectronsFromIonizationLFA;

template<>
InputParameters validParams<ElectronsFromIonizationLFA>();

class ElectronsFromIonizationLFA : public Kernel
{
public:
  ElectronsFromIonizationLFA(const InputParameters & parameters);
  virtual ~ElectronsFromIonizationLFA();

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  const MaterialProperty<Real> & _diffem;
  const MaterialProperty<Real> & _muem;
  const MaterialProperty<Real> & _iz_coeff_efield_a;
  const MaterialProperty<Real> & _iz_coeff_efield_b;
  const MaterialProperty<Real> & _iz_coeff_efield_c;

  const VariableGradient & _grad_potential;
  unsigned int _potential_id;
};


#endif /* ELECTRONSFROMIONIZATIONLFA_H */
