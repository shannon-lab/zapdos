#ifndef ELECTRONTOTALFLUXMAG_H
#define ELECTRONTOTALFLUXMAG_H

#include "AuxKernel.h"

class ElectronTotalFluxMag;

template<>
InputParameters validParams<ElectronTotalFluxMag>();

class ElectronTotalFluxMag : public AuxKernel
{
public:
  ElectronTotalFluxMag(const InputParameters & parameters);
  
  virtual ~ElectronTotalFluxMag() {}
  
protected:

  const MaterialProperty<Real> & _muem;
  const MaterialProperty<Real> & _diffem;

  const VariableValue & _em;
  const VariableGradient & _grad_potential;
  const VariableGradient & _grad_em;
  virtual Real computeValue();

};

#endif //ELECTRONTOTALFLUXMAG_H
