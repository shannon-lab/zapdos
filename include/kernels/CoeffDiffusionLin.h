//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef COEFFDIFFUSIONLIN_H
#define COEFFDIFFUSIONLIN_H

#include "Diffusion.h"

class CoeffDiffusionLin;

template <>
InputParameters validParams<CoeffDiffusionLin>();

// This diffusion kernel should only be used with species whose values are in the logarithmic form.

class CoeffDiffusionLin : public Diffusion
{
public:
  CoeffDiffusionLin(const InputParameters & parameters);
  virtual ~CoeffDiffusionLin();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  Real _r_units;

  const MaterialProperty<Real> & _diffusivity;
};

#endif /* COEFFDIFFUSIONLIN_H */
