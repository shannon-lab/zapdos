#ifndef TM0CYLINDRICALER_H
#define TM0CYLINDRICALER_H

#include "AuxKernel.h"

class TM0CylindricalEr;

template<>
InputParameters validParams<TM0CylindricalEr>();

class TM0CylindricalEr : public AuxKernel
{
 public:

  TM0CylindricalEr(const InputParameters & parameters);

 protected:

  virtual Real computeValue();

 private:
  const VariableGradient & _grad_Hphi;

  Real _omega;
  Real _eps_r;
  Real _eps0;
};

#endif //TM0CYLINDRICALER_H
