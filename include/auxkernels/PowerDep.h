//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef POWERDEP_H
#define POWERDEP_H

#include "AuxKernel.h"

class PowerDep;

template <>
InputParameters validParams<PowerDep>();

class PowerDep : public AuxKernel
{
public:
  PowerDep(const InputParameters & parameters);

  virtual ~PowerDep() {}
  virtual Real computeValue();

protected:
  Real _r_units;

  MooseVariable & _density_var;
  const VariableValue & _density_log;
  const VariableGradient & _grad_density_log;
  const VariableGradient & _grad_potential;
  const MaterialProperty<Real> & _mu;
  const MaterialProperty<Real> & _sgn;
  const MaterialProperty<Real> & _diff;
  bool _art_diff;
  std::string _potential_units;
  RealVectorValue _current;
  Real _voltage_scaling;
};

#endif // POWERDEP_H
