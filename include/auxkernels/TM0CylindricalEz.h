#ifndef TM0CYLINDRICALEZ_H
#define TM0CYLINDRICALEZ_H

#include "AuxKernel.h"

class TM0CylindricalEz;

template<>
InputParameters validParams<TM0CylindricalEz>();

class TM0CylindricalEz : public AuxKernel
{
 public:

  TM0CylindricalEz(const InputParameters & parameters);

 protected:

  virtual Real computeValue();

 private:
  const VariableGradient & _grad_Hphi;
  const VariableValue & _Hphi;

  Real _omega;
  Real _eps_r;
  Real _eps0;
};

#endif //TM0CYLINDRICALEZ_H
