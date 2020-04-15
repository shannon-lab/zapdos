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

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("ZapdosApp", EEDFReactionLogForShootMethod);

template <>
InputParameters
validParams<EEDFReactionLogForShootMethod>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("electron", "The electron species variable.");
  params.addRequiredCoupledVar("density", "The accelerated density variable.");
  params.addRequiredCoupledVar("energy", "The energy variable.");
  params.addRequiredParam<std::string>("reaction", "The full reaction equation.");
  params.addRequiredParam<Real>("coefficient", "The stoichiometric coeffient.");
  params.addParam<std::string>(
      "number",
      "",
      "The reaction number. Optional, just for material property naming purposes. If a single "
      "reaction has multiple different rate coefficients (frequently the case when multiple "
      "species are lumped together to simplify a reaction network), this will prevent the same "
      "material property from being declared multiple times.");
  params.addClassDescription("The derivative of an EEDF reaction term used to calculate the "
                             "sensitivity variable for the shoothing method."
                             "(Densities must be in log form)");
  return params;
}

EEDFReactionLogForShootMethod::EEDFReactionLogForShootMethod(const InputParameters & parameters)
  : Kernel(parameters),
    _electron(coupledValue("electron")),
    _density(coupledValue("density")),
    _energy(coupledValue("energy")),
    _electron_id(coupled("electron")),
    _density_id(coupled("density")),
    _energy_id(coupled("energy")),
    _reaction_coeff(getMaterialProperty<Real>("k" + getParam<std::string>("number") + "_" +
                                              getParam<std::string>("reaction"))),
    _d_k_d_en(getMaterialProperty<Real>("d_k" + getParam<std::string>("number") + "_d_en_" +
                                        getParam<std::string>("reaction"))),
    _stoichiometric_coeff(getParam<Real>("coefficient"))
{
}

Real
EEDFReactionLogForShootMethod::computeQpResidual()
{
  return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * 1.0 *
         std::exp(_electron[_qp]) * _u[_qp];
}

Real
EEDFReactionLogForShootMethod::computeQpJacobian()
{
  return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * 1.0 *
         std::exp(_electron[_qp]) * _phi[_j][_qp];
}

Real
EEDFReactionLogForShootMethod::computeQpOffDiagJacobian(unsigned int jvar)
{
  Real actual_mean_en, d_ame_d_electron, d_ame_d_energy;

  if (jvar == _electron_id)
  {
    actual_mean_en = std::exp(_energy[_qp] - _electron[_qp]);
    d_ame_d_electron = -actual_mean_en;

    return -_test[_i][_qp] * _stoichiometric_coeff *
           (_reaction_coeff[_qp] + (_d_k_d_en[_qp] * d_ame_d_electron)) * _phi[_j][_qp] *
           std::exp(_electron[_qp]) * _u[_qp];
  }
  if (jvar == _energy_id)
  {
    actual_mean_en = std::exp(_energy[_qp] - _electron[_qp]);
    d_ame_d_energy = actual_mean_en;

    return -_test[_i][_qp] * _stoichiometric_coeff * (_d_k_d_en[_qp] * d_ame_d_energy) *
           _phi[_j][_qp] * std::exp(_electron[_qp]) * _u[_qp];
  }
  else
    return 0.0;
}
