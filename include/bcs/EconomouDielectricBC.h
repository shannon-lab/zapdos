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

/**
 *  Dielectric boundary condition
 */
class EconomouDielectricBC : public ADIntegratedBC
{
public:
  static InputParameters validParams();

  EconomouDielectricBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Scaling units for the position
  const Real _r_units;

  /// Electron mean energy density value
  const ADVariableValue & _mean_en;
  /// Electron density value
  const ADVariableValue & _em;
  /// Ion density variables
  std::vector<MooseVariable *> _ip_var;
  /// Ion density values
  std::vector<const ADVariableValue *> _ip;
  /// Effective ion potential, if needed
  std::vector<const ADVariableValue *> _potential_ion;
  /// Gradient of effective ion potential, if needed
  std::vector<const ADVariableGradient *> _grad_potential_ion;
  /// Time derivative of the gradient of the variable
  const VariableGradient & _grad_u_dot; // TODO: fix this up
  /// Time derivative of the variable
  const ADVariableValue & _u_dot;

  /// Elementary charge
  const MaterialProperty<Real> & _e;
  /// Charge sign of the ions
  std::vector<const MaterialProperty<Real> *> _sgnip;
  /// Mobility coefficient of the ions
  std::vector<const ADMaterialProperty<Real> *> _muip;
  /// Mass of electrons
  const MaterialProperty<Real> & _massem;
  /// Material name of secondary electron coefficients
  const std::vector<std::string> _se_coeff_names;
  /// Material value of secondary electron coefficient
  std::vector<const ADMaterialProperty<Real> *> _user_se_coeff;

  /// Permittivity of the dielectric
  const Real & _epsilon_d;
  /// Thickness of the dielectric
  const Real & _thickness;
  /// Equal to 1 when the drift velocity is direct towards the wall and zero otherwise
  Real _a;
  /// Value of total ion flux
  ADRealVectorValue _ion_flux;
  /// Value of a single ion flux
  ADRealVectorValue _temp_flux;
  /// Electron thermal velocity
  ADReal _v_thermal;
  /// Electron flux
  ADRealVectorValue _em_flux;
  /// Scaling units for the potential (V or kV)
  std::string _potential_units;
  /// Scaling value for the potential
  Real _voltage_scaling;
  /// Number of ions defined
  const unsigned int _num_ions;
};
