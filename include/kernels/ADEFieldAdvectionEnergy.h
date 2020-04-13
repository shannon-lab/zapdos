//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef ADEFIELDADVECTIONENERGY_H
#define ADEFIELDADVECTIONENERGY_H

#include "ADKernelGrad.h"

class ADEFieldAdvectionEnergy : public ADKernelGrad
{
public:
  ADEFieldAdvectionEnergy(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  ADRealVectorValue precomputeQpResidual() override;

  // Material properties

  Real _r_units;

  const ADMaterialProperty<Real> & _muel;
  const MaterialProperty<Real> & _sign;

private:
  // Coupled variables
  const ADVariableGradient & _grad_potential;
  const ADVariableValue & _em;
};

#endif // ADEFIELDADVECTIONENERGY_H
