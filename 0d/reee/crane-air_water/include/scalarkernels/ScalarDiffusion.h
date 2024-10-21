#pragma once

#include "ODEKernel.h"
#include "RateCoefficientProvider.h"

class ScalarDiffusion;

template <>
InputParameters validParams<ScalarDiffusion>();

class ScalarDiffusion : public ODEKernel
{
public:
  ScalarDiffusion(const InputParameters & parameters);

protected:
  Real computeQpResidual() override;
  Real computeQpJacobian() override;
  Real computeQpOffDiagJacobian(unsigned int) override;

  Real _rate;
};
