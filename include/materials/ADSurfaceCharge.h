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

/**
 *  Adds a surface charge material property based on the rate of change of the total charged
 *  flux to a boundary. (NOTE: this material is meant to be boundary-restricted.)
 */
class ADSurfaceCharge : public ADMaterial, public DerivativeMaterialPropertyNameInterface
{
public:
  static InputParameters validParams();
  ADSurfaceCharge(const InputParameters & parameters);

protected:
  virtual void computeQpProperties() override;
  virtual void initQpStatefulProperties() override;

  /**
   *  TODO: Add options for different forms of the surface flux
   */
  void computeChargeFlux();
  /// Recombination coefficient for Lymberopoulos-style BCs
  Real _ks;
  /// Ion reflection coefficient for Hagelaar-style BCS
  Real _r_factor_ion;
  /// Electron reflection coefficient for Hagelaar-style BCS
  Real _r_factor_electron;

  /// Surface charge value
  ADMaterialProperty<Real> & _sigma;
  /// Surface charge value during previous time step
  const MaterialProperty<Real> & _sigma_old;
  /// The plasma current on the surface
  MaterialProperty<Real> & _plasma_current;

  /// Position units
  Real _r_units;
  /// Scaling units for the potential (V or kV)
  const std::string _potential_units;
  const ADMaterialProperty<RealVectorValue> & _electric_field;

  /// Number of charged species
  unsigned int _num_species;
  /// Charged species variables
  std::vector<const ADVariableValue *> _species;
  /// Gradient of charged species
  std::vector<const ADVariableGradient *> _grad_species;
  /// Mobility coefficient
  std::vector<const ADMaterialProperty<Real> *> _mu;
  /// Diffusion coefficient
  std::vector<const ADMaterialProperty<Real> *> _diff;
  /// Charge sign of the coupled species
  std::vector<const MaterialProperty<Real> *> _sgn;

  /// Charge flux on the surface
  ADReal _charge_flux;

  /// Scaling value for the potential
  Real _voltage_scaling;
  /// Elementary charge times Avogadro's number
  Real _q_times_NA;
};
