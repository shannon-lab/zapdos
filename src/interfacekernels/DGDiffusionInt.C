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

#include "DGDiffusionInt.h"

#include <cmath>

template<>
InputParameters validParams<DGDiffusionInt>()
{
  InputParameters params = validParams<InterfaceKernel>();
  return params;
}

DGDiffusionInt::DGDiffusionInt(const InputParameters & parameters) :
    InterfaceKernel(parameters)
{
  if (!parameters.isParamValid("boundary"))
  {
    mooseError("In order to use the DGDiffusionInt dgkernel, you must specify a boundary where it will live.");
  }
}

Real
DGDiffusionInt::computeQpResidual(Moose::DGResidualType type)
{
  Real r = 0;

  switch (type)
  {
  case Moose::Element:
    r += 0.5 * (-_grad_u[_qp] * _normals[_qp] + -_grad_neighbor_value[_qp] * _normals[_qp]) * _test[_i][_qp];
    break;

  case Moose::Neighbor:
    r += 0.5 * (_grad_u[_qp] * _normals[_qp] + _grad_neighbor_value[_qp] * _normals[_qp]) * _test_neighbor[_i][_qp];
    break;
  }

  return r;
}

Real
DGDiffusionInt::computeQpJacobian(Moose::DGJacobianType type)
{
  Real jac = 0;

  switch (type)
  {

  case Moose::ElementElement:
    jac -= 0.5 * _grad_phi[_j][_qp] * _normals[_qp] * _test[_i][_qp];
    break;

  case Moose::ElementNeighbor:
    jac -= 0.5 * _grad_phi_neighbor[_j][_qp] * _normals[_qp] * _test[_i][_qp];
    break;

  case Moose::NeighborElement:
    jac += 0.5 * _grad_phi[_j][_qp] * _normals[_qp] * _test_neighbor[_i][_qp];
    break;

  case Moose::NeighborNeighbor:
    jac += 0.5 * _grad_phi_neighbor[_j][_qp] * _normals[_qp] * _test_neighbor[_i][_qp];
    break;
  }

  return jac;
}
