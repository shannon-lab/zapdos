#pragma once

#include "ODEKernel.h"
// #include "RateCoefficientProvider.h"

class Product1BodyScalarLog;

template <>
InputParameters validParams<Product1BodyScalarLog>();

class Product1BodyScalarLog : public ODEKernel
{
public:
  Product1BodyScalarLog(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  unsigned int _v_var;
  const VariableValue & _v;
  const VariableValue & _rate_coefficient;

  Real _stoichiometric_coeff;
  bool _v_eq_u;
  bool _v_coupled;
  bool _rate_constant_equation;

  // const RateCoefficientProvider & _data;
};
