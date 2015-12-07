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

  VariableValue & _density_log;
  const MaterialProperty<Real> & _N_A;
};

#endif //DENSITY_H
