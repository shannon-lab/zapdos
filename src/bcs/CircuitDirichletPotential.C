//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "CircuitDirichletPotential.h"
#include "Zapdos.h"
#include "Function.h"

registerMooseObject("ZapdosApp", CircuitDirichletPotential);

InputParameters
CircuitDirichletPotential::validParams()
{
  InputParameters params = ADNodalBC::validParams();
  params.addRequiredParam<PostprocessorName>(
      "current",
      "The postprocessor response for calculating the current passing through the needle surface.");
  params.addRequiredParam<FunctionName>(
      "surface_potential",
      "The electrical potential applied to the surface if no current was flowing in the circuit.");
  params.addRequiredParam<std::string>("surface",
                                       "Whether you are specifying the potential on the "
                                       "anode or the cathode with the requirement that the "
                                       "other metal surface be grounded.");
  params.addRequiredParam<Real>("resist", "The ballast resistance in Ohms");
  params.addRequiredParam<Real>("position_units", "Units of position");
  params.addRequiredParam<std::string>("potential_units", "The potential units.");
  params.addRequiredParam<bool>("use_moles", "Whether to convert from units of moles to \\#.");
  params.addParam<Real>("A",
                        1.,
                        "For 1D calculations, an area has to be passed. This area also must "
                        "match the units convention of position_units.");
  params.deprecateParam("A", "area", "04/01/2026");
  params.addParam<Real>("area",
                        1.,
                        "For 1D calculations, an area has to be passed. This area also must "
                        "match the units convention of position_units.");
  params.addClassDescription("Dirichlet circuit boundary condition for potential"
                             " (The current is given through a UserObject)");
  return params;
}

CircuitDirichletPotential::CircuitDirichletPotential(const InputParameters & parameters)
  : ADNodalBC(parameters),
    _current(getPostprocessorValue("current")),
    _surface_potential(getFunction("surface_potential")),
    _surface(getParam<std::string>("surface")),
    _resist(getParam<Real>("resist")),
    _potential_units(getParam<std::string>("potential_units")),
    _r_units(1. / getParam<Real>("position_units")),
    _convert_moles(getParam<bool>("use_moles")),
    _A(getParam<Real>("area"))
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

ADReal
CircuitDirichletPotential::computeQpResidual()
{
  if (_convert_moles)
    return _surface_potential.value(_t, *_current_node) - _u +
           _current_sign * _current / std::pow(_r_units, 2.) * _resist / _voltage_scaling *
               ZAPDOS_CONSTANTS::e * _A * ZAPDOS_CONSTANTS::N_A;
  else
    return _surface_potential.value(_t, *_current_node) - _u +
           _current_sign * _current / std::pow(_r_units, 2.) * _resist / _voltage_scaling *
               ZAPDOS_CONSTANTS::e * _A;
}
