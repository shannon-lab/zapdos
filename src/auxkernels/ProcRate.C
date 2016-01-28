#include "ProcRate.h"

template<>
InputParameters validParams<ProcRate>()
{
  InputParameters params = validParams<AuxKernel>();

  params.addRequiredCoupledVar("em","The electron density");
  params.addRequiredCoupledVar("potential","The potential");
  params.addRequiredParam<std::string>("proc", "The process that we want to get the townsend coefficient for. Options are iz, ex, and el.");
  return params;
}

ProcRate::ProcRate(const InputParameters & parameters) :
    AuxKernel(parameters),

    _em(coupledValue("em")),
    _grad_em(coupledGradient("em")),
    _grad_potential(coupledGradient("potential")),
    _muem(getMaterialProperty<Real>("muem")),
    _sgnem(getMaterialProperty<Real>("sgnem")),
    _diffem(getMaterialProperty<Real>("diffem")),
    _alpha(getMaterialProperty<Real>("alpha_" + getParam<std::string>("proc"))),
    _em_current(0, 0, 0)
{
}

Real
ProcRate::computeValue()
{
  _em_current = 6.02e23 * (_sgnem[_qp] * _muem[_qp] * -_grad_potential[_qp] * std::exp(_em[_qp]) - _diffem[_qp]* std::exp(_em[_qp]) * _grad_em[_qp]);

  return _alpha[_qp] * _em_current.size();
}
