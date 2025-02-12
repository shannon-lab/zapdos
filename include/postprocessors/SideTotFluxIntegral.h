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
 * This postprocessor computes a side integral of the mass flux.
 */
class SideTotFluxIntegral : public SideIntegralVariablePostprocessor
{
public:
  SideTotFluxIntegral(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpIntegral();

  /* std::string _diffusivity; */
  /* const MaterialProperty<Real> & _diffusion_coef; */
  std::string _mobility;
  const MaterialProperty<Real> & _mobility_coef;

  Real _r_units;
  Real _r;
  const MaterialProperty<Real> & _kb;
  const MaterialProperty<Real> & _T_heavy;
  const MaterialProperty<Real> & _mass;
  Real _v_thermal;
  Real _user_velocity;
  const MaterialProperty<Real> & _e;
  const MaterialProperty<Real> & _sgn;
  Real _a;

  const ADMaterialProperty<RealVectorValue> & _electric_field;
};
