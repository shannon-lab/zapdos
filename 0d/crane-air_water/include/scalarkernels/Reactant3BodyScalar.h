#pragma once

#include "ODEKernel.h"
// #include "RateCoefficientProvider.h"

class Reactant3BodyScalar;

template <>
InputParameters validParams<Reactant3BodyScalar>();

class Reactant3BodyScalar : public ODEKernel
{
public:
  Reactant3BodyScalar(const InputParameters & parameters);

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
  bool _rate_constant_equation;

  // const RateCoefficientProvider & _data;
};
