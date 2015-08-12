#ifndef DIFFUSIVEFLUX_H
#define DIFFUSIVEFLUX_H

#include "AuxKernel.h"

class DiffusiveFlux;

template<>
InputParameters validParams<DiffusiveFlux>();

class DiffusiveFlux : public AuxKernel
{
 public:

  DiffusiveFlux(const InputParameters & parameters);

 protected:

  virtual Real computeValue();
  
  // Input file scalars
  
  // Material properties

  const MaterialProperty<Real> & _diffusivity;
  const MaterialProperty<Real> & _electron_mult;
  
  // Coupled variables

 private:
  VariableGradient & _grad_electron_density;
};

#endif //DIFFUSIVEFLUX_H
