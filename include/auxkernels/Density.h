#ifndef DENSITY_H
#define DENSITY_H

#include "AuxKernel.h"

class Density;

template<>
InputParameters validParams<Density>();

class Density : public AuxKernel
{
public:
  Density(const InputParameters & parameters);

  virtual ~Density() {}

protected:

  virtual Real computeValue();

  const VariableValue & _density_log;
};

#endif //DENSITY_H
