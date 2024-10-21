#include "ReactantFirstOrderLog.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("CraneApp", ReactantFirstOrderLog);

template <>
InputParameters
validParams<ReactantFirstOrderLog>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<std::string>("reaction", "The full reaction equation.");
  params.addRequiredParam<Real>("coefficient", "The stoichiometric coeffient.");
  params.addParam<bool>("diffusion_term", false, "If this is a diffusion term, uses diff_rate.");
  return params;
}

ReactantFirstOrderLog::ReactantFirstOrderLog(const InputParameters & parameters)
  : Kernel(parameters),
    _reaction_coeff(getMaterialProperty<Real>("k_" + getParam<std::string>("reaction"))),
    _stoichiometric_coeff(getParam<Real>("coefficient"))
{
}

Real
ReactantFirstOrderLog::computeQpResidual()
{
  return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * std::exp(_u[_qp]);
}

Real
ReactantFirstOrderLog::computeQpJacobian()
{
  return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * std::exp(_u[_qp]) *
         _phi[_j][_qp];
}

Real
ReactantFirstOrderLog::computeQpOffDiagJacobian(unsigned int)
{
  return 0.0;
}
