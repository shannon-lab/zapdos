//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "EFieldAdvAux.h"

#include "metaphysicl/raw_type.h"

using MetaPhysicL::raw_value;

registerMooseObject("ZapdosApp", EFieldAdvAux);
registerMooseObject("ZapdosApp", ADEFieldAdvAux);

template <bool is_ad>
InputParameters
EFieldAdvAuxTempl<is_ad>::validParams()
{
  InputParameters params = AuxKernel::validParams();
  params.addRequiredCoupledVar(
      "potential", "The gradient of the potential will be used to compute the advection velocity.");
  params.addRequiredCoupledVar("density_log", "The variable representing the log of the density.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addClassDescription("Returns the electric field driven advective flux of defined species");
  return params;
}

template <bool is_ad>
EFieldAdvAuxTempl<is_ad>::EFieldAdvAuxTempl(const InputParameters & parameters)
  : AuxKernel(parameters),
    _r_units(1. / getParam<Real>("position_units")),

    // Coupled variables

    _density_var(*getVar("density_log", 0)),
    _density_log(coupledValue("density_log")),
    _grad_potential(coupledGradient("potential")),

    // Material properties

    _mu(getGenericMaterialProperty<Real, is_ad>("mu" + _density_var.name())),
    _sgn(getMaterialProperty<Real>("sgn" + _density_var.name()))
{
}

template <bool is_ad>
Real
EFieldAdvAuxTempl<is_ad>::computeValue()
{
  return _sgn[_qp] * raw_value(_mu[_qp]) * std::exp(_density_log[_qp]) * -_grad_potential[_qp](0) *
         _r_units * 6.02e23;
}

template class EFieldAdvAuxTempl<false>;
template class EFieldAdvAuxTempl<true>;
