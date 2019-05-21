//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef ELECTRONENERGYTERMELASTICRATE_H
#define ELECTRONENERGYTERMELASTICRATE_H

#include "Kernel.h"

class ElectronEnergyTermElasticRate;

template <>
InputParameters validParams<ElectronEnergyTermElasticRate>();

class ElectronEnergyTermElasticRate : public Kernel
{
public:
  ElectronEnergyTermElasticRate(const InputParameters & parameters);
  virtual ~ElectronEnergyTermElasticRate();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  Real _r_units;

  const MaterialProperty<Real> & _rate_coefficient;
  const MaterialProperty<Real> & _d_iz_d_actual_mean_en;

  const VariableValue & _electron;
  const VariableValue & _target;
  unsigned int _electron_id;
  unsigned int _target_id;

  const MaterialProperty<Real> & _massIncident;
  const MaterialProperty<Real> & _massTarget;
};

#endif /* ELECTRONENERGYTERMELASTICRATE_H */
