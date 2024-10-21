#pragma once

#include "ODEKernel.h"
// #include "RateCoefficientProvider.h"

class Reactant1BodyScalarLog;

template <>
InputParameters validParams<Reactant1BodyScalarLog>();

class Reactant1BodyScalarLog : public ODEKernel
{
public:
  Reactant1BodyScalarLog(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  //virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;
  const VariableValue & _rate_coefficient;
  Real _stoichiometric_coeff;
  bool _rate_constant_equation;

  // const RateCoefficientProvider & _data;
};
