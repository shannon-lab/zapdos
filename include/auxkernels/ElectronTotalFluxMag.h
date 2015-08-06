#ifndef ELECTRONTOTALFLUXMAG_H
#define ELECTRONTOTALFLUXMAG_H

#include "AuxKernel.h"

class ElectronTotalFluxMag;

template<>
InputParameters validParams<ElectronTotalFluxMag>();

class ElectronTotalFluxMag : public AuxKernel
{
public:
  ElectronTotalFluxMag(const std::string & name, InputParameters parameters);
  
  virtual ~ElectronTotalFluxMag() {}
  
protected:

  const MaterialProperty<Real> & _muem;
  const MaterialProperty<Real> & _diffem;

  VariableValue & _em;
  VariableGradient & _grad_potential;
  VariableGradient & _grad_em;
  virtual Real computeValue();

};

#endif //ELECTRONTOTALFLUXMAG_H
