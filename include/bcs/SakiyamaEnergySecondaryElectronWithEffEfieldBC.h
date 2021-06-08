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

class SakiyamaEnergySecondaryElectronWithEffEfieldBC : public ADIntegratedBC
{
public:
  static InputParameters validParams();

  SakiyamaEnergySecondaryElectronWithEffEfieldBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  Real _r_units;
  bool Te_dependent;

  // Coupled variables
  const ADVariableValue & _Ex;
  const ADVariableValue & _Ey;
  const ADVariableValue & _Ez;

  const ADVariableValue & _em;
  std::vector<MooseVariable *> _ip_var;
  std::vector<const ADVariableValue *> _ip;

  std::vector<const MaterialProperty<Real> *> _sgnip;
  std::vector<const ADMaterialProperty<Real> *> _muip;
  Real _se_coeff;
  Real _user_se_energy;

  Real _a;
  ADReal _se_energy;
  ADRealVectorValue _ion_flux;

  unsigned int _num_ions;
  unsigned int _ip_index;
  std::vector<unsigned int>::iterator _iter;
};
