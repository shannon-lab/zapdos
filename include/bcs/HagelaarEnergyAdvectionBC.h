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

#include "ADIntegratedBC.h"

class HagelaarEnergyAdvectionBC : public ADIntegratedBC
{
public:
  static InputParameters validParams();

  HagelaarEnergyAdvectionBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  Real _r_units;
  Real _r;

  // Coupled variables

  const ADVariableGradient & _grad_potential;
  MooseVariable & _ip_var;
  const ADVariableValue & _ip;
  const ADVariableGradient & _grad_ip;

  const MaterialProperty<Real> & _sgnip;
  const ADMaterialProperty<Real> & _muip;
  const ADMaterialProperty<Real> & _Dip;
  const MaterialProperty<Real> & _se_coeff;
  const MaterialProperty<Real> & _se_energy;
  const ADMaterialProperty<Real> & _mumean_en;

  Real _a;
  ADRealVectorValue _ion_flux;
  Real _v_thermal;
  Real _n_gamma;
};
