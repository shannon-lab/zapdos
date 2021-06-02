//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "PowerDep.h"

#include "metaphysicl/raw_type.h"

using MetaPhysicL::raw_value;

registerMooseObject("ZapdosApp", PowerDep);
registerMooseObject("ZapdosApp", ADPowerDep);

template <bool is_ad>
InputParameters
PowerDepTempl<is_ad>::validParams()
{
  InputParameters params = AuxKernel::validParams();

  params.addRequiredCoupledVar("density_log", "The electron density");
  params.addParam<bool>(
      "art_diff", false, "Whether there is a current contribution from artificial diffusion.");
  params.addRequiredParam<std::string>("potential_units", "The potential units.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addParam<std::string>("field_property_name",
                               "field_solver_interface_property",
                               "Name of the solver interface material property.");
  params.addClassDescription(
      "Amount of power deposited into a user specified specie by Joule Heating");
  return params;
}

template <bool is_ad>
PowerDepTempl<is_ad>::PowerDepTempl(const InputParameters & parameters)
  : AuxKernel(parameters),

    _r_units(1. / getParam<Real>("position_units")),
    _density_var(*getVar("density_log", 0)),
    _density_log(coupledValue("density_log")),
    _grad_density_log(coupledGradient("density_log")),
    _electric_field(
        getADMaterialProperty<RealVectorValue>(getParam<std::string>("field_property_name"))),
    _mu(getGenericMaterialProperty<Real, is_ad>("mu" + _density_var.name())),
    _sgn(getMaterialProperty<Real>("sgn" + _density_var.name())),
    _diff(getGenericMaterialProperty<Real, is_ad>("diff" + _density_var.name())),
    _art_diff(getParam<bool>("art_diff")),
    _potential_units(getParam<std::string>("potential_units")),
    _current(0, 0, 0)
{
  if (_potential_units.compare("V") == 0)
    _voltage_scaling = 1.;
  else if (_potential_units.compare("kV") == 0)
    _voltage_scaling = 1000;
}

template <bool is_ad>
Real
PowerDepTempl<is_ad>::computeValue()
{
  _current =
      _sgn[_qp] * 1.6e-19 * 6.02e23 *
      (_sgn[_qp] * raw_value(_mu[_qp]) * raw_value(_electric_field[_qp]) * _r_units *
           std::exp(_density_log[_qp]) -
       raw_value(_diff[_qp]) * std::exp(_density_log[_qp]) * _grad_density_log[_qp] * _r_units);

  if (_art_diff)
  {
    Real vd_mag = raw_value(_mu[_qp]) * raw_value((-_electric_field[_qp]).norm()) * _r_units;
    Real delta = vd_mag * _current_elem->hmax() / 2.;
    _current += _sgn[_qp] * 1.6e-19 * 6.02e23 * -delta * std::exp(_density_log[_qp]) *
                _grad_density_log[_qp] * _r_units;
  }

  return _current * raw_value(_electric_field[_qp]) * _r_units * _voltage_scaling;
}

template class PowerDepTempl<false>;
template class PowerDepTempl<true>;
