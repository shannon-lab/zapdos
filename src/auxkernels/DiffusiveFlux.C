//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "DiffusiveFlux.h"

#include "metaphysicl/raw_type.h"

using MetaPhysicL::raw_value;

registerMooseObject("ZapdosApp", DiffusiveFlux);
registerMooseObject("ZapdosApp", ADDiffusiveFlux);

template <bool is_ad>
InputParameters
DiffusiveFluxTempl<is_ad>::validParams()
{
  InputParameters params = AuxKernel::validParams();
  params.addRequiredCoupledVar("density_log", "The variable representing the log of the density.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addParam<int>("component", 0, "The component of position. (0 = x, 1 = y, 2 = z)");
  params.addClassDescription("Returns the diffusive flux of the specified species");
  return params;
}

template <bool is_ad>
DiffusiveFluxTempl<is_ad>::DiffusiveFluxTempl(const InputParameters & parameters)
  : AuxKernel(parameters),
    _component(getParam<int>("component")),
    _r_units(1. / getParam<Real>("position_units")),

    // Coupled variables

    _grad_density_log(coupledGradient("density_log")),
    _density_var(*getVar("density_log", 0)),
    _density_log(coupledValue("density_log")),

    // Material properties

    _diff(getGenericMaterialProperty<Real, is_ad>("diff" + _density_var.name()))
{
}

template <bool is_ad>
Real
DiffusiveFluxTempl<is_ad>::computeValue()
{
  return -raw_value(_diff[_qp]) * std::exp(_density_log[_qp]) * _grad_density_log[_qp](_component) *
         _r_units * 6.02e23;
}

template class DiffusiveFluxTempl<false>;
template class DiffusiveFluxTempl<true>;
