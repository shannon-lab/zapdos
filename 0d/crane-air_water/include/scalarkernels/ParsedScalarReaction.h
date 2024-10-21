#pragma once

#include "ParsedODEKernel.h"
#include "ParsedScalarReaction.h"
#include "SplineInterpolation.h"

class ParsedScalarReaction;

template <>
InputParameters validParams<ParsedScalarReaction>();

class ParsedScalarReaction : public ParsedODEKernel
{
public:
  ParsedScalarReaction(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

  SplineInterpolation _temperature_interpolation;

  std::string _sampling_format;
  // int _v_var;
  // const VariableValue & _v;
  //
  // Real _n_gas;
  // Real _stoichiometric_coeff;
  // bool _v_eq_u;

};
