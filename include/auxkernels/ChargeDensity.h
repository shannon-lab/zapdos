#ifndef CHARGEDENSITY_H
#define CHARGEDENSITY_H

#include "AuxKernel.h"

class ChargeDensity;

template<>
InputParameters validParams<ChargeDensity>();

class ChargeDensity : public AuxKernel
{
public:
  ChargeDensity(const InputParameters & parameters);
  
  virtual ~ChargeDensity() {}
  
protected:

  virtual Real computeValue();

  Real _e;
  const VariableValue & _electron_density;
  const VariableValue & _ion_density;
};

#endif //CHARGEDENSITY_H
