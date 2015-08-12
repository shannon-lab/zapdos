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

  Real _muem;
  Real _diff;

  VariableValue & _em;
  VariableGradient & _grad_potential;
  VariableGradient & _grad_em;
  virtual Real computeValue();

};

#endif //ELECTRONTOTALFLUXMAG_H
