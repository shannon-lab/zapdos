#ifndef ELECTRONTEMPERATURE_H
#define ELECTRONTEMPERATURE_H

#include "AuxKernel.h"

class ElectronTemperature;

template<>
InputParameters validParams<ElectronTemperature>();

class ElectronTemperature : public AuxKernel
{
public:
  ElectronTemperature(const InputParameters & parameters);
  
  virtual ~ElectronTemperature() {}
  
protected:

  virtual Real computeValue();
  
  const VariableValue & _electron_density;
  const VariableValue & _mean_en;
};

#endif //ELECTRONTEMPERATURE_H
