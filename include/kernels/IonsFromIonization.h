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

#ifndef IONSFROMIONIZATION_H
#define IONSFROMIONIZATION_H

#include "Kernel.h"

class IonsFromIonization;

template<>
InputParameters validParams<IonsFromIonization>();

class IonsFromIonization : public Kernel
{
public:
  IonsFromIonization(const InputParameters & parameters);
  virtual ~IonsFromIonization();

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  Real _r_units;

  const MaterialProperty<Real> & _diffem;
  const MaterialProperty<Real> & _muem;
  const MaterialProperty<Real> & _alpha_iz;
  const MaterialProperty<Real> & _d_iz_d_actual_mean_en;
  const MaterialProperty<Real> & _d_muem_d_actual_mean_en;
  const MaterialProperty<Real> & _d_diffem_d_actual_mean_en;

  VariableValue & _mean_en;
  VariableGradient & _grad_potential;
  VariableValue & _em;
  VariableGradient & _grad_em;
  unsigned int _mean_en_id;
  unsigned int _potential_id;
  unsigned int _em_id;
};


#endif /* IONSFROMIONIZATION_H */
