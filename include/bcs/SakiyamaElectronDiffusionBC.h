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

#include "IntegratedBC.h"

class SakiyamaElectronDiffusionBC;

template <>
InputParameters validParams<SakiyamaElectronDiffusionBC>();

class SakiyamaElectronDiffusionBC : public IntegratedBC
{
public:
  SakiyamaElectronDiffusionBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  Real _r_units;

  // Coupled variables

  const VariableValue & _mean_en;
  unsigned int _mean_en_id;

  const MaterialProperty<Real> & _massem;
  const MaterialProperty<Real> & _e;

  Real _a;
  Real _v_thermal;
  Real _d_v_thermal_d_u;
  Real _d_v_thermal_d_mean_en;
  Real _actual_mean_en;
};
