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

class SakiyamaSecondaryElectronWithEffEfieldBC : public ADIntegratedBC
{
public:
  static InputParameters validParams();

  SakiyamaSecondaryElectronWithEffEfieldBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  Real _r_units;

  // Coupled variables

  const ADVariableValue & _Ex;
  const ADVariableValue & _Ey;
  const ADVariableValue & _Ez;
  std::vector<const ADVariableValue *> _ip;

  Real _a;
  ADRealVectorValue _ion_flux;
  Real _user_se_coeff;

  std::vector<const MaterialProperty<Real> *> _sgnip;
  std::vector<const ADMaterialProperty<Real> *> _muip;

  unsigned int _num_ions;
};
