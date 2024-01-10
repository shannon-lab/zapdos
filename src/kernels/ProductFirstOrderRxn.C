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

registerMooseObject("ZapdosApp", ProductFirstOrderRxn);

InputParameters
ProductFirstOrderRxn::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addRequiredCoupledVar("v", "The variable that is reacting to create u.");
  params.addClassDescription("Generic first order reaction source term for u (v is the reactant"
                             "and densities must be in logarithmic form)");
  return params;
}

ProductFirstOrderRxn::ProductFirstOrderRxn(const InputParameters & parameters)
  : ADKernel(parameters),

    _coupled_var(*getVar("v", 0)),
    _v(adCoupledValue("v")),
    _reaction_coeff(getADMaterialProperty<Real>("k" + _coupled_var.name()))
{
}

ADReal
ProductFirstOrderRxn::computeQpResidual()
{
  return -_test[_i][_qp] * (1.) * _reaction_coeff[_qp] * std::exp(_v[_qp]);
}
