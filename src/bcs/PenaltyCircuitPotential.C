#include "PenaltyCircuitPotential.h"

template<>
InputParameters validParams<PenaltyCircuitPotential>()
{
  InputParameters p = validParams<IntegratedBC>();
  p.addRequiredParam<PostprocessorName>("current", "The postprocessor response for calculating the current passing through the needle surface.");
  p.addRequiredParam<Real>("surface_potential", "The electrical potential applied to the surface if no current was flowing in the circuit.");
  p.addRequiredParam<std::string>("surface", "Whether you are specifying the potential on the anode or the cathode with the requirement that the other metal surface be grounded.");
  p.addRequiredParam<Real>("penalty", "The constant multiplying the penalty term.");
  return p;
}


PenaltyCircuitPotential::PenaltyCircuitPotential(const InputParameters & parameters) :
  IntegratedBC(parameters),
  _current(getPostprocessorValue("current")),
  _surface_potential(getParam<Real>("surface_potential")),
  _surface(getParam<std::string>("surface")),
  _p(getParam<Real>("penalty"))
{
  if (_surface.compare("anode") == 0)
    _current_sign = -1.;
  else if (_surface.compare("cathode") == 0)
    _current_sign = 1.;
}

Real
PenaltyCircuitPotential::computeQpResidual()
{
  return _test[_i][_qp] * _p * (_surface_potential - _u[_qp] + _current_sign * _current);
}

Real
PenaltyCircuitPotential::computeQpJacobian()
{
  return _test[_i][_qp] * _p * -1.;
}
