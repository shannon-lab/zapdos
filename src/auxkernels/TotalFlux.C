//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "TotalFlux.h"

#include "metaphysicl/raw_type.h"

using MetaPhysicL::raw_value;

registerMooseObject("ZapdosApp", TotalFlux);
registerMooseObject("ZapdosApp", ADTotalFlux);

template <bool is_ad>
InputParameters
TotalFluxTempl<is_ad>::validParams()
{
  InputParameters params = AuxKernel::validParams();

  params.addRequiredCoupledVar("density_log", "The electron density");
  params.addRequiredCoupledVar("potential", "The potential");
  params.addClassDescription("Returns the total flux of defined species");

  return params;
}

template <bool is_ad>
TotalFluxTempl<is_ad>::TotalFluxTempl(const InputParameters & parameters)
  : AuxKernel(parameters),

    _density_var(*getVar("density_log", 0)),
    _density_log(coupledValue("density_log")),
    _grad_density_log(coupledGradient("density_log")),
    _grad_potential(coupledGradient("potential")),
    _mu(getGenericMaterialProperty<Real, is_ad>("mu" + _density_var.name())),
    _sgn(getMaterialProperty<Real>("sgn" + _density_var.name())),
    _diff(getGenericMaterialProperty<Real, is_ad>("diff" + _density_var.name()))
{
}

template <bool is_ad>
Real
TotalFluxTempl<is_ad>::computeValue()
{
  return _sgn[_qp] * raw_value(_mu[_qp]) * -_grad_potential[_qp](0) * std::exp(_density_log[_qp]) -
         raw_value(_diff[_qp]) * std::exp(_density_log[_qp]) * _grad_density_log[_qp](0);
}

template class TotalFluxTempl<false>;
template class TotalFluxTempl<true>;
