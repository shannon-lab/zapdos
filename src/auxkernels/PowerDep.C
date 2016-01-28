#include "PowerDep.h"

template<>
InputParameters validParams<PowerDep>()
{
  InputParameters params = validParams<AuxKernel>();

  params.addRequiredCoupledVar("density_log","The electron density");
  params.addRequiredCoupledVar("potential","The potential");
  params.addParam<bool>("art_diff",false,"Whether there is a current contribution from artificial diffusion.");
  params.addRequiredParam<std::string>("potential_units", "The potential units.");
  return params;
}

PowerDep::PowerDep(const InputParameters & parameters) :
    AuxKernel(parameters),

    _density_var(*getVar("density_log",0)),
    _density_log(coupledValue("density_log")),
    _grad_density_log(coupledGradient("density_log")),
    _grad_potential(coupledGradient("potential")),
    _mu(getMaterialProperty<Real>("mu" + _density_var.name())),
    _sgn(getMaterialProperty<Real>("sgn" + _density_var.name())),
    _diff(getMaterialProperty<Real>("diff" + _density_var.name())),
    _art_diff(getParam<bool>("art_diff")),
    _potential_units(getParam<std::string>("potential_units")),
    _current(0, 0, 0)
{
  if (_potential_units.compare("V") == 0)
    _voltage_scaling = 1.;
  else if (_potential_units.compare("kV") == 0)
    _voltage_scaling = 1000;
}

Real
PowerDep::computeValue()
{
  _current = _sgn[_qp] * 1.6e-19 * 6.02e23 * (_sgn[_qp] * _mu[_qp] * -_grad_potential[_qp] * std::exp(_density_log[_qp]) - _diff[_qp]* std::exp(_density_log[_qp]) * _grad_density_log[_qp]);

  if (_art_diff)
  {
    Real vd_mag = _mu[_qp] * _grad_potential[_qp].size();
    Real delta = vd_mag * _current_elem->hmax()/2.;
    _current += _sgn[_qp] * 1.6e-19 * 6.02e23 * -delta * std::exp(_density_log[_qp]) * _grad_density_log[_qp];
  }

  return _current * -_grad_potential[_qp] * _voltage_scaling;
}
