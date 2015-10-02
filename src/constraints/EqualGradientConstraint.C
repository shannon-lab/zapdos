/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "EqualGradientConstraint.h"
#include "SubProblem.h"
#include "FEProblem.h"

template<>
InputParameters validParams<EqualGradientConstraint>()
{
  InputParameters params = validParams<FaceFaceConstraint>();
  return params;
}

EqualGradientConstraint::EqualGradientConstraint(const InputParameters & parameters) :
    FaceFaceConstraint(parameters)
{
}

EqualGradientConstraint::~EqualGradientConstraint()
{
}

Real
EqualGradientConstraint::computeQpResidual()
{
  // return (_grad_u_master[_qp]*_normals_master[_qp]- _grad_u_slave[_qp]*_normals_slave[_qp])*_test[_i][_qp];
  return 0.0;
}

Real
EqualGradientConstraint::computeQpResidualSide(Moose::ConstraintType res_type)
{
  switch (res_type)
  {
  case Moose::Master: return  _lambda[_qp] * _test_master[_i][_qp];
  case Moose::Slave:  return -_lambda[_qp] * _test_slave[_i][_qp];
  default: return 0;
  }
}

Real
EqualGradientConstraint::computeQpJacobianSide(Moose::ConstraintJacobianType jac_type)
{
  switch (jac_type)
  {
  case Moose::MasterMaster:
  case Moose::SlaveMaster:
    return  _phi[_j][_qp] * _test_master[_i][_qp];

  case Moose::MasterSlave:
  case Moose::SlaveSlave:
    return -_phi[_j][_qp] * _test_slave[_i][_qp];

  default:
    return 0;
  }
}

