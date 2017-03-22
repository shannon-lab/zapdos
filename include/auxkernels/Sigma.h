#ifndef SIGMA_H
#define SIGMA_H

#include "AuxKernel.h"

class Sigma;

template<>
InputParameters validParams<Sigma>();

class Sigma : public AuxKernel
{
public:
  Sigma(const InputParameters & parameters);

  virtual ~Sigma() {}
  virtual Real computeValue() override;

protected:

  const VariableValue & _n;
  const VariableGradient & _grad_potential;
};

#endif //SIGMA_H
