
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

// MOOSE includes
#include "SideIntegralVariablePostprocessor.h"

/**
 * This postprocessor computes a side integral of current density.
 */
class SideCurrent : public SideIntegralVariablePostprocessor
{
public:
  SideCurrent(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpIntegral();

  std::string _mobility;
  const MaterialProperty<Real> & _mobility_coef;

  Real _r_units;
  Real _r;
  const MaterialProperty<Real> & _kb;
  const MaterialProperty<Real> & _T_heavy;
  const MaterialProperty<Real> & _mass;
  Real _v_thermal;
  Real _ve_thermal;
  Real _user_velocity;
  const MaterialProperty<Real> & _e;
  const MaterialProperty<Real> & _sgn;
  Real _a;
  Real _b;

  const ADMaterialProperty<RealVectorValue> & _electric_field;

  const VariableValue & _mean_en;
  const VariableValue & _Arp;
  const MaterialProperty<Real> & _muArp;

  unsigned int _num_ions;
  std::vector<const VariableValue *> _ions;
  std::vector<const VariableGradient *> _grad_ions;
  std::vector<const MaterialProperty<Real> *> _mu_ions;
  std::vector<const MaterialProperty<Real> *> _sgn_ions;
  std::vector<const MaterialProperty<Real> *> _mass_ions;
  std::vector<const MaterialProperty<Real> *> _T_ions;

  Real _ion_flux;
};
