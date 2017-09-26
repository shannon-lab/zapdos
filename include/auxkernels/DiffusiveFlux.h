#ifndef DIFFUSIVEFLUX_H
#define DIFFUSIVEFLUX_H

#include "AuxKernel.h"

class DiffusiveFlux;

template <>
InputParameters validParams<DiffusiveFlux>();

class DiffusiveFlux : public AuxKernel
{
public:
  DiffusiveFlux(const InputParameters & parameters);

protected:
  virtual Real computeValue();

  Real _r_units;

  // Coupled variables

  const VariableGradient & _grad_density_log;
  MooseVariable & _density_var;
  const VariableValue & _density_log;

  // Material properties

  const MaterialProperty<Real> & _diff;
};

#endif // DIFFUSIVEFLUX_H
