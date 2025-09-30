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
 *  The electron flux boundary condition due to field emission
 */
class FieldEmissionBC : public ADIntegratedBC
{
public:
  static InputParameters validParams();

  FieldEmissionBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Scaling units for the position
  const Real _r_units;
  /// Reflection coefficient
  const Real _r;

  /// Number of ions defined
  const unsigned int _num_ions;
  /// Ion density variables
  std::vector<MooseVariable *> _ip_var;
  /// Ion density values
  std::vector<const ADVariableValue *> _ip;
  /// Gradient of ion density values
  std::vector<const ADVariableGradient *> _grad_ip;

  /// Mobility coefficient of the electrons
  const ADMaterialProperty<Real> & _muem;
  /// Mass of electrons
  const MaterialProperty<Real> & _massem;
  /// Charge sign of the ions
  std::vector<const MaterialProperty<Real> *> _sgnip;
  /// Mobility coefficient of the ions
  std::vector<const ADMaterialProperty<Real> *> _muip;
  /// Diffusion coefficient of the ions
  std::vector<const ADMaterialProperty<Real> *> _Dip;
  /// Material name of secondary electron coefficients
  const std::vector<std::string> _se_coeff_names;
  /// Material value of secondary electron coefficient
  std::vector<const ADMaterialProperty<Real> *> _se_coeff;
  /// Work function of material
  const MaterialProperty<Real> & _work_function;
  /// Field enhancement factor of surface
  const MaterialProperty<Real> & _field_enhancement;

  /// The electric field provided as a material property
  const ADMaterialProperty<RealVectorValue> & _electric_field;

  /// Equal to 1 when the drift velocity is direct towards the wall and zero otherwise
  Real _a;
  /// Value of total ion flux
  ADRealVectorValue _ion_flux;
  /// Time constant for ramping the boundary condition
  const Real _tau;
  /// If true use "_tau" to ramp the boundary condition
  bool _relax;
  /// Scaling units for the potential (V or kV)
  const std::string _potential_units;
  /// Scaling value for the potential
  Real _voltage_scaling;

  /// First constant of simplified standard Fowler–Nordheim-type equation
  Real FE_a;
  /// Second constant of simplified standard Fowler–Nordheim-type equation
  Real FE_b;
  /// Third constant of simplified standard Fowler–Nordheim-type equation
  Real FE_c;
  /// correction factor for simplified standard Fowler–Nordheim-type equation
  ADReal v;
  /// Scaled barrier field
  ADReal f;
  /// Current density from field emission
  ADReal jFE;
  /// Current density from secondary electrons
  ADReal jSE;
  /// Local field
  ADReal F;
  /// Ramping coefficient
  Real _relaxation_Expr;
};
