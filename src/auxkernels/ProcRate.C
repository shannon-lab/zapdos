//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ProcRate.h"

#include "metaphysicl/raw_type.h"

using MetaPhysicL::raw_value;

registerMooseObject("ZapdosApp", ProcRate);
registerMooseObject("ZapdosApp", ADProcRate);

template <bool is_ad>
InputParameters
ProcRateTempl<is_ad>::validParams()
{
  InputParameters params = AuxKernel::validParams();

  params.addRequiredCoupledVar("em", "The electron density");
  params.addRequiredParam<std::string>(
      "proc",
      "The process that we want to get the townsend coefficient for. Options are iz, ex, and el.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addParam<std::string>("field_property_name",
                               "field_solver_interface_property",
                               "Name of the solver interface material property.");
  params.addClassDescription(
      "Reaction rate for electron impact collisions in units of #/m$^{3}$s. User can pass "
      "choice of elastic, excitation, or ionization Townsend coefficients");
  return params;
}

template <bool is_ad>
ProcRateTempl<is_ad>::ProcRateTempl(const InputParameters & parameters)
  : AuxKernel(parameters),

    _r_units(1. / getParam<Real>("position_units")),
    _em(coupledValue("em")),
    _grad_em(coupledGradient("em")),
    _electric_field(
        getADMaterialProperty<RealVectorValue>(getParam<std::string>("field_property_name"))),
    _muem(getGenericMaterialProperty<Real, is_ad>("muem")),
    _sgnem(getMaterialProperty<Real>("sgnem")),
    _diffem(getGenericMaterialProperty<Real, is_ad>("diffem")),
    _alpha(getGenericMaterialProperty<Real, is_ad>("alpha_" + getParam<std::string>("proc"))),
    _em_current(0, 0, 0)
{
}

template <bool is_ad>
Real
ProcRateTempl<is_ad>::computeValue()
{
  _em_current = 6.02e23 * (_sgnem[_qp] * raw_value(_muem[_qp]) * raw_value(_electric_field[_qp]) *
                               _r_units * std::exp(_em[_qp]) -
                           raw_value(_diffem[_qp]) * std::exp(_em[_qp]) * _grad_em[_qp] * _r_units);

  return raw_value(_alpha[_qp]) * _em_current.norm();
}

template class ProcRateTempl<false>;
template class ProcRateTempl<true>;
