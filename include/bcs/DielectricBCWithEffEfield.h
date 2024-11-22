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
 *  Time integrated dielectric boundary condition
 */
class DielectricBCWithEffEfield : public ADIntegratedBC
{
public:
  static InputParameters validParams();

  DielectricBCWithEffEfield(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Scaling units for the position
  Real _r_units;

  /// Variable value during previous time step
  const VariableValue & _u_old;
  /// Gradient of variable during previous time step
  const VariableGradient & _grad_u_old;

  /// Electron mean energy density value
  const ADVariableValue & _mean_en;
  /// Electron mean energy density variable
  MooseVariable & _mean_en_var;
  /// Electron mean energy density value during previous time step
  const VariableValue & _mean_en_old;
  /// Electron density value
  const ADVariableValue & _em;
  /// Electron density variable
  MooseVariable & _em_var;
  /// Electron density value during previous time step
  const VariableValue & _em_old;
  /// Ion density value
  const ADVariableValue & _ip;
  /// Ion density variable
  MooseVariable & _ip_var;
  /// Ion density value during previous time step
  const VariableValue & _ip_old;

  /// x-component of the electric field value
  const ADVariableValue & _Ex;
  /// x-component of the electric field variable
  MooseVariable & _Ex_var;
  /// x-component of the electric field value during previous time step
  const VariableValue & _Ex_old;
  /// y-component of the electric field value
  const ADVariableValue & _Ey;
  /// y-component of the electric field variable
  MooseVariable & _Ey_var;
  /// y-component of the electric field value during previous time step
  const VariableValue & _Ey_old;
  /// z-component of the electric field value
  const ADVariableValue & _Ez;
  /// z-component of the electric field variable
  MooseVariable & _Ez_var;
  /// z-component of the electric field value during previous time step
  const VariableValue & _Ez_old;

  /// Elementary charge
  const MaterialProperty<Real> & _e;
  /// Permittivity of free space
  const ADMaterialProperty<Real> & _epsilon_0;
  /// Avogadro's number
  const MaterialProperty<Real> & _N_A;

  /// Charge sign of the ions
  const MaterialProperty<Real> & _sgnip;
  /// Mobility coefficient of the ions
  const ADMaterialProperty<Real> & _muip;
  /// Mass of electrons
  const MaterialProperty<Real> & _massem;
  /// Secondary electron coefficient
  Real _user_se_coeff;

  /// Permittivity of the dielectric
  const Real & _epsilon_d;
  /// Thickness of the dielectric
  const Real & _thickness;
  /// Equal to 1 when the drift velocity is direct towards the wall and zero otherwise
  Real _a;
  /// Value of "_a" during previous time step
  Real _a_old;
  /// Value of ion flux
  ADRealVectorValue _ion_flux;
  /// Value of ion flux during previous time step
  ADRealVectorValue _ion_flux_old;
  /// Electron thermal velocity
  ADReal _v_thermal;
  /// Value of electron thermal velocity during previous time step
  Real _v_thermal_old;
  /// Electron flux
  ADRealVectorValue _em_flux;
  /// Value of electron flux during previous time step
  ADRealVectorValue _em_flux_old;
  /// Scaling units for the potential (V or kV)
  std::string _potential_units;
  /// Scaling value for the potential
  Real _voltage_scaling;
};
