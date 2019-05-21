//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef COEFFDIFFUSIONENERGY_H
#define COEFFDIFFUSIONENERGY_H

#include "Kernel.h"

class CoeffDiffusionEnergy;

template <>
InputParameters validParams<CoeffDiffusionEnergy>();

// This diffusion kernel should only be used with species whose values are in the logarithmic form.

class CoeffDiffusionEnergy : public Kernel
{
public:
  CoeffDiffusionEnergy(const InputParameters & parameters);
  virtual ~CoeffDiffusionEnergy();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  Real _r_units;

  const MaterialProperty<Real> & _diffel;
  const MaterialProperty<Real> & _d_diffel_d_actual_mean_en;

  const VariableValue & _em;
  unsigned int _em_id;

  Real _d_diffel_d_u;
  Real _d_diffel_d_em;
};

#endif /* COEFFDIFFUSIONENERGY_H */
