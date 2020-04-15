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

  params.addRequiredCoupledVar("density_log", "The electron density");
  params.addRequiredCoupledVar("potential", "The potential");
  params.addParam<bool>(
      "art_diff", false, "Whether there is a current contribution from artificial diffusion.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addClassDescription(
      "Returns the electric current associated with the flux of defined species");
  return params;
}

template <bool is_ad>
CurrentTempl<is_ad>::CurrentTempl(const InputParameters & parameters)
  : AuxKernel(parameters),

    _r_units(1. / getParam<Real>("position_units")),

    _density_var(*getVar("density_log", 0)),
    _density_log(coupledValue("density_log")),
    _grad_density_log(coupledGradient("density_log")),
    _grad_potential(coupledGradient("potential")),
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
  Real r =
      _sgn[_qp] * 1.6e-19 * 6.02e23 *
      (_sgn[_qp] * raw_value(_mu[_qp]) * -_grad_potential[_qp](0) * _r_units *
           std::exp(_density_log[_qp]) -
       raw_value(_diff[_qp]) * std::exp(_density_log[_qp]) * _grad_density_log[_qp](0) * _r_units);

  if (_art_diff)
  {
    Real vd_mag = raw_value(_mu[_qp]) * _grad_potential[_qp].norm() * _r_units;
    Real delta = vd_mag * _current_elem->hmax() / 2.;
    r += _sgn[_qp] * 1.6e-19 * 6.02e23 * -delta * std::exp(_density_log[_qp]) *
         _grad_density_log[_qp](0) * _r_units;
  }

  return r;
}

template class CurrentTempl<false>;
template class CurrentTempl<true>;
