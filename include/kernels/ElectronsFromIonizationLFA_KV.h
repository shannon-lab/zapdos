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

#ifndef ELECTRONSFROMIONIZATIONLFA_KV_H
#define ELECTRONSFROMIONIZATIONLFA_KV_H

#include "Kernel.h"

class ElectronsFromIonizationLFA_KV;

template<>
InputParameters validParams<ElectronsFromIonizationLFA_KV>();

class ElectronsFromIonizationLFA_KV : public Kernel
{
public:
  ElectronsFromIonizationLFA_KV(const InputParameters & parameters);
  virtual ~ElectronsFromIonizationLFA_KV();

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  const MaterialProperty<Real> & _diffem;
  const MaterialProperty<Real> & _muem;
  const MaterialProperty<Real> & _iz_coeff_efield_a;
  const MaterialProperty<Real> & _iz_coeff_efield_b;
  const MaterialProperty<Real> & _iz_coeff_efield_c;

  VariableGradient & _grad_potential;
  unsigned int _potential_id;
};


#endif /* ELECTRONSFROMIONIZATIONLFA_KV_H */
