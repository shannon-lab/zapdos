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
 *  The electron flux boundary condition due to field ehanced thermionic emission
 *  (Schottky emission)
 */
class SchottkyEmissionBC : public ADIntegratedBC
{
public:
  static InputParameters validParams();

  SchottkyEmissionBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Scaling units for the position
  const Real _r_units;
  /// Reflection coefficient
  const Real _r;
  /// Number of ions defined
  const unsigned int _num_ions;
  /// Material name of secondary electron coefficients
  const std::vector<std::string> _se_coeff_names;
  /// Material value of secondary electron coefficient
  std::vector<const ADMaterialProperty<Real> *> _se_coeff;
  /// Electron mean energy density
  const ADVariableValue & _mean_en;

  /// Ion density variables
  std::vector<MooseVariable *> _ip_var;
  /// Ion density values
  std::vector<const ADVariableValue *> _ip;
  /// Gradient of ion density values
  std::vector<const ADVariableGradient *> _grad_ip;

  /// Charge sign of the ions
  std::vector<const MaterialProperty<Real> *> _sgnip;
  /// Mobility coefficient of the ions
  std::vector<const ADMaterialProperty<Real> *> _muip;
  /// Diffusion coefficient of the ions
  std::vector<const ADMaterialProperty<Real> *> _Dip;

  /// Mass of electrons
  const MaterialProperty<Real> & _massem;
  /// Work function of material
  const MaterialProperty<Real> & _work_function;
  /// Field enhancement factor of surface
  const MaterialProperty<Real> & _field_enhancement;
  /// Richardson coefficient
  const MaterialProperty<Real> & _Richardson_coefficient;
  /// Temperature of surface
  const MaterialProperty<Real> & _cathode_temperature;

  /// Equal to 1 when the drift velocity is direct towards the wall and zero otherwise
  Real _a;
  /// Electron thermal velocity
  ADReal _v_thermal;
  /// Ion flux
  ADRealVectorValue _ion_flux;
  /// Time constant for ramping the boundary condition
  const Real _tau;
  /// If true use "_tau" to ramp the boundary condition
  const bool _relax;

  /// Scaling units for the potential (V or kV)
  const std::string _potential_units;

  /// The electric field provided as a material property
  const ADMaterialProperty<RealVectorValue> & _electric_field;
  /// Scaling value for the potential
  Real _voltage_scaling;

  /// Term for 'dPhi' divided by the local field squared
  Real _dPhi_over_F;
  /// The difference in the work function due to the electric field
  ADReal dPhi;
  /// Boltzmann constant
  Real kB;
  /// Current density from Schottky emission
  ADReal jRD;
  /// Current density from secondary electrons
  ADReal jSE;
  /// Local field
  ADReal F;
  /// Ramping coefficient
  Real _relaxation_Expr;
};
