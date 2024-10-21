#include "GenericRateConstant.h"
#include "MooseUtils.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("CraneApp", GenericRateConstant);

template <>
InputParameters
validParams<GenericRateConstant>()
{
  InputParameters params = validParams<Material>();
  params.addRequiredParam<std::string>("reaction", "The full reaction equation.");
  params.addRequiredParam<Real>("reaction_rate_value", "The value of the reaction rate (constant).");

  return params;
}

GenericRateConstant::GenericRateConstant(const InputParameters & parameters)
  : Material(parameters),
    _reaction_rate(declareProperty<Real>("k_" + getParam<std::string>("reaction"))),
    _d_k_d_en(declareProperty<Real>("d_k_d_en_"+getParam<std::string>("reaction"))),
    _rate_value(getParam<Real>("reaction_rate_value"))
{
}

void
GenericRateConstant::computeQpProperties()
{
  _reaction_rate[_qp] = _rate_value;
  _d_k_d_en[_qp] = 0.0;
}
