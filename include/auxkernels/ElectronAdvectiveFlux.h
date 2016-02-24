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

  const MaterialProperty<Real> & _muem;
  const VariableValue & _electron_density;
  const VariableGradient & _grad_potential;
  virtual Real computeValue();

};

#endif //ELECTRONADVECTIVEFLUX_H
