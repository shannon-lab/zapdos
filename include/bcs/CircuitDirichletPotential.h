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

#include "ADNodalBC.h"

/**
 * Boundary condition of a Dirichlet type
 *
 * Sets the value at the node to the value of a Postprocessor
 */
class CircuitDirichletPotential : public ADNodalBC
{
public:
  static InputParameters validParams();

  CircuitDirichletPotential(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// The value for this BC
  const PostprocessorValue & _current;
  const Function & _surface_potential;
  std::string _surface;
  Real _resist;
  Real _coulomb_charge;
  Real _N_A;
  std::string _potential_units;
  Real _r_units;
  bool _convert_moles;
  Real _A;

  Real _current_sign;
  Real _voltage_scaling;
};
