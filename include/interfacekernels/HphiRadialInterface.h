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

#include "ADInterfaceKernel.h"

/**
 * DG kernel for interfacing of the axial electic field on adjacent blocks.
 * The axial electric field is related to the azimuthal magnetic flux
 * through using the Ampère–Maxwell law.
 */
class HphiRadialInterface : public ADInterfaceKernel
{
public:
  static InputParameters validParams();

  HphiRadialInterface(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual(Moose::DGResidualType type) override;

  /// The relative permittivity of the neighboring domain
  const ADMaterialProperty<Real> & _eps_r_neighbor;
  /// The relative permittivity of the main domain
  const ADMaterialProperty<Real> & _eps_r;
};
