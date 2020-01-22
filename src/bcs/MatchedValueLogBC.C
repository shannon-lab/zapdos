//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "MatchedValueLogBC.h"

template <>
InputParameters
validParams<MatchedValueLogBC>()
{
  InputParameters params = validParams<NodalBC>();
  params.addRequiredParam<Real>("H", "The ratio of liquid phase density to gas phase density");
  params.addRequiredCoupledVar("v", "The variable whose value we are to match.");
  params.addClassDescription(
      "Henry’s Law like thermodynamic boundary condition for specifying a specie"
      "concentration ratio at the gas-liquid interface");
  return params;
}

MatchedValueLogBC::MatchedValueLogBC(const InputParameters & parameters)
  : NodalBC(parameters), _v(coupledValue("v")), _v_num(coupled("v")), _H(getParam<Real>("H"))
{
}

Real
MatchedValueLogBC::computeQpResidual()
{
  return _H * std::exp(_u[_qp]) - std::exp(_v[_qp]);
}

Real
MatchedValueLogBC::computeQpJacobian()
{
  return _H * std::exp(_u[_qp]);
}

Real
MatchedValueLogBC::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _v_num)
    return -std::exp(_v[_qp]);
  else
    return 0.;
}
