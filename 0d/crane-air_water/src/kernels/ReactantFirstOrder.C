#include "ReactantFirstOrder.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("CraneApp", ReactantFirstOrder);

template <>
InputParameters
validParams<ReactantFirstOrder>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<std::string>("reaction", "The full reaction equation.");
  params.addRequiredParam<Real>("coefficient", "The stoichiometric coeffient.");
  return params;
}

ReactantFirstOrder::ReactantFirstOrder(const InputParameters & parameters)
  : Kernel(parameters),
    _reaction_coeff(getMaterialProperty<Real>("k_" + getParam<std::string>("reaction"))),
    // _reaction_coeff(getMaterialProperty<Real>("diffusion_rate")),
    // _n_gas(getMaterialProperty<Real>("n_gas")),
    _stoichiometric_coeff(getParam<Real>("coefficient"))
{
}

Real
ReactantFirstOrder::computeQpResidual()
{
  return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * _u[_qp];
}

Real
ReactantFirstOrder::computeQpJacobian()
{
  return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * _phi[_j][_qp];
}

Real
ReactantFirstOrder::computeQpOffDiagJacobian(unsigned int)
{
  return 0.0;
}
