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

class EconomouDielectricBC : public ADIntegratedBC
{
public:
  static InputParameters validParams();

  EconomouDielectricBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  const Real _r_units;

  const ADVariableValue & _mean_en;
  const ADVariableValue & _em;
  std::vector<MooseVariable *> _ip_var;
  std::vector<const ADVariableValue *> _ip;
  std::vector<const ADVariableValue *> _potential_ion;
  std::vector<const ADVariableGradient *> _grad_potential_ion;
  const VariableGradient & _grad_u_dot; // TODO: fix this up
  const ADVariableValue & _u_dot;

  const MaterialProperty<Real> & _e;
  std::vector<const MaterialProperty<Real> *> _sgnip;
  std::vector<const ADMaterialProperty<Real> *> _muip;
  const MaterialProperty<Real> & _massem;
  const std::vector<std::string> _se_coeff_names;
  std::vector<const ADMaterialProperty<Real> *> _user_se_coeff;

  const Real & _epsilon_d;
  const Real & _thickness;
  Real _a;
  ADRealVectorValue _ion_flux;
  ADRealVectorValue _temp_flux;
  ADReal _v_thermal;
  ADRealVectorValue _em_flux;
  std::string _potential_units;

  Real _voltage_scaling;

  const unsigned int _num_ions;
};
