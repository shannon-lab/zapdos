//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "LinearCombinationAuxKernel.h"

registerMooseObject("ZapdosApp", LinearCombinationAuxKernel);

InputParameters
LinearCombinationAuxKernel::validParams()
{
  InputParameters params = AuxKernel::validParams();

  params.addRequiredCoupledVar("coupled_variables",
                               "The variables you would like to create a sum of");
  params.addRequiredParam<std::vector<Real>>("weights", "The weight of each coupled variable");
  params.addParam<Real>("bias", 0, "The bias for the linear combination");
  params.addClassDescription(
      "Linearly combine coupled variables with user provided weights and a bias");
  return params;
}

LinearCombinationAuxKernel::LinearCombinationAuxKernel(const InputParameters & parameters)
  : AuxKernel(parameters),
    _weights(getParam<std::vector<Real>>("weights")),
    _num_vars(coupledComponents("coupled_variables")),
    _bias(getParam<Real>("bias"))
{
  _vars.resize(_num_vars);
  _var_vals.resize(_num_vars);

  for (unsigned int i = 0; i < _num_vars; ++i)
  {
    _vars[i] = getVar("coupled_variables", i);
    _var_vals[i] = &coupledValue("coupled_variables", i);
  }
}

Real
LinearCombinationAuxKernel::computeValue()
{
  Real sum = 0;
  for (unsigned int i = 0; i < _num_vars; ++i)
  {
    sum += _weights[i] * (*_var_vals[i])[_qp];
  }

  return (sum + _bias);
}
