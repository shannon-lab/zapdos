#ifndef DENSITYMOLES_H
#define DENSITYMOLES_H

#include "Density.h"

class DensityMoles;

template <>
InputParameters validParams<DensityMoles>();

class DensityMoles : public Density
{
public:
  DensityMoles(const InputParameters & parameters);

  virtual ~DensityMoles() {}

protected:
  virtual Real computeValue() override;

  bool _convert_moles;
  const MaterialProperty<Real> & _N_A;
};

#endif // DENSITYMOLES_H
