//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "Kernel.h"

class ElectronEnergyTermElasticTownsend;

template <>
InputParameters validParams<ElectronEnergyTermElasticTownsend>();

class ElectronEnergyTermElasticTownsend : public Kernel
{
public:
  ElectronEnergyTermElasticTownsend(const InputParameters & parameters);
  virtual ~ElectronEnergyTermElasticTownsend();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  Real _r_units;
  std::string _reaction_coeff_name;
  const MaterialProperty<Real> & _diffem;
  const MaterialProperty<Real> & _muem;
  const MaterialProperty<Real> & _alpha;
  const MaterialProperty<Real> & _d_iz_d_actual_mean_en;
  const MaterialProperty<Real> & _d_muem_d_actual_mean_en;
  const MaterialProperty<Real> & _d_diffem_d_actual_mean_en;
  // const MaterialProperty<Real> & _massem;
  const MaterialProperty<Real> & _massGas;
  const MaterialProperty<Real> & _d_el_d_actual_mean_en;

  const VariableGradient & _grad_potential;
  const VariableValue & _em;
  const VariableGradient & _grad_em;
  unsigned int _potential_id;
  unsigned int _em_id;
  Real _massem;
};
