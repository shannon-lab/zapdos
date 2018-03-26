#include "CircuitDirichletPotential.h"
#include "Function.h"

registerMooseObject("ZapdosApp", CircuitDirichletPotential);

template <>
InputParameters
validParams<CircuitDirichletPotential>()
{
  InputParameters p = validParams<NodalBC>();
  p.addRequiredParam<PostprocessorName>(
      "current",
      "The postprocessor response for calculating the current passing through the needle surface.");
  p.addRequiredParam<FunctionName>(
      "surface_potential",
      "The electrical potential applied to the surface if no current was flowing in the circuit.");
  p.addRequiredParam<std::string>("surface",
                                  "Whether you are specifying the potential on the "
                                  "anode or the cathode with the requirement that the "
                                  "other metal surface be grounded.");
  p.addRequiredParam<Real>("resist", "The ballast resistance in Ohms");
  p.addRequiredParam<Real>("position_units", "Units of position");
  p.addRequiredParam<std::string>("potential_units", "The potential units.");
  p.addRequiredParam<bool>("use_moles", "Whether to convert from units of moles to #.");
  p.addParam<Real>("A",
                   1.,
                   "For 1D calculations, an area has to be passed. This area also must "
                   "match the units convention of position_units.");
  return p;
}

CircuitDirichletPotential::CircuitDirichletPotential(const InputParameters & parameters)
  : NodalBC(parameters),
    _current(getPostprocessorValue("current")),
    _surface_potential(getFunction("surface_potential")),
    _surface(getParam<std::string>("surface")),
    _resist(getParam<Real>("resist")),
    _coulomb_charge(1.6e-19),
    _N_A(6.02e23),
    _potential_units(getParam<std::string>("potential_units")),
    _r_units(1. / getParam<Real>("position_units")),
    _convert_moles(getParam<bool>("use_moles")),
    _A(getParam<Real>("A"))
{
  if (_surface.compare("anode") == 0)
    _current_sign = -1.;
  else if (_surface.compare("cathode") == 0)
    _current_sign = 1.;
  if (_potential_units.compare("V") == 0)
    _voltage_scaling = 1.;
  else if (_potential_units.compare("kV") == 0)
    _voltage_scaling = 1000;
}

Real
CircuitDirichletPotential::computeQpResidual()
{
  if (_convert_moles)
    return _surface_potential.value(_t, *_current_node) - _u[_qp] +
           _current_sign * _current / std::pow(_r_units, 2.) * _resist / _voltage_scaling *
               _coulomb_charge * _A * _N_A;
  else
    return _surface_potential.value(_t, *_current_node) - _u[_qp] +
           _current_sign * _current / std::pow(_r_units, 2.) * _resist / _voltage_scaling *
               _coulomb_charge * _A;
}

Real
CircuitDirichletPotential::computeQpJacobian()
{
  return -1.;
}
