#pragma once

#include "ODEKernel.h"
// #include "RateCoefficientProvider.h"

class Reactant2BodyScalar;

template <>
InputParameters validParams<Reactant2BodyScalar>();

class Reactant2BodyScalar : public ODEKernel
{
public:
  Reactant2BodyScalar(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

  unsigned int _v_var;
  const VariableValue & _v;
  const VariableValue & _rate_coefficient;

  Real _stoichiometric_coeff;
  bool _v_eq_u;
  bool _rate_constant_equation;

  // const RateCoefficientProvider & _data;
};
