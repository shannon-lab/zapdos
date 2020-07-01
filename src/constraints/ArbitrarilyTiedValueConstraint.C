//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ArbitrarilyTiedValueConstraint.h"

// MOOSE includes
#include "MooseVariable.h"
#include "SystemBase.h"

// libmesh includes
#include "libmesh/sparse_matrix.h"

registerMooseObject("ZapdosApp", ArbitrarilyTiedValueConstraint);

template <>
InputParameters
validParams<ArbitrarilyTiedValueConstraint>()
{
  InputParameters params = validParams<NodeFaceConstraint>();
  params.addParam<Real>("scaling", 1, "scaling factor to be applied to constraint equations");
  params.addRequiredParam<Real>("H", "The value of u_secondary/u_primary.");
  params.set<bool>("use_displaced_mesh") = true;
  return params;
}

ArbitrarilyTiedValueConstraint::ArbitrarilyTiedValueConstraint(const InputParameters & parameters)
  : NodeFaceConstraint(parameters),
    _scaling(getParam<Real>("scaling")),
    _H(getParam<Real>("H")),
    _residual_copy(_sys.residualGhosted())
{
}

Real
ArbitrarilyTiedValueConstraint::computeQpSecondaryValue()
{
  return _H * _u_primary[_qp];
}

Real
ArbitrarilyTiedValueConstraint::computeQpResidual(Moose::ConstraintType type)
{
  Real scaling_factor = _var.scalingFactor();
  Real secondary_resid = 0;
  Real retVal = 0;
  switch (type)
  {
    case Moose::Secondary:
      retVal = (_u_secondary[_qp] - _H * _u_primary[_qp]) * _test_secondary[_i][_qp] * _scaling;
      break;
    case Moose::Primary:
      secondary_resid =
          _residual_copy(_current_node->dof_number(0, _var.number(), 0)) / scaling_factor;
      retVal = secondary_resid * _test_primary[_i][_qp];
      break;
    default:
      break;
  }
  return retVal;
}

Real
ArbitrarilyTiedValueConstraint::computeQpJacobian(Moose::ConstraintJacobianType type)
{
  Real scaling_factor = _var.scalingFactor();
  Real secondary_jac = 0;
  Real retVal = 0;
  switch (type)
  {
    case Moose::SecondarySecondary:
      retVal = _phi_secondary[_j][_qp] * _test_secondary[_i][_qp] * _scaling;
      break;
    case Moose::SecondaryPrimary:
      retVal = -_H * _phi_primary[_j][_qp] * _test_secondary[_i][_qp] * _scaling;
      break;
    case Moose::PrimarySecondary:
      secondary_jac =
          (*_jacobian)(_current_node->dof_number(0, _var.number(), 0), _connected_dof_indices[_j]);
      retVal = secondary_jac * _test_primary[_i][_qp] / scaling_factor;
      break;
    case Moose::PrimaryPrimary:
      retVal = 0;
      break;

    default:
      return 0;
  }
  return retVal;
}
