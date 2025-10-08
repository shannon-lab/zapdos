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
#include "ProvideMobility.h"

/**
 *  A Neumann boundary condition based on Kirchhoff's law of voltage
 */
class NeumannCircuitVoltageMoles_KV : public ADIntegratedBC
{
public:
  static InputParameters validParams();

  NeumannCircuitVoltageMoles_KV(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Scaling units for the position
  const Real _r_units;
  /// Voltage of the applied circuit
  const Function & _V_bat;
  /// The ProvideMobility UserObject that provides the Coulomb charge, electrode area, and ballast resistance
  const ProvideMobility & _data;

  /// Ion density values
  std::vector<const ADVariableValue *> _ip;
  /// Gradient of ion density values
  std::vector<const ADVariableGradient *> _grad_ip;
  /// Electron mean energy density
  const ADVariableValue & _mean_en;
  /// Electron density
  const ADVariableValue & _em;
  /// Material name of secondary electron coefficients
  const std::vector<std::string> _se_coeff_names;
  /// Material value of secondary electron coefficient
  std::vector<const ADMaterialProperty<Real> *> _se_coeff;
  /// Mobility coefficient of the ions
  std::vector<const ADMaterialProperty<Real> *> _muip;
  /// Charge sign of the ions
  std::vector<const MaterialProperty<Real> *> _sgnip;
  /// Diffusion coefficient of the ions
  std::vector<const ADMaterialProperty<Real> *> _Dip;
  /// Mobility coefficient of electrons
  const ADMaterialProperty<Real> & _muem;
  /// Mass of electrons
  const MaterialProperty<Real> & _massem;
  /// Temperature of ions
  std::vector<const ADVariableValue *> _T_heavy;
  /// Mass of ions
  std::vector<const MaterialProperty<Real> *> _mass;

  /// Scaling units for the potential (V or kV)
  const std::string & _potential_units;
  /// Reflection coefficient
  const Real & _r;

  /// Ion flux
  ADRealVectorValue _ion_flux;
  /// Gamma electron density (electrons emitted by the surface)
  ADReal _n_gamma;
  /// Electron mean energy (in units of eV)
  ADReal _actual_mean_en;
  /// Electron thermal velocity
  ADReal _v_e_th;
  /// Ion thermal velocity
  ADReal _v_i_th;
  /// Equal to 1 when the electron drift velocity is direct towards the wall and zero otherwise
  Real _a;
  /// Equal to 1 when the ion drift velocity is direct towards the wall and zero otherwise
  Real _b;

  /// Scaling value for the potential
  Real _voltage_scaling;

  /// Ion thermal diffusion flux
  ADReal _ion_drift;
  /// Ion drift velocity for secondary electron production
  ADReal _secondary_ion;
  /// Number of ions defined
  const unsigned int _num_ions;
};
