//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "JouleHeating.h"

registerADMooseObject("ZapdosApp", JouleHeating);

InputParameters
JouleHeating::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addRequiredCoupledVar("em", "The electron density.");
  params.addRequiredParam<std::string>("potential_units", "The potential units.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addParam<std::string>("field_property_name",
                               "field_solver_interface_property",
                               "Name of the solver interface material property.");
  params.addClassDescription("Joule heating term for electrons (densities must be in logarithmic "
                             "form), where the Jacobian is "
                             "computed using forward automatic differentiation.");
  return params;
}

JouleHeating::JouleHeating(const InputParameters & parameters)
  : ADKernel(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _potential_units(getParam<std::string>("potential_units")),
    _diff(getADMaterialProperty<Real>("diffem")),
    _mu(getADMaterialProperty<Real>("muem")),
    _electric_field(
        getADMaterialProperty<RealVectorValue>(getParam<std::string>("field_property_name"))),
    _em(adCoupledValue("em")),
    _grad_em(adCoupledGradient("em"))
{
  if (_potential_units.compare("V") == 0)
    _voltage_scaling = 1.;
  else if (_potential_units.compare("kV") == 0)
    _voltage_scaling = 1000.;
  else
    mooseError("Potential units " + _potential_units + " not valid! Use V or kV.");
}

ADReal
JouleHeating::computeQpResidual()
{
  return _test[_i][_qp] * _electric_field[_qp] * _r_units * _voltage_scaling *
         (-_mu[_qp] * _electric_field[_qp] * _r_units * std::exp(_em[_qp]) -
          _diff[_qp] * std::exp(_em[_qp]) * _grad_em[_qp] * _r_units);
}
