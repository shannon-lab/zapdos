#ifndef EFIELDMAGNITUDESOURCE_H
#define EFIELDMAGNITUDESOURCE_H

#include "Kernel.h"

class EFieldMagnitudeSource;

template <>
InputParameters validParams<EFieldMagnitudeSource>();

class EFieldMagnitudeSource : public Kernel
{
public:
  EFieldMagnitudeSource(const InputParameters & parameters);
  virtual ~EFieldMagnitudeSource();

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

  const VariableGradient & _grad_potential;
  unsigned int _potential_id;
};

#endif /* EFIELDMAGNITUDESOURCE_H */
