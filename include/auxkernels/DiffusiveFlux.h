#ifndef DIFFUSIVEFLUX_H
#define DIFFUSIVEFLUX_H

#include "AuxKernel.h"

class DiffusiveFlux;

template<>
InputParameters validParams<DiffusiveFlux>();

class DiffusiveFlux : public AuxKernel
{
 public:

  DiffusiveFlux(const std::string & name,
		   InputParameters parameters);

 protected:

  virtual Real computeValue();
  
  // Input file scalars
  
  // Material properties

  MaterialProperty<Real> & _diffusivity;
  MaterialProperty<Real> & _electron_mult;
  
  // Coupled variables

 private:
  VariableGradient & _grad_electron_density;
};

#endif //DIFFUSIVEFLUX_H
