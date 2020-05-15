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

class SakiyamaSecondaryElectronBC;

template <>
InputParameters validParams<SakiyamaSecondaryElectronBC>();

class SakiyamaSecondaryElectronBC : public IntegratedBC
{
public:
  SakiyamaSecondaryElectronBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  Real _r_units;

  // Coupled variables

  const VariableGradient & _grad_potential;
  unsigned int _potential_id;
  unsigned int _mean_en_id;
  std::vector<MooseVariable *> _ip_var;
  std::vector<const VariableValue *> _ip;
  std::vector<const VariableGradient *> _gradip;

  Real _a;
  RealVectorValue _ion_flux;
  RealVectorValue _d_ion_flux_d_potential;
  RealVectorValue _d_ion_flux_d_ip;
  Real _actual_mean_en;
  Real _user_se_coeff;

  std::vector<const MaterialProperty<Real> *> _sgnip;
  std::vector<const MaterialProperty<Real> *> _muip;
  std::vector<const MaterialProperty<Real> *> _Tip;
  std::vector<const MaterialProperty<Real> *> _massip;

  std::vector<unsigned int> _ion_id;
  unsigned int _num_ions;
  unsigned int _ip_index;
  std::vector<unsigned int>::iterator _iter;
};
