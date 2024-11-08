//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ReactionSecondOrderLogForShootMethod.h"

registerMooseObject("ZapdosApp", ReactionSecondOrderLogForShootMethod);

InputParameters
ReactionSecondOrderLogForShootMethod::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addCoupledVar("density", "The accelerated density variable.");
  params.addCoupledVar("v", "The Second variable that is reacting.");
  params.addRequiredParam<std::string>("reaction", "The full reaction equation.");
  params.addRequiredParam<Real>("coefficient", "The stoichiometric coeffient.");
  params.addParam<std::string>(
      "number",
      "",
      "The reaction number. Optional, just for material property naming purposes. If a single "
      "reaction has multiple different rate coefficients (frequently the case when multiple "
      "species are lumped together to simplify a reaction network), this will prevent the same "
      "material property from being declared multiple times.");
  params.addClassDescription("The derivative of a second order reaction term used to calculate "
                             "the sensitivity variable for the shoothing method. "
                             "(Densities must be in logarithmic form)");
  return params;
}

ReactionSecondOrderLogForShootMethod::ReactionSecondOrderLogForShootMethod(
    const InputParameters & parameters)
  : ADKernel(parameters),
    _reaction_coeff(getADMaterialProperty<Real>("k" + getParam<std::string>("number") + "_" +
                                                getParam<std::string>("reaction"))),

    _density(adCoupledValue("density")),
    _density_id(coupled("density")),
    _v(adCoupledValue("v")),
    _v_id(coupled("v")),

    _stoichiometric_coeff(getParam<Real>("coefficient"))
{
}

ADReal
ReactionSecondOrderLogForShootMethod::computeQpResidual()
{
  Real power;

  power = 1.;
  if (_v_id == _density_id)
    power += 1.;

  return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * power *
         std::exp(_v[_qp]) * _u[_qp];
}
