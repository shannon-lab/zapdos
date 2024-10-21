#pragma once

#include "ODEKernel.h"
// #include "RateCoefficientProvider.h"

class Reactant2BodyScalarLog;

template <>
InputParameters validParams<Reactant2BodyScalarLog>();

class Reactant2BodyScalarLog : public ODEKernel
{
public:
  Reactant2BodyScalarLog(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

  unsigned int _v_var;
  const VariableValue & _v;
  const VariableValue & _rate_coefficient;

  Real _stoichiometric_coeff;
  bool _v_eq_u;
  bool _v_coupled;
  bool _rate_constant_equation;

  // const RateCoefficientProvider & _data;
};
