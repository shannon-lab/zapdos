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

#ifndef ELECTRONSFROMIONIZATION_H
#define ELECTRONSFROMIONIZATION_H

#include "Kernel.h"

class ElectronsFromIonization;

template<>
InputParameters validParams<ElectronsFromIonization>();

class ElectronsFromIonization : public Kernel
{
public:
  ElectronsFromIonization(const InputParameters & parameters);
  virtual ~ElectronsFromIonization();

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  Real _r_units;

  const MaterialProperty<Real> & _diffem;
  const MaterialProperty<Real> & _d_diffem_d_actual_mean_en;
  const MaterialProperty<Real> & _muem;
  const MaterialProperty<Real> & _d_muem_d_actual_mean_en;
  const MaterialProperty<Real> & _alpha_iz;
  const MaterialProperty<Real> & _d_iz_d_actual_mean_en;
  MaterialProperty<Real> _user_diffem;
  MaterialProperty<Real> _user_d_diffem_d_actual_mean_en;
  MaterialProperty<Real> _user_muem;
  MaterialProperty<Real> _user_d_muem_d_actual_mean_en;
  MaterialProperty<Real> _user_alpha_iz;
  MaterialProperty<Real> _user_d_iz_d_actual_mean_en;

  const VariableValue & _mean_en;
  const VariableGradient & _grad_potential;
  VariableGradient _minus_e_field;
  unsigned int _mean_en_id;
  unsigned int _potential_id;
  const VariableValue & _em;
  const VariableGradient & _grad_em;
  unsigned int _em_id;
};


#endif /* ELECTRONSFROMIONIZATION_H */
