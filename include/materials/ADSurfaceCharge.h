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

#include "ADMaterial.h"
#include "DerivativeMaterialPropertyNameInterface.h"

class ADSurfaceCharge : public ADMaterial, public DerivativeMaterialPropertyNameInterface
{
public:
  static InputParameters validParams();
  ADSurfaceCharge(const InputParameters & parameters);

protected:
  virtual void computeQpProperties() override;
  virtual void initQpStatefulProperties() override;

  void computeChargeFlux();

  int _bc_type;
  ADMaterialProperty<Real> & _sigma;
  const MaterialProperty<Real> & _sigma_old;
  MaterialProperty<Real> & _plasma_current;

  Real _r_units;
  const std::string _potential_units;
  const ADMaterialProperty<RealVectorValue> & _electric_field;

  unsigned int _num_species;
  std::vector<const ADVariableValue *> _species;
  std::vector<const ADVariableGradient *> _grad_species;
  std::vector<const ADMaterialProperty<Real> *> _mu;
  std::vector<const ADMaterialProperty<Real> *> _diff;
  std::vector<const MaterialProperty<Real> *> _sgn;

  // Recombination coefficient for Lymberopoulos-style BCs
  Real _ks;

  ADReal _charge_flux;

  ADReal _actual_mean_energy;
  ADReal _electron_flux;

  Real _voltage_scaling;
  Real _q_times_NA;
  Real _r_factor_ion;
  Real _r_factor_electron;
};
