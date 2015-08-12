#ifndef IONDENSITY_H
#define IONDENSITY_H

#include "AuxKernel.h"

class IonDensity;

template<>
InputParameters validParams<IonDensity>();

class IonDensity : public AuxKernel
{
public:
  IonDensity(const InputParameters & parameters);
  
  virtual ~IonDensity() {}
  
protected:

  virtual Real computeValue();
  
  VariableValue & _ion_density;
};

#endif //IONDENSITY_H
