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

#include "DGAdvectionInterface.h"

#include <cmath>

template<>
InputParameters validParams<DGAdvectionInterface>()
{
  InputParameters params = validParams<InterfaceKernel>();
  params.addRequiredCoupledVar("potential","The potential on the master side of the interface.");
  params.addRequiredCoupledVar("potential_neighbor", "The potential on the slave side of the interface.");
  return params;
}

DGAdvectionInterface::DGAdvectionInterface(const InputParameters & parameters) :
    InterfaceKernel(parameters),
    _potential_var(*getVar("potential",0)),
    _potential_neighbor_var(*getVar("potential_neighbor",0)),
    _grad_potential(_potential_var.gradSln()),
    _grad_potential_neighbor(_potential_neighbor_var.gradSlnNeighbor()),
    _potential_id(coupled("potential")),
    _potential_neighbor_id(coupled("potential_neighbor")),

    _mu(getMaterialProperty<Real>("mu" + _var.name())),
    _mu_neighbor(getNeighborMaterialProperty<Real>("mu" + _neighbor_var.name())),
    _sgn(getMaterialProperty<Real>("sgn" + _var.name())),
    _sgn_neighbor(getNeighborMaterialProperty<Real>("sgn" + _neighbor_var.name()))
{
  if (!parameters.isParamValid("boundary"))
  {
    mooseError("In order to use the DGAdvectionInterface dgkernel, you must specify a boundary where it will live.");
  }
}

Real
DGAdvectionInterface::computeQpResidual(Moose::DGResidualType type)
{
  if (_mu_neighbor[_qp] < std::numeric_limits<double>::epsilon() || std::abs(_sgn_neighbor[_qp]) < std::numeric_limits<double>::epsilon())
    mooseError("It doesn't appear that DG material properties got passed.");

  Real r = 0;

  switch (type)
  {
  case Moose::Element:
    if ( (_sgn[_qp] * -_grad_potential[_qp] * _normals[_qp]) >= 0.0)
      r += _mu[_qp] * _sgn[_qp] * -_grad_potential[_qp] * std::exp(_u[_qp]) * _normals[_qp] * _test[_i][_qp];
    else
      r += _mu_neighbor[_qp] * _sgn_neighbor[_qp] * -_grad_potential_neighbor[_qp] * std::exp(_u_neighbor[_qp]) * _normals[_qp] * _test[_i][_qp];
    break;

  case Moose::Neighbor:
    if ( (_sgn[_qp] * -_grad_potential[_qp] * _normals[_qp]) >= 0.0)
      r += -_mu[_qp] * _sgn[_qp] * -_grad_potential[_qp] * std::exp(_u[_qp]) * _normals[_qp] * _test_neighbor[_i][_qp];
    else
      r += -_mu_neighbor[_qp] * _sgn_neighbor[_qp] * -_grad_potential_neighbor[_qp] * std::exp(_u_neighbor[_qp]) * _normals[_qp] * _test_neighbor[_i][_qp];
    break;
  }

  return r;
}

Real
DGAdvectionInterface::computeQpJacobian(Moose::DGJacobianType type)
{
  Real r = 0;

  switch (type)
  {
  case Moose::ElementElement:
    if ( (_sgn[_qp] * -_grad_potential[_qp] * _normals[_qp]) >= 0.0)
      r += _mu[_qp] * _sgn[_qp] * -_grad_potential[_qp] * std::exp(_u[_qp]) * _phi[_j][_qp] * _normals[_qp] * _test[_i][_qp];
    else
      r += 0.;
    break;

  case Moose::NeighborNeighbor:
    if ( (_sgn[_qp] * -_grad_potential[_qp] * _normals[_qp]) >= 0.0)
      r += 0.;
    else
      r += -_mu_neighbor[_qp] * _sgn_neighbor[_qp] * -_grad_potential_neighbor[_qp] * std::exp(_u_neighbor[_qp]) * _phi_neighbor[_j][_qp] * _normals[_qp] * _test_neighbor[_i][_qp];
    break;
  }

  return r;
}

Real
DGAdvectionInterface::computeQpOffDiagJacobian(Moose::DGJacobianType type, unsigned int jvar)
{
  Real r = 0;

  if (jvar == _var.number() && type == Moose::NeighborElement)
  {
    if ( (_sgn[_qp] * -_grad_potential[_qp] * _normals[_qp]) >= 0.0)
      r += -_mu[_qp] * _sgn[_qp] * -_grad_potential[_qp] * std::exp(_u[_qp]) * _phi[_j][_qp] * _normals[_qp] * _test_neighbor[_i][_qp];
    else
      r += 0.;
  }

  else if (jvar == _neighbor_var.number() && type == Moose::ElementNeighbor)
  {
    if ( (_sgn[_qp] * -_grad_potential[_qp] * _normals[_qp]) >= 0.0)
      r += 0.;
    else
      r += _mu_neighbor[_qp] * _sgn_neighbor[_qp] * -_grad_potential_neighbor[_qp] * std::exp(_u_neighbor[_qp]) * _phi_neighbor[_j][_qp] * _normals[_qp] * _test[_i][_qp];
  }

  else if (jvar == _potential_id)
  {
    switch (type)
    {

      case Moose::ElementElement:
        if ( (_sgn[_qp] * -_grad_potential[_qp] * _normals[_qp]) >= 0.0)
          r +=  _mu[_qp] * _sgn[_qp] * -_grad_phi[_j][_qp] * std::exp(_u[_qp]) * _normals[_qp] * _test[_i][_qp];
        else
          r += 0.0;
        break;

      case Moose::ElementNeighbor:
        r += 0.;

      case Moose::NeighborElement:
        if ( (_sgn[_qp] * -_grad_potential[_qp] * _normals[_qp]) >= 0.0)
          r += -_mu[_qp] * _sgn[_qp] * -_grad_phi[_j][_qp] * std::exp(_u[_qp]) * _normals[_qp] * _test_neighbor[_i][_qp];
        else
          r += 0.;

      case Moose::NeighborNeighbor:
        r += 0.;

    }
  }

  else if (jvar == _potential_neighbor_id)
  {
    switch (type)
    {

      case Moose::ElementElement:
        r += 0.;

      case Moose::ElementNeighbor:
        if ( (_sgn[_qp] * -_grad_potential[_qp] * _normals[_qp]) >= 0.0)
          r += 0.;
        else
          r +=  (_mu_neighbor[_qp] * _sgn_neighbor[_qp] * -_grad_phi_neighbor[_j][_qp] * std::exp(_neighbor_value[_qp]) * _normals[_qp]) * _test[_i][_qp];

      case Moose::NeighborElement:
        r += 0.;

      case Moose::NeighborNeighbor:
        if ( (_sgn[_qp] * -_grad_potential[_qp] * _normals[_qp]) >= 0.0)
          r += 0.;
        else
          r +=  -(_mu_neighbor[_qp] * _sgn_neighbor[_qp] * -_grad_phi_neighbor[_j][_qp] * std::exp(_neighbor_value[_qp]) * _normals[_qp]) * _test_neighbor[_i][_qp];

    }
  }

  return r;
}
