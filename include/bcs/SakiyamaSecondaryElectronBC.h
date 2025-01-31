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

class SakiyamaSecondaryElectronBC : public ADIntegratedBC
{
public:
  static InputParameters validParams();

  SakiyamaSecondaryElectronBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  const Real _r_units;
  const unsigned int _num_ions;
  const std::vector<std::string> _se_coeff_names;
  std::vector<const ADMaterialProperty<Real> *> _se_coeff;
  // Coupled variables
  std::vector<const ADVariableValue *> _ip;

  Real _a;
  ADRealVectorValue _ion_flux;

  std::vector<const MaterialProperty<Real> *> _sgnip;
  std::vector<const ADMaterialProperty<Real> *> _muip;

  const ADMaterialProperty<RealVectorValue> & _electric_field;
};
