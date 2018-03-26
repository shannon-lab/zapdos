#include "DriftDiffusionUserDoNothingBC.h"

registerMooseObject("ZapdosApp", DriftDiffusionUserDoNothingBC);

template <>
InputParameters
validParams<DriftDiffusionUserDoNothingBC>()
{
  InputParameters params = validParams<DriftDiffusionDoNothingBC>();
  params.addRequiredParam<Real>("mu", "The mobility.");
  params.addRequiredParam<Real>("diff", "The diffusivity.");
  params.addRequiredParam<Real>("sign", "The charge sign of the drift-diffusing particle.");
  return params;
}

// This diffusion kernel should only be used with species whose values are in the logarithmic form.

DriftDiffusionUserDoNothingBC::DriftDiffusionUserDoNothingBC(const InputParameters & parameters)
  : DriftDiffusionDoNothingBC(parameters)
{
  _mu.resize(_fe_problem.getMaxQps(), Real(getParam<Real>("mu")));
  _diffusivity.resize(_fe_problem.getMaxQps(), Real(getParam<Real>("diff")));
  _sign.resize(_fe_problem.getMaxQps(), Real(getParam<Real>("sign")));
}
