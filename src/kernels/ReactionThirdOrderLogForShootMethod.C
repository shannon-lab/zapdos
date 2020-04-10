//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ReactionThirdOrderLogForShootMethod.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("ZapdosApp", ReactionThirdOrderLogForShootMethod);

template <>
InputParameters
validParams<ReactionThirdOrderLogForShootMethod>()
{
  InputParameters params = validParams<Kernel>();
  params.addCoupledVar("density", "The accelerated density variable.");
  params.addCoupledVar("v", "The Second variable that is reacting.");
  params.addCoupledVar("w", "The Third variable that is reacting.");
  params.addRequiredParam<std::string>("reaction", "The full reaction equation.");
  params.addRequiredParam<Real>("coefficient", "The stoichiometric coeffient.");
  params.addParam<std::string>(
      "number",
      "",
      "The reaction number. Optional, just for material property naming purposes. If a single "
      "reaction has multiple different rate coefficients (frequently the case when multiple "
      "species are lumped together to simplify a reaction network), this will prevent the same "
      "material property from being declared multiple times.");
  params.addClassDescription(
    "The derivative of an third order reaction term used to calculate the sensitivity variable for the shoothing method."
    "(Densities must be in log form)");
  return params;
}

ReactionThirdOrderLogForShootMethod::ReactionThirdOrderLogForShootMethod(const InputParameters & parameters)
  : Kernel(parameters),
    _reaction_coeff(getMaterialProperty<Real>("k" + getParam<std::string>("number") + "_" +
                                              getParam<std::string>("reaction"))),

    _density(coupledValue("density")),
    _density_id(coupled("density")),
    _v(coupledValue("v")),
    _v_id(coupled("v")),
    _w(coupledValue("w")),
    _w_id(coupled("v")),

    _stoichiometric_coeff(getParam<Real>("coefficient"))
{
}

Real
ReactionThirdOrderLogForShootMethod::computeQpResidual()
{
  Real power;

  power = 1.;
  if (_v_id == _density_id)
    power += 1.;

  if (_w_id == _density_id)
    power += 1.;

  return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * power *
         std::exp(_v[_qp]) * std::exp(_w[_qp]) * _u[_qp];
}

Real
ReactionThirdOrderLogForShootMethod::computeQpJacobian()
{
  Real power;

  power = 1.;
  if (_v_id == _density_id)
    power += 1.;

  if (_w_id == _density_id)
    power += 1.;

  return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * power *
         std::exp(_v[_qp]) * std::exp(_w[_qp]) * _phi[_j][_qp];
}

Real
ReactionThirdOrderLogForShootMethod::computeQpOffDiagJacobian(unsigned int jvar)
{
  if(_v_id == _w_id)
  {
    if (jvar == _v_id)
    {
      if (_v_id == _density_id)  //i.e. density == v == w
      {
        return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * 6.0 *
               _phi[_j][_qp] * std::exp(_v[_qp]) * std::exp(_w[_qp]) * _u[_qp];
      }
      else  //i.e. density != v == w
      {
        return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * 2.0 *
               _phi[_j][_qp] * std::exp(_v[_qp]) * std::exp(_w[_qp]) * _u[_qp];
      }
    }
    else
      return 0.0;
  }
  else
  {
    if (jvar == _v_id)
    {
      if (_v_id == _density_id)  //i.e. density == v != w
      {
        return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * 2.0 *
               _phi[_j][_qp] * std::exp(_v[_qp]) * std::exp(_w[_qp]) * _u[_qp];
      }
      else  //i.e. density != v != w
      {
        return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * 1.0 *
               _phi[_j][_qp] * std::exp(_v[_qp]) * std::exp(_w[_qp]) * _u[_qp];
      }
    }
    if (jvar == _w_id)
    {
      if (_w_id == _density_id)  //i.e. density == w != v
      {
        return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * 2.0 *
               _phi[_j][_qp] * std::exp(_v[_qp]) * std::exp(_w[_qp]) * _u[_qp];
      }
      else  //i.e. density != v != w
      {
        return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * 1.0 *
               _phi[_j][_qp] * std::exp(_v[_qp]) * std::exp(_w[_qp]) * _u[_qp];
      }
    }
    else
      return 0.0;
  }
}
