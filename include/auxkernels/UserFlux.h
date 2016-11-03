#ifndef USERFLUX_H
#define USERFLUX_H

#include "AuxKernel.h"

class UserFlux;

template<>
InputParameters validParams<UserFlux>();

class UserFlux : public AuxKernel
{
public:
  UserFlux(const InputParameters & parameters);

  virtual ~UserFlux() {}
  virtual Real computeValue();

protected:

  const VariableValue & _u;
  const VariableGradient & _grad_u;
  Real _mu;
  Real _diff;
  Real _sign;
  Real _EField;
};

#endif //USERFLUX_H
