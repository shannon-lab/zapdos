#include "ProductFirstOrder.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("CraneApp", ProductFirstOrder);

template <>
InputParameters
validParams<ProductFirstOrder>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("v", "The first variable that is reacting to create u.");
  params.addRequiredParam<std::string>("reaction", "The full reaction equation.");
  params.addRequiredParam<Real>("coefficient", "The stoichiometric coeffient.");
  params.addParam<bool>("_v_eq_u", false, "Whether or not v and u are the same variable.");
  return params;
}

ProductFirstOrder::ProductFirstOrder(const InputParameters & parameters)
  : Kernel(parameters),
    _v(coupledValue("v")),
    _v_id(coupled("v")),
    _reaction_coeff(getMaterialProperty<Real>("k_" + getParam<std::string>("reaction"))),
    _stoichiometric_coeff(getParam<Real>("coefficient")),
    _v_eq_u(getParam<bool>("_v_eq_u"))
{
}

Real
ProductFirstOrder::computeQpResidual()
{
  return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * _v[_qp];
}

Real
ProductFirstOrder::computeQpJacobian()
{
  if (_v_eq_u)
    return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * _phi[_j][_qp];
  else
    return 0.0;
}

Real
ProductFirstOrder::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (!_v_eq_u && jvar == _v_id)
    return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * _phi[_j][_qp];
  else
    return 0.0;
}
