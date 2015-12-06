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

#include "DGMatDiffusionInt.h"

#include <cmath>

template<>
InputParameters validParams<DGMatDiffusionInt>()
{
  InputParameters params = validParams<DGInterface>();
  params.addParam<Real>("D",1.,"The diffusion coefficient.");
  params.addParam<Real>("D_neighbor",1.,"The neighboring diffusion coefficient.");
  return params;
}

DGMatDiffusionInt::DGMatDiffusionInt(const InputParameters & parameters) :
    DGInterface(parameters),
    _D(getMaterialProperty<Real>("diff" + _var.name())),
    _D_neighbor(getNeighborMaterialProperty<Real>("diff" + _neighbor_var.name()))
{
  if (!parameters.isParamValid("boundary"))
  {
    mooseError("In order to use the DGMatDiffusionInt dgkernel, you must specify a boundary where it will live.");
  }
}

Real
DGMatDiffusionInt::computeQpResidual(Moose::DGResidualType type)
{
  if (_D_neighbor[_qp] < std::numeric_limits<double>::epsilon())
    mooseError("It doesn't appear that DG material properties got passed.");

  Real r = 0;

  switch (type)
  {
  case Moose::Element:
    r += 0.5 * (-_D[_qp] * _grad_u[_qp] * _normals[_qp] + -_D_neighbor[_qp] * _grad_neighbor_value[_qp] * _normals[_qp]) * _test[_i][_qp];
    break;

  case Moose::Neighbor:
    r += 0.5 * (_D[_qp] * _grad_u[_qp] * _normals[_qp] + _D_neighbor[_qp] * _grad_neighbor_value[_qp] * _normals[_qp]) * _test_neighbor[_i][_qp];
    break;
  }

  return r;
}

Real
DGMatDiffusionInt::computeQpJacobian(Moose::DGJacobianType type)
{
  Real jac = 0;

  switch (type)
  {

  case Moose::ElementElement:
    jac -= 0.5 * _D[_qp] * _grad_phi[_j][_qp] * _normals[_qp] * _test[_i][_qp];
    break;

  case Moose::NeighborNeighbor:
    jac += 0.5 * _D_neighbor[_qp] * _grad_phi_neighbor[_j][_qp] * _normals[_qp] * _test_neighbor[_i][_qp];
    break;
  }

  return jac;
}

Real
DGMatDiffusionInt::computeQpOffDiagJacobian(Moose::DGJacobianType type, unsigned int jvar)
{

  if (jvar == _var.number())
    return  0.5 * (_D[_qp] * _grad_phi[_j][_qp] * _normals[_qp]) * _test_neighbor[_i][_qp];

  else if (jvar == _neighbor_var.number())
    return  0.5 * (-_D_neighbor[_qp] * _grad_phi_neighbor[_j][_qp] * _normals[_qp]) * _test[_i][_qp];

  else
    return 0.;

}
