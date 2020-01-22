//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ReactantFirstOrderRxn.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("ZapdosApp", ReactantFirstOrderRxn);

template <>
InputParameters
validParams<ReactantFirstOrderRxn>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Generic first order reaction sink term for u (u is the reactant)"
                             "(Densities must be in log form)");
  return params;
}

ReactantFirstOrderRxn::ReactantFirstOrderRxn(const InputParameters & parameters)
  : Kernel(parameters),

    _reaction_coeff(getMaterialProperty<Real>("k" + _var.name()))
{
}

Real
ReactantFirstOrderRxn::computeQpResidual()
{
  return -_test[_i][_qp] * (-1.) * _reaction_coeff[_qp] * std::exp(_u[_qp]);
}

Real
ReactantFirstOrderRxn::computeQpJacobian()
{
  return -_test[_i][_qp] * (-1.) * _reaction_coeff[_qp] * std::exp(_u[_qp]) * _phi[_j][_qp];
}
