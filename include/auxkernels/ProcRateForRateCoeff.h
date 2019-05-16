#ifndef PROCRATEFORRATECOEFF_H
#define PROCRATEFORRATECOEFF_H

#include "AuxKernel.h"

class ProcRateForRateCoeff;

template <>
InputParameters validParams<ProcRateForRateCoeff>();

class ProcRateForRateCoeff : public AuxKernel
{
public:
  ProcRateForRateCoeff(const InputParameters & parameters);

  virtual ~ProcRateForRateCoeff() {}
  virtual Real computeValue();

protected:


  const VariableValue & _v;
  const VariableValue & _w;
  const MaterialProperty<Real> & _reaction_coeff;
};

#endif // ProcRateForRateCoeff_H
