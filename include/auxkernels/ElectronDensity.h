#ifndef ELECTRONDENSITY_H
#define ELECTRONDENSITY_H

#include "AuxKernel.h"

class ElectronDensity;

template<>
InputParameters validParams<ElectronDensity>();

class ElectronDensity : public AuxKernel
{
public:
  ElectronDensity(const InputParameters & parameters);
  
  virtual ~ElectronDensity() {}
  
protected:

  virtual Real computeValue();
  
  VariableValue & _electron_density;
};

#endif //ELECTRONDENSITY_H
