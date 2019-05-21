//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef ELECTRONENERGYLOSSFROMELASTIC_H
#define ELECTRONENERGYLOSSFROMELASTIC_H

#include "Kernel.h"

class ElectronEnergyLossFromElastic;

template <>
InputParameters validParams<ElectronEnergyLossFromElastic>();

class ElectronEnergyLossFromElastic : public Kernel
{
public:
  ElectronEnergyLossFromElastic(const InputParameters & parameters);
  virtual ~ElectronEnergyLossFromElastic();

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
  const MaterialProperty<Real> & _massem;
  const MaterialProperty<Real> & _massGas;
  const MaterialProperty<Real> & _alpha_el;
  const MaterialProperty<Real> & _d_el_d_actual_mean_en;

  const VariableGradient & _grad_potential;
  const VariableValue & _em;
  const VariableGradient & _grad_em;
  unsigned int _potential_id;
  unsigned int _em_id;
};

#endif /* ELECTRONENERGYLOSSFROMELASTIC_H */
