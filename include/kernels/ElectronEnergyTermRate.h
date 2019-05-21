//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef ELECTRONENERGYTERMRATE_H
#define ELECTRONENERGYTERMRATE_H

#include "Kernel.h"

class ElectronEnergyTermRate;

template <>
InputParameters validParams<ElectronEnergyTermRate>();

class ElectronEnergyTermRate : public Kernel
{
public:
  ElectronEnergyTermRate(const InputParameters & parameters);
  virtual ~ElectronEnergyTermRate();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  Real _r_units;
  bool _elastic;
  Real _threshold_energy;
  Real _energy_change;

  // const MaterialProperty<Real> & _elastic_energy;
  const MaterialProperty<Real> & _n_gas;
  const MaterialProperty<Real> & _rate_coefficient;
  const MaterialProperty<Real> & _d_iz_d_actual_mean_en;

  const VariableValue & _em;
  const VariableValue & _v;
  const VariableGradient & _grad_em;
  unsigned int _em_id;
  unsigned int _v_id;
};

#endif /* ELECTRONENERGYTERMRATE_H */
