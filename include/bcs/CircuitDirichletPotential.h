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
 *  Dirichlet circuit boundary condition for potential
 *  (The current is given through an UserObject)
 */
class CircuitDirichletPotential : public ADNodalBC
{
public:
  static InputParameters validParams();

  CircuitDirichletPotential(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Current provided as a postprocessor
  const PostprocessorValue & _current;
  /// Potential applied to the surface
  const Function & _surface_potential;
  /// Is the surface a anode or cathode
  const std::string _surface;
  /// The ballast resistance
  const Real _resist;
  /// Elementary charge being 1.6e-19 C
  const Real _coulomb_charge;
  /// Avogadro's number
  const Real _N_A;
  /// Scaling units for the potential (V or kV)
  const std::string _potential_units;
  /// Scaling units for the position
  const Real _r_units;
  /// True if molar density is used
  const bool _convert_moles;
  /// Area of surface
  const Real _A;

  /// Sign based on anode or cathode surface
  Real _current_sign;
  /// Scaling value for the potential
  Real _voltage_scaling;
};
