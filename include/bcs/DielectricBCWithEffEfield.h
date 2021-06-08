//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "ADIntegratedBC.h"

/**
 * Implements a simple constant Neumann BC where grad(u)=value on the boundary.
 * Uses the term produced from integrating the diffusion operator by parts.
 */
class DielectricBCWithEffEfield : public ADIntegratedBC
{
public:
  static InputParameters validParams();

  DielectricBCWithEffEfield(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  Real _r_units;

  const VariableValue & _u_old;
  const VariableGradient & _grad_u_old;

  const ADVariableValue & _mean_en;
  MooseVariable & _mean_en_var;
  const VariableValue & _mean_en_old;
  const ADVariableValue & _em;
  MooseVariable & _em_var;
  const VariableValue & _em_old;
  const ADVariableValue & _ip;
  MooseVariable & _ip_var;
  const VariableValue & _ip_old;

  const ADVariableValue & _Ex;
  MooseVariable & _Ex_var;
  const VariableValue & _Ex_old;
  const ADVariableValue & _Ey;
  MooseVariable & _Ey_var;
  const VariableValue & _Ey_old;
  const ADVariableValue & _Ez;
  MooseVariable & _Ez_var;
  const VariableValue & _Ez_old;

  const MaterialProperty<Real> & _e;
  const ADMaterialProperty<Real> & _epsilon_0;
  const MaterialProperty<Real> & _N_A;

  const MaterialProperty<Real> & _sgnip;
  const ADMaterialProperty<Real> & _muip;
  const MaterialProperty<Real> & _massem;
  Real _user_se_coeff;

  const Real & _epsilon_d;
  const Real & _thickness;
  Real _a;
  Real _a_old;
  ADRealVectorValue _ion_flux;
  ADRealVectorValue _ion_flux_old;
  ADReal _v_thermal;
  Real _v_thermal_old;
  ADRealVectorValue _em_flux;
  ADRealVectorValue _em_flux_old;
  std::string _potential_units;

  Real _voltage_scaling;
};
