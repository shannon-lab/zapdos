#include "CircuitDirichletPotential.h"
#include "Function.h"

template<>
InputParameters validParams<CircuitDirichletPotential>()
{
  InputParameters p = validParams<NodalBC>();
  p.addRequiredParam<PostprocessorName>("current", "The postprocessor response for calculating the current passing through the needle surface.");
  p.addRequiredParam<FunctionName>("surface_potential", "The electrical potential applied to the surface if no current was flowing in the circuit.");
  p.addRequiredParam<std::string>("surface", "Whether you are specifying the potential on the anode or the cathode with the requirement that the other metal surface be grounded.");
  return p;
}


CircuitDirichletPotential::CircuitDirichletPotential(const InputParameters & parameters) :
  NodalBC(parameters),
  _current(getPostprocessorValue("current")),
  _surface_potential(getFunction("surface_potential")),
  _surface(getParam<std::string>("surface"))
{
  if (_surface.compare("anode") == 0)
    _current_sign = -1.;
  else if (_surface.compare("cathode") == 0)
    _current_sign = 1.;
}

Real
CircuitDirichletPotential::computeQpResidual()
{
  return _surface_potential.value(_t, *_current_node) - _u[_qp] + _current_sign * _current;
}

Real
CircuitDirichletPotential::computeQpJacobian()
{
  return -1.;
}
