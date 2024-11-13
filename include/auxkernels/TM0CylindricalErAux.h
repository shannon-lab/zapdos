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

#include "AuxKernel.h"

/**
 *  Calculates the radial E-field for an axisymmetric TM_0 wave
 */
class TM0CylindricalErAux : public AuxKernel
{
public:
  TM0CylindricalErAux(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeValue() override;

private:
  /// Gradient of the azimuthal component of the magnetic field 
  const VariableGradient & _grad_Hphi;
  /// Angular frequency of the wave
  Real _omega;
  /// Relative permittivity of the medium
  Real _eps_r;
  /// Permittivity of free space
  Real _eps0;
};
