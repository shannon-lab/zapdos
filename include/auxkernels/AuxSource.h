#ifndef AUXSOURCE_H
#define AUXSOURCE_H

#include "AuxKernel.h"

class AuxSource;

template<>
InputParameters validParams<AuxSource>();

class AuxSource : public AuxKernel
{
public:
  AuxSource(const InputParameters & parameters);
  
  virtual ~AuxSource() {}
  
protected:

  Real _muem;
  Real _diff;

  VariableValue & _em;
  VariableGradient & _grad_potential;
  VariableGradient & _grad_em;
  virtual Real computeValue();

};

#endif //AUXSOURCE_H
