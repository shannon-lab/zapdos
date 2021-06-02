//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "Current.h"

#include "metaphysicl/raw_type.h"

using MetaPhysicL::raw_value;

registerMooseObject("ZapdosApp", Current);
registerMooseObject("ZapdosApp", ADCurrent);

template <bool is_ad>
InputParameters
CurrentTempl<is_ad>::validParams()
{
  InputParameters params = AuxKernel::validParams();

  params.addRequiredCoupledVar("density_log", "The log of the species density");
  params.addParam<int>(
      "component", 0, "The component of the Current vector. (0 = x, 1 = y, 2 = z)");
  params.addParam<bool>(
      "art_diff", false, "Whether there is a current contribution from artificial diffusion.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addParam<std::string>("field_property_name",
                               "field_solver_interface_property",
                               "Name of the solver interface material property.");
  params.addClassDescription(
      "Returns the electric current associated with the flux of the specified species");
  return params;
}

template <bool is_ad>
CurrentTempl<is_ad>::CurrentTempl(const InputParameters & parameters)
  : AuxKernel(parameters),

    _component(getParam<int>("component")),
    _r_units(1. / getParam<Real>("position_units")),

    _density_var(*getVar("density_log", 0)),
    _density_log(coupledValue("density_log")),
    _grad_density_log(coupledGradient("density_log")),
    _electric_field(
        getADMaterialProperty<RealVectorValue>(getParam<std::string>("field_property_name"))),
    _mu(getGenericMaterialProperty<Real, is_ad>("mu" + _density_var.name())),
    _sgn(getMaterialProperty<Real>("sgn" + _density_var.name())),
    _diff(getGenericMaterialProperty<Real, is_ad>("diff" + _density_var.name())),
    _art_diff(getParam<bool>("art_diff"))
{
}

template <bool is_ad>
Real
CurrentTempl<is_ad>::computeValue()
{
  Real r = _sgn[_qp] * 1.6e-19 * 6.02e23 *
           (_sgn[_qp] * raw_value(_mu[_qp]) * raw_value(_electric_field[_qp](_component)) * _r_units *
                std::exp(_density_log[_qp]) -
            raw_value(_diff[_qp]) * std::exp(_density_log[_qp]) *
                _grad_density_log[_qp](_component) * _r_units);

  if (_art_diff)
  {
    Real vd_mag = raw_value(_mu[_qp]) * raw_value((-_electric_field[_qp]).norm()) * _r_units;
    Real delta = vd_mag * _current_elem->hmax() / 2.;
    r += _sgn[_qp] * 1.6e-19 * 6.02e23 * -delta * std::exp(_density_log[_qp]) *
         _grad_density_log[_qp](_component) * _r_units;
  }

  return r;
}

template class CurrentTempl<false>;
template class CurrentTempl<true>;
