#ifndef CHARGEDENSITY_H
#define CHARGEDENSITY_H

#include "AuxKernel.h"

class ChargeDensity;

template<>
InputParameters validParams<ChargeDensity>();

class ChargeDensity : public AuxKernel
{
public:
  ChargeDensity(const std::string & name, InputParameters parameters);
  
  virtual ~ChargeDensity() {}
  
protected:

  virtual Real computeValue();
  
  VariableValue & _electron_density;
  VariableValue & _ion_density;

  MaterialProperty<Real> & _coulomb_charge;
};

#endif //CHARGEDENSITY_H
