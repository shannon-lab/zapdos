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

class LymberopoulosElectronBC;

template <>
InputParameters validParams<LymberopoulosElectronBC>();

class LymberopoulosElectronBC : public IntegratedBC
{
public:
  LymberopoulosElectronBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  Real _r_units;
  Real _ks;
  Real _gamma;

  // Coupled variables
  const VariableGradient & _grad_potential;
  unsigned int _potential_id;
  std::vector<MooseVariable *> _ion_var;
  std::vector<const VariableValue *> _ion;

  Real _sign;

  std::vector<const MaterialProperty<Real> *> _sgnion;
  std::vector<const MaterialProperty<Real> *> _muion;

  std::vector<unsigned int> _ion_id;
  unsigned int _num_ions;
  unsigned int _ip_index;
  std::vector<unsigned int>::iterator _iter;

  RealVectorValue _ion_flux;
  RealVectorValue _d_ion_flux_d_V;
  RealVectorValue _d_ion_flux_d_ion;
};

