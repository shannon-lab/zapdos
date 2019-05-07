#include "ProcRateForRateCoeffThreeBody.h"

registerMooseObject("ZapdosApp", ProcRateForRateCoeffThreeBody);

template <>
InputParameters
validParams<ProcRateForRateCoeffThreeBody>()
{
  InputParameters params = validParams<AuxKernel>();

  params.addCoupledVar("v", "The first variable that is reacting to create u.");
  params.addCoupledVar("w", "The second variable that is reacting to create u.");
  params.addCoupledVar("vv", "The second variable that is reacting to create u.");
  params.addRequiredParam<std::string>("reaction", "The full reaction equation.");

  return params;
}

ProcRateForRateCoeffThreeBody::ProcRateForRateCoeffThreeBody(const InputParameters & parameters)
  : AuxKernel(parameters),

  _v(coupledValue("v")),
  _w(coupledValue("w")),
  _vv(coupledValue("vv")),
  _reaction_coeff(getMaterialProperty<Real>("k_" + getParam<std::string>("reaction")))
{
}

Real
ProcRateForRateCoeffThreeBody::computeValue()
{

  return 6.02e23 * _reaction_coeff[_qp] * std::exp(_v[_qp]) * std::exp(_w[_qp]) * std::exp(_vv[_qp]);

}
