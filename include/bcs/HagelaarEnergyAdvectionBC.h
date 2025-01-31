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

  const Real _r_units;
  const Real _r;
  const unsigned int _num_ions;
  // Coupled variables
  std::vector<MooseVariable *> _ip_var;
  std::vector<const ADVariableValue *> _ip;
  std::vector<const ADVariableGradient *> _grad_ip;

  std::vector<const MaterialProperty<Real> *> _sgnip;
  std::vector<const ADMaterialProperty<Real> *> _muip;
  std::vector<const ADMaterialProperty<Real> *> _Dip;
  const std::vector<std::string> _se_coeff_names;
  std::vector<const ADMaterialProperty<Real> *> _se_coeff;
  const Real _se_energy;
  const ADMaterialProperty<Real> & _mumean_en;

  const ADMaterialProperty<RealVectorValue> & _electric_field;

  Real _a;
  ADRealVectorValue _ion_flux;
  Real _v_thermal;
  Real _n_gamma;
  ADReal _bc_val;
};
