//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "EEDFReactionLogForShootMethod.h"

registerMooseObject("ZapdosApp", EEDFReactionLogForShootMethod);

InputParameters
EEDFReactionLogForShootMethod::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addRequiredCoupledVar("electron", "The electron species variable.");
  params.addRequiredCoupledVar("density", "The accelerated density variable.");
  params.addRequiredParam<std::string>("reaction", "The full reaction equation.");
  params.addRequiredParam<Real>("coefficient", "The stoichiometric coefficient.");
  params.addParam<std::string>(
      "number",
      "",
      "The reaction number. Optional, just for material property naming purposes. If a single "
      "reaction has multiple different rate coefficients (frequently the case when multiple "
      "species are lumped together to simplify a reaction network), this will prevent the same "
      "material property from being declared multiple times.");
  params.addClassDescription("The derivative of an EEDF reaction term used to calculate the "
                             "sensitivity variable for the shoothing method."
                             "(Densities must be in logarithmic form)");
  return params;
}

EEDFReactionLogForShootMethod::EEDFReactionLogForShootMethod(const InputParameters & parameters)
  : ADKernel(parameters),
    _electron(adCoupledValue("electron")),
    _density(adCoupledValue("density")),
    _reaction_coeff(getADMaterialProperty<Real>("k" + getParam<std::string>("number") + "_" +
                                                getParam<std::string>("reaction"))),
    _stoichiometric_coeff(getParam<Real>("coefficient"))
{
}

ADReal
EEDFReactionLogForShootMethod::computeQpResidual()
{
  return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] *
         _u[_qp] * std::exp(_electron[_qp]);
}
