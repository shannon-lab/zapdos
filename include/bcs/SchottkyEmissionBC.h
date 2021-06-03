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

class SchottkyEmissionBC : public ADIntegratedBC
{
public:
  static InputParameters validParams();

  SchottkyEmissionBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  Real _r_units;
  Real _r;

  // Coupled variables

  const ADVariableGradient & _grad_potential;
  const ADVariableValue & _mean_en;

  MooseVariable & _ip_var;
  const ADVariableValue & _ip;
  const ADVariableGradient & _grad_ip;

  const MaterialProperty<Real> & _massem;
  const MaterialProperty<Real> & _e;
  const MaterialProperty<Real> & _sgnip;
  const ADMaterialProperty<Real> & _muip;
  const ADMaterialProperty<Real> & _Dip;
  const MaterialProperty<Real> & _se_coeff;
  const MaterialProperty<Real> & _work_function;
  const MaterialProperty<Real> & _field_enhancement;
  const MaterialProperty<Real> & _Richardson_coefficient;
  const MaterialProperty<Real> & _cathode_temperature;

  Real _a;
  ADReal _v_thermal;
  ADRealVectorValue _ion_flux;
  Real _tau;
  bool _relax;
  std::string _potential_units;

  // Unique variables

  Real _voltage_scaling;
  Real _dPhi_over_F;
};
