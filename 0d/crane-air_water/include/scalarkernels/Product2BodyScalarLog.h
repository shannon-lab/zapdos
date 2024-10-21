#pragma once

#include "ODEKernel.h"
// #include "RateCoefficientProvider.h"

class Product2BodyScalarLog;

template <>
InputParameters validParams<Product2BodyScalarLog>();

class Product2BodyScalarLog : public ODEKernel
{
public:
  Product2BodyScalarLog(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  unsigned int _v_var;
  const VariableValue & _v;
  unsigned int _w_var;
  const VariableValue & _w;
  const VariableValue & _rate_coefficient;

  Real _stoichiometric_coeff;
  // Real _reaction_coeff;
  bool _v_eq_u;
  bool _w_eq_u;
  bool _v_coupled;
  bool _w_coupled;
  bool _rate_constant_equation;

  // const RateCoefficientProvider & _data;
};
