//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef EXCITATIONREACTION_H
#define EXCITATIONREACTION_H

#include "Kernel.h"

class ExcitationReaction;

template <>
InputParameters validParams<ExcitationReaction>();

class ExcitationReaction : public Kernel
{
public:
  ExcitationReaction(const InputParameters & parameters);
  virtual ~ExcitationReaction();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  Real _r_units;
  const MaterialProperty<Real> & _n_gas;
  const MaterialProperty<Real> & _diffem;
  const MaterialProperty<Real> & _muem;
  const MaterialProperty<Real> & _alpha_source;
  // const MaterialProperty<Real> & _alpha_sink;
  const MaterialProperty<Real> & _d_iz_d_actual_mean_en;
  const MaterialProperty<Real> & _d_muem_d_actual_mean_en;
  const MaterialProperty<Real> & _d_diffem_d_actual_mean_en;

  const VariableValue & _mean_en;
  const VariableGradient & _grad_potential;
  const VariableValue & _em;
  const VariableGradient & _grad_em;
  unsigned int _mean_en_id;
  unsigned int _potential_id;
  unsigned int _em_id;

  bool _reactant;
};

#endif /* EXCITATIONREACTION_H */
