#ifndef POTENTIALGRADIENTSOURCE_H
#define POTENTIALGRADIENTSOURCE_H

#include "Kernel.h"

class PotentialGradientSource;

template <>
InputParameters validParams<PotentialGradientSource>();

// This diffusion kernel should only be used with species whose values are in the logarithmic form.

class PotentialGradientSource : public Kernel
{
public:
  PotentialGradientSource(const InputParameters & parameters);
  virtual ~PotentialGradientSource();

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

  const VariableGradient & _grad_potential;
  unsigned int _potential_id;
};

#endif /* POTENTIALGRADIENTSOURCE_H */
