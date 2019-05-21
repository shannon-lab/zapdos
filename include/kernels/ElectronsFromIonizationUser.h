//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef ELECTRONSFROMIONIZATIONUSER_H
#define ELECTRONSFROMIONIZATIONUSER_H

#include "ElectronsFromIonization.h"

class ElectronsFromIonizationUser;

template <>
InputParameters validParams<ElectronsFromIonizationUser>();

class ElectronsFromIonizationUser : public ElectronsFromIonization
{
public:
  ElectronsFromIonizationUser(const InputParameters & parameters);

protected:
  MooseArray<Real> _diffem;
  MooseArray<Real> _d_diffem_d_actual_mean_en;
  MooseArray<Real> _muem;
  MooseArray<Real> _d_muem_d_actual_mean_en;
  MooseArray<Real> _alpha_iz;
  MooseArray<Real> _d_iz_d_actual_mean_en;
};

#endif /* ELECTRONSFROMIONIZATIONUSER_H */
