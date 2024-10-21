#pragma once

#include "ODEKernel.h"
// #include "RateCoefficientProvider.h"

class Product3BodyScalar;

template <>
InputParameters validParams<Product3BodyScalar>();

class Product3BodyScalar : public ODEKernel
{
public:
  Product3BodyScalar(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  unsigned int _v_var;
  const VariableValue & _v;
  unsigned int _w_var;
  const VariableValue & _w;
  unsigned int _x_var;
  const VariableValue & _x;
  const VariableValue & _rate_coefficient;

  Real _stoichiometric_coeff;
  bool _v_eq_u;
  bool _w_eq_u;
  bool _x_eq_u;
  bool _rate_constant_equation;

  // const RateCoefficientProvider & _data;
};
