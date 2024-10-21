#pragma once

#include "ODEKernel.h"

class Product3BodyScalarLog;

template <>
InputParameters validParams<Product3BodyScalarLog>();

class Product3BodyScalarLog : public ODEKernel
{
public:
  Product3BodyScalarLog(const InputParameters & parameters);

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
  // Real _reaction_coeff;
  bool _v_eq_u;
  bool _w_eq_u;
  bool _x_eq_u;
  bool _v_coupled;
  bool _w_coupled;
  bool _x_coupled;
  bool _rate_constant_equation;

  // const RateCoefficientProvider & _data;
};
