#pragma once

#include "ODEKernel.h"
// #include "RateCoefficientProvider.h"

class EnergyTermScalar;

template <>
InputParameters validParams<EnergyTermScalar>();

class EnergyTermScalar : public ODEKernel
{
public:
  EnergyTermScalar(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  Real _energy_change;
  Real _energy_scale;
  unsigned int _v_var;
  const VariableValue & _v;
  unsigned int _w_var;
  const VariableValue & _w;
  const VariableValue & _rate_coefficient;

  Real _n_gas;
  // Real _reaction_coeff;
  bool _v_eq_u;
  bool _w_eq_u;
  bool _rate_constant_equation;

  // const RateCoefficientProvider & _data;
};
