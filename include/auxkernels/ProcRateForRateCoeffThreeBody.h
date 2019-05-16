#ifndef PROCRATEFORRATECOEFFTHREEBODY_H
#define PROCRATEFORRATECOEFFTHREEBODY_H

#include "AuxKernel.h"

class ProcRateForRateCoeffThreeBody;

template <>
InputParameters validParams<ProcRateForRateCoeffThreeBody>();

class ProcRateForRateCoeffThreeBody : public AuxKernel
{
public:
  ProcRateForRateCoeffThreeBody(const InputParameters & parameters);

  virtual ~ProcRateForRateCoeffThreeBody() {}
  virtual Real computeValue();

protected:


  const VariableValue & _v;
  const VariableValue & _w;
  const VariableValue & _vv;
  const MaterialProperty<Real> & _reaction_coeff;
};

#endif // ProcRateForRateCoeffThreeBody_H
