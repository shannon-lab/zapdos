//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ProcRateForRateCoeffThreeBody.h"

registerMooseObject("ZapdosApp", ProcRateForRateCoeffThreeBody);

InputParameters
ProcRateForRateCoeffThreeBody::validParams()
{
  InputParameters params = AuxKernel::validParams();

  params.addCoupledVar("v", "The first variable that is reacting to create u.");
  params.addCoupledVar("w", "The second variable that is reacting to create u.");
  params.addCoupledVar("vv", "The second variable that is reacting to create u.");
  params.addRequiredParam<std::string>("reaction", "The full reaction equation.");
  params.addClassDescription(
      "Reaction rate for three body collisions in units of #/m^3s. User can pass"
      "choice of elastic, excitation, or ionization reaction rate coefficients");

  return params;
}

ProcRateForRateCoeffThreeBody::ProcRateForRateCoeffThreeBody(const InputParameters & parameters)
  : AuxKernel(parameters),

    _v(coupledValue("v")),
    _w(coupledValue("w")),
    _vv(coupledValue("vv")),
    _reaction_coeff(getMaterialProperty<Real>("k_" + getParam<std::string>("reaction")))
{
}

Real
ProcRateForRateCoeffThreeBody::computeValue()
{

  return 6.02e23 * _reaction_coeff[_qp] * std::exp(_v[_qp]) * std::exp(_w[_qp]) *
         std::exp(_vv[_qp]);
}
