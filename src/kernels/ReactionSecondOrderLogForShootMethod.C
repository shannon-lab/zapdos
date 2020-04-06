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

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("ZapdosApp", ReactionSecondOrderLogForShootMethod);

template <>
InputParameters
validParams<ReactionSecondOrderLogForShootMethod>()
{
  InputParameters params = validParams<Kernel>();
  params.addCoupledVar("density", "The accelerated density variable.");
  params.addCoupledVar("v", "The Second variable that is reacting.");
  params.addRequiredParam<std::string>("reaction", "The full reaction equation.");
  params.addRequiredParam<Real>("coefficient", "The stoichiometric coeffient.");
  params.addClassDescription(
    "The derivative of an second order reaction term used to calculate the sensitivity variable for the shoothing method."
    "(Densities must be in log form)");
  return params;
}

ReactionSecondOrderLogForShootMethod::ReactionSecondOrderLogForShootMethod(const InputParameters & parameters)
  : Kernel(parameters),
  _reaction_coeff(getMaterialProperty<Real>("k_" + getParam<std::string>("reaction"))),

  _density(coupledValue("density")),
  _density_id(coupled("density")),
  _v(coupledValue("v")),
  _v_id(coupled("v")),

  _stoichiometric_coeff(getParam<Real>("coefficient"))
{
}

Real
ReactionSecondOrderLogForShootMethod::computeQpResidual()
{
  if (_v_id == _density_id)
  {
    return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * 2.0 *
            std::exp(_v[_qp]) * _u[_qp];
  }
  else
  {
    return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * 1.0 *
            std::exp(_v[_qp]) * _u[_qp];
  }
}

Real
ReactionSecondOrderLogForShootMethod::computeQpJacobian()
{
  if (_v_id == _density_id)
  {
    return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * 2.0 *
            std::exp(_v[_qp]) * _phi[_j][_qp];
  }
  else
  {
    return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * 1.0 *
            std::exp(_v[_qp]) * _phi[_j][_qp];
  }
}

Real
ReactionSecondOrderLogForShootMethod::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _v_id)
  {
    if (_v_id == _density_id)
    {
      return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * 2.0 *
              std::exp(_v[_qp]) * _phi[_j][_qp] * _u[_qp];
    }
    else
    {
      return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * 1.0 *
              std::exp(_v[_qp]) * _phi[_j][_qp] * _u[_qp];
    }
  }
  else
    return 0.0;
}
