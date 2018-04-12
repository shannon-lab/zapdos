#ifndef SIGMAMAT_H_
#define SIGMAMAT_H_

#include "Material.h"

class SigmaMat;

template <>
InputParameters validParams<SigmaMat>();

class SigmaMat : public Material
{
public:
  SigmaMat(const InputParameters & parameters);

protected:
  virtual void computeQpProperties() override;
  virtual void initQpStatefulProperties() override;

  MaterialProperty<Real> & _sigma;
  const MaterialProperty<Real> & _sigma_old;

  const VariableValue & _n;
  const VariableGradient & _grad_potential;
};

#endif // SIGMAMAT_H
