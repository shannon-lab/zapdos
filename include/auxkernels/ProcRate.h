#ifndef PROCRATE_H
#define PROCRATE_H

#include "AuxKernel.h"

class ProcRate;

template<>
InputParameters validParams<ProcRate>();

class ProcRate : public AuxKernel
{
public:
  ProcRate(const InputParameters & parameters);

  virtual ~ProcRate() {}
  virtual Real computeValue();

protected:
  VariableValue & _em;
  VariableGradient & _grad_em;
  VariableGradient & _grad_potential;
  const MaterialProperty<Real> & _muem;
  const MaterialProperty<Real> & _sgnem;
  const MaterialProperty<Real> & _diffem;
  const MaterialProperty<Real> & _alpha;

  RealVectorValue _em_current;
};

#endif //PROCRATE_H
