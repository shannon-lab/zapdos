//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ProcRateForRateCoeff.h"

using MetaPhysicL::raw_value;

registerMooseObject("ZapdosApp", ProcRateForRateCoeff);
registerMooseObject("ZapdosApp", ADProcRateForRateCoeff);

template <bool is_ad>
InputParameters
ProcRateForRateCoeffTempl<is_ad>::validParams()
{
  InputParameters params = AuxKernel::validParams();

  params.addCoupledVar("v", "The first variable that is reacting to create u.");
  params.addCoupledVar("w", "The second variable that is reacting to create u.");
  params.addRequiredParam<std::string>("reaction", "The full reaction equation.");
  params.addClassDescription(
      "Reaction rate for two body collisions in units of #/m$^{3}$s. User can pass "
      "choice of elastic, excitation, or ionization reaction rate coefficients");

  return params;
}

template <bool is_ad>
ProcRateForRateCoeffTempl<is_ad>::ProcRateForRateCoeffTempl(const InputParameters & parameters)
  : AuxKernel(parameters),

    _v(coupledValue("v")),
    _w(coupledValue("w")),
    _reaction_coeff(
        getGenericMaterialProperty<Real, is_ad>("k_" + getParam<std::string>("reaction")))
{
}

template <bool is_ad>
Real
ProcRateForRateCoeffTempl<is_ad>::computeValue()
{

  return 6.02e23 * raw_value(_reaction_coeff[_qp]) * std::exp(_v[_qp]) * std::exp(_w[_qp]);
}

template class ProcRateForRateCoeffTempl<false>;
template class ProcRateForRateCoeffTempl<true>;
