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

class LymberopoulosElectronBC : public ADIntegratedBC
{
public:
  static InputParameters validParams();

  LymberopoulosElectronBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  Real _r_units;
  Real _ks;
  Real _gamma;

  // Coupled variables
  const ADVariableGradient & _grad_potential;
  std::vector<MooseVariable *> _ion_var;
  std::vector<const ADVariableValue *> _ion;

  Real _sign;

  std::vector<const MaterialProperty<Real> *> _sgnion;
  std::vector<const ADMaterialProperty<Real> *> _muion;

  unsigned int _num_ions;
  unsigned int _ip_index;
  std::vector<unsigned int>::iterator _iter;

  ADRealVectorValue _ion_flux;
};
