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

#include "DGPenaltyTiedValue.h"

#include <cmath>

template<>
InputParameters validParams<DGPenaltyTiedValue>()
{
  InputParameters params = validParams<InterfaceKernel>();
  params.addParam<Real>("scale_factor",1.,"The amount by which to scale this penalty condition.");
  return params;
}

DGPenaltyTiedValue::DGPenaltyTiedValue(const InputParameters & parameters) :
    InterfaceKernel(parameters),
    _scale_factor(getParam<Real>("scale_factor"))
{
  if (!parameters.isParamValid("boundary"))
  {
    mooseError("In order to use the DGPenaltyTiedValue dgkernel, you must specify a boundary where it will live.");
  }
}

Real
DGPenaltyTiedValue::computeQpResidual(Moose::DGResidualType type)
{
  Real r = 0;

  switch (type)
  {
  case Moose::Element:
    r += 0.5 * (_u[_qp] - _neighbor_value[_qp]) * _scale_factor * _test[_i][_qp];
    break;

  case Moose::Neighbor:
    r += 0.5 * (_u[_qp] - _neighbor_value[_qp]) * _scale_factor * _test_neighbor[_i][_qp];
    break;
  }

  return r;
}

Real
DGPenaltyTiedValue::computeQpJacobian(Moose::DGJacobianType type)
{
  Real jac = 0;

  switch (type)
  {

  case Moose::ElementElement:
    jac +=  0.5 * (_phi[_j][_qp]) * _scale_factor * _test[_i][_qp];
    break;

  case Moose::NeighborNeighbor:
    jac += 0.5 * (- _phi_neighbor[_j][_qp]) * _scale_factor * _test_neighbor[_i][_qp];
    break;
  }

  return jac;
}

Real
DGPenaltyTiedValue::computeQpOffDiagJacobian(Moose::DGJacobianType type, unsigned int jvar)
{

  if (jvar == _var.number())
    return 0.5 * (_phi[_j][_qp]) * _scale_factor * _test_neighbor[_i][_qp];

  else if (jvar == _neighbor_var.number())
    return 0.5 * (- _phi_neighbor[_j][_qp]) * _scale_factor * _test[_i][_qp];

  else
    return 0.;

}
