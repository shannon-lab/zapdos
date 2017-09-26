#ifndef TM0CYLINDRICALEZAUX_H
#define TM0CYLINDRICALEZAUX_H

#include "AuxKernel.h"

class TM0CylindricalEzAux;

template <>
InputParameters validParams<TM0CylindricalEzAux>();

class TM0CylindricalEzAux : public AuxKernel
{
public:
  TM0CylindricalEzAux(const InputParameters & parameters);

protected:
  virtual Real computeValue();

private:
  const VariableGradient & _grad_Hphi;
  const VariableValue & _Hphi;

  Real _omega;
  Real _eps_r;
  Real _eps0;
};

#endif // TM0CYLINDRICALEZAUX_H
