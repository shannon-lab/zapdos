#ifndef TOTALFLUX_H
#define TOTALFLUX_H

#include "AuxKernel.h"

class TotalFlux;

template<>
InputParameters validParams<TotalFlux>();

class TotalFlux : public AuxKernel
{
public:
  TotalFlux(const InputParameters & parameters);
  
  virtual ~TotalFlux() {}
  virtual Real computeValue();
  
protected:
  MooseVariable & _density_var;
  const VariableValue & _density_log;
  const VariableGradient & _grad_density_log;
  const VariableGradient & _grad_potential;
  const MaterialProperty<Real> & _mu;
  const MaterialProperty<Real> & _sgn;
  const MaterialProperty<Real> & _diff;
};

#endif //TOTALFLUX_H
