//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef EFIELDARTDIFF_H
#define EFIELDARTDIFF_H

// Including the "Diffusion" Kernel here so we can extend it
#include "Kernel.h"

class EFieldArtDiff;

template <>
InputParameters validParams<EFieldArtDiff>();

class EFieldArtDiff : public Kernel
{
public:
  EFieldArtDiff(const InputParameters & parameters);
  virtual ~EFieldArtDiff();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // Coupled variables

  const VariableGradient & _grad_potential;
  unsigned int _potential_id;

  Real _scale;
  Real _r_units;

  // Material Properties

  const MaterialProperty<Real> & _mu;
};

#endif /* EFIELDARTDIFF_H */
