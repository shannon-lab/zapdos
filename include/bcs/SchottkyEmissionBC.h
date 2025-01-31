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

  const Real _r_units;
  const Real _r;
  const unsigned int _num_ions;
  const std::vector<std::string> _se_coeff_names;
  std::vector<const ADMaterialProperty<Real> *> _se_coeff;
  // Coupled variables
  const ADVariableValue & _mean_en;

  std::vector<MooseVariable *> _ip_var;
  std::vector<const ADVariableValue *> _ip;
  std::vector<const ADVariableGradient *> _grad_ip;

  std::vector<const MaterialProperty<Real> *> _sgnip;
  std::vector<const ADMaterialProperty<Real> *> _muip;
  std::vector<const ADMaterialProperty<Real> *> _Dip;

  const MaterialProperty<Real> & _massem;
  const MaterialProperty<Real> & _e;
  const MaterialProperty<Real> & _work_function;
  const MaterialProperty<Real> & _field_enhancement;
  const MaterialProperty<Real> & _Richardson_coefficient;
  const MaterialProperty<Real> & _cathode_temperature;

  Real _a;
  ADReal _v_thermal;
  ADRealVectorValue _ion_flux;
  const Real _tau;
  bool _relax;
  std::string _potential_units;

  const ADMaterialProperty<RealVectorValue> & _electric_field;

  // Unique variables

  Real _voltage_scaling;
  Real _dPhi_over_F;
  ADReal dPhi;
  Real kB;
  ADReal jRD;
  ADReal jSE;
  ADReal F;
  Real _relaxation_Expr;
};
