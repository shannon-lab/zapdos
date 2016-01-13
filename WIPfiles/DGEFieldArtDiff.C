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

#include "DGEFieldArtDiff.h"

#include <cmath>

template<>
InputParameters validParams<DGEFieldArtDiff>()
{
  InputParameters params = validParams<InterfaceKernel>();
  params.addRequiredCoupledVar("potential","The potential on the master side of the interface.");
  params.addRequiredCoupledVar("potential_neighbor", "The potential on the slave side of the interface.");
  return params;
}

DGEFieldArtDiff::DGEFieldArtDiff(const InputParameters & parameters) :
    InterfaceKernel(parameters),
    _potential_var(*getVar("potential",0)),
    _potential_neighbor_var(*getVar("potential_neighbor",0)),
    _grad_potential(_potential_var.gradSln()),
    _grad_potential_neighbor(_potential_neighbor_var.gradSlnNeighbor()),

    _mu(getMaterialProperty<Real>("mu" + _var.name())),
    _mu_neighbor(getNeighborMaterialProperty<Real>("mu" + _neighbor_var.name())),
{
  if (!parameters.isParamValid("boundary"))
  {
    mooseError("In order to use the DGEFieldArtDiff dgkernel, you must specify a boundary where it will live.");
  }
}

Real
DGEFieldArtDiff::computeQpResidual(Moose::DGResidualType type)
{
  if (_mu_neighbor[_qp] < std::numeric_limits<double>::epsilon() < std::numeric_limits<double>::epsilon())
    mooseError("It doesn't appear that DG material properties got passed.");

  Real  vd_mag = _mu[_qp]*_grad_potential[_qp].size();
  Real  delta = vd_mag*_current_elem->hmax()/2.0;
  Real vd_mag_neighbor = _mu_neighbor[_qp] * _grad_potential_neighbor[_qp].size();
  Real delta_neighbor = vd_mag_neighbor*_current_el
  Real r = 0;

  switch (type)
  {
  case Moose::Element:
    r += 0.5 * (_mu[_qp] * _sgn[_qp] * -_grad_potential[_qp] * std::exp(_u[_qp]) * _normals[_qp] + _mu_neighbor[_qp] * _sgn_neighbor[_qp] * -_grad_potential_neighbor[_qp] * std::exp(_neighbor_value[_qp]) * _normals[_qp]) * _test[_i][_qp];
    break;

  case Moose::Neighbor:
    r += -0.5 * (_mu[_qp] * _sgn[_qp] * -_grad_potential[_qp] * std::exp(_u[_qp]) * _normals[_qp] + _mu_neighbor[_qp] * _sgn_neighbor[_qp] * -_grad_potential_neighbor[_qp] * std::exp(_neighbor_value[_qp]) * _normals[_qp]) * _test_neighbor[_i][_qp];
    break;
  }

  return r;
}

Real
DGEFieldArtDiff::computeQpJacobian(Moose::DGJacobianType type)
{
  Real jac = 0;

  switch (type)
  {

  case Moose::ElementElement:
    jac += 0.5 * (_mu[_qp] * _sgn[_qp] * -_grad_potential[_qp] * std::exp(_u[_qp]) * _phi[_j][_qp] * _normals[_qp]) * _test[_i][_qp];
    break;

  case Moose::ElementNeighbor:
    jac += 0.5 * (_mu_neighbor[_qp] * _sgn_neighbor[_qp] * -_grad_potential_neighbor[_qp] * std::exp(_neighbor_value[_qp]) * _phi_neighbor[_j][_qp] * _normals[_qp]) * _test[_i][_qp];
    break;

  case Moose::NeighborElement:
    jac += -0.5 * (_mu[_qp] * _sgn[_qp] * -_grad_potential[_qp] * std::exp(_u[_qp]) * _phi[_j][_qp] * _normals[_qp]) * _test_neighbor[_i][_qp];
    break;

  case Moose::NeighborNeighbor:
    jac += -0.5 * (_mu_neighbor[_qp] * _sgn_neighbor[_qp] * -_grad_potential_neighbor[_qp] * std::exp(_neighbor_value[_qp]) * _phi_neighbor[_j][_qp] * _normals[_qp]) * _test_neighbor[_i][_qp];
    break;
  }

  return jac;
}
