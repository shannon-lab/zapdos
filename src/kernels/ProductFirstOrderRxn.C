//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ProductFirstOrderRxn.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("ZapdosApp", ProductFirstOrderRxn);

template <>
InputParameters
validParams<ProductFirstOrderRxn>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("v", "The variable that is reacting to create u.");
  return params;
}

ProductFirstOrderRxn::ProductFirstOrderRxn(const InputParameters & parameters)
  : Kernel(parameters),

    _coupled_var(*getVar("v", 0)),
    _v(coupledValue("v")),
    _v_id(coupled("v")),
    _reaction_coeff(getMaterialProperty<Real>("k" + _coupled_var.name()))
{
}

Real
ProductFirstOrderRxn::computeQpResidual()
{
  return -_test[_i][_qp] * (1.) * _reaction_coeff[_qp] * std::exp(_v[_qp]);
}

Real
ProductFirstOrderRxn::computeQpJacobian()
{
  return 0.0;
}

Real
ProductFirstOrderRxn::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _v_id)
    return -_test[_i][_qp] * (1.) * _reaction_coeff[_qp] * std::exp(_v[_qp]) * _phi[_j][_qp];

  else
    return 0.0;
}
