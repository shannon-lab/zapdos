#ifndef ELECTRONTOTALFLUX_H
#define ELECTRONTOTALFLUX_H

#include "AuxKernel.h"

class ElectronTotalFlux;

template<>
InputParameters validParams<ElectronTotalFlux>();

class ElectronTotalFlux : public AuxKernel
{
public:
  ElectronTotalFlux(const InputParameters & parameters);
  
  virtual ~ElectronTotalFlux() {}
  
protected:

  Real _muem;
  Real _diff;

  VariableValue & _em;
  VariableGradient & _grad_potential;
  VariableGradient & _grad_em;
  virtual Real computeValue();

};

#endif //ELECTRONTOTALFLUX_H
