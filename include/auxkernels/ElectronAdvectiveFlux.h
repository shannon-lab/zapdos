#ifndef ELECTRONADVECTIVEFLUX_H
#define ELECTRONADVECTIVEFLUX_H

#include "AuxKernel.h"

class ElectronAdvectiveFlux;

template<>
InputParameters validParams<ElectronAdvectiveFlux>();

class ElectronAdvectiveFlux : public AuxKernel
{
public:
  ElectronAdvectiveFlux(const InputParameters & parameters);
  
  virtual ~ElectronAdvectiveFlux() {}
  
protected:

  Real _muem;

  VariableValue & _electron_density;
  VariableGradient & _grad_potential;
  virtual Real computeValue();

};

#endif //ELECTRONADVECTIVEFLUX_H
