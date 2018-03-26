#include "DGEFieldAdvection.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("ZapdosApp", DGEFieldAdvection);

template <>
InputParameters
validParams<DGEFieldAdvection>()
{
  InputParameters params = validParams<DGKernel>();
  params.addRequiredCoupledVar("potential", "The potential that drives advection.");
  return params;
}

DGEFieldAdvection::DGEFieldAdvection(const InputParameters & parameters)
  : DGKernel(parameters),

    _mu(getMaterialProperty<Real>("mu" + _var.name())),
    _sgn(getMaterialProperty<Real>("sgn" + _var.name())),
    _mu_neighbor(getNeighborMaterialProperty<Real>("mu" + _var.name())),
    _sgn_neighbor(getNeighborMaterialProperty<Real>("sgn" + _var.name())),

    _potential_var(*getVar("potential", 0)),
    _potential_id(coupled("potential")),
    _grad_potential(coupledGradient("potential")),
    _grad_potential_neighbor(_potential_var.gradSlnNeighbor()),
    _grad_phi_pot(_potential_var.gradPhiFace()),
    _grad_phi_neighbor_pot(_potential_var.gradPhiFaceNeighbor())
{
}

Real
DGEFieldAdvection::computeQpResidual(Moose::DGResidualType type)
{
  Real r = 0;
  RealVectorValue _velocity = _mu[_qp] * _sgn[_qp] * -_grad_potential[_qp];
  RealVectorValue _velocity_neighbor =
      _mu_neighbor[_qp] * _sgn_neighbor[_qp] * -_grad_potential_neighbor[_qp];
  RealVectorValue _velocity_average = 0.5 * (_velocity + _velocity_neighbor);

  switch (type)
  {
    case Moose::Element:
      if ((_velocity_average * _normals[_qp]) >= 0.0)
        r += (_velocity_average * _normals[_qp]) * std::exp(_u[_qp]) * _test[_i][_qp];
      else
        r += (_velocity_average * _normals[_qp]) * std::exp(_u_neighbor[_qp]) * _test[_i][_qp];
      break;

    case Moose::Neighbor:
      if ((_velocity_average * _normals[_qp]) >= 0.0)
        r += -(_velocity_average * _normals[_qp]) * std::exp(_u[_qp]) * _test_neighbor[_i][_qp];
      else
        r += -(_velocity_average * _normals[_qp]) * std::exp(_u_neighbor[_qp]) *
             _test_neighbor[_i][_qp];
      break;
  }
  return r;
}

Real
DGEFieldAdvection::computeQpJacobian(Moose::DGJacobianType type)
{
  Real jac = 0;
  RealVectorValue _velocity = _mu[_qp] * _sgn[_qp] * -_grad_potential[_qp];
  RealVectorValue _velocity_neighbor =
      _mu_neighbor[_qp] * _sgn_neighbor[_qp] * -_grad_potential_neighbor[_qp];
  RealVectorValue _velocity_average = 0.5 * (_velocity + _velocity_neighbor);

  switch (type)
  {

    case Moose::ElementElement:
      if ((_velocity_average * _normals[_qp]) >= 0.0)
        jac += (_velocity_average * _normals[_qp]) * std::exp(_u[_qp]) * _phi[_j][_qp] *
               _test[_i][_qp];
      else
        jac += 0.0;
      break;

    case Moose::ElementNeighbor:
      if ((_velocity_average * _normals[_qp]) >= 0.0)
        jac += 0.0;
      else
        jac += (_velocity_average * _normals[_qp]) * std::exp(_u_neighbor[_qp]) *
               _phi_neighbor[_j][_qp] * _test[_i][_qp];
      break;

    case Moose::NeighborElement:
      if ((_velocity_average * _normals[_qp]) >= 0.0)
        jac += -(_velocity_average * _normals[_qp]) * std::exp(_u[_qp]) * _phi[_j][_qp] *
               _test_neighbor[_i][_qp];
      else
        jac += 0.0;
      break;

    case Moose::NeighborNeighbor:
      if ((_velocity_average * _normals[_qp]) >= 0.0)
        jac += 0.0;
      else
        jac += -(_velocity_average * _normals[_qp]) * std::exp(_u_neighbor[_qp]) *
               _phi_neighbor[_j][_qp] * _test_neighbor[_i][_qp];
      break;
  }
  return jac;
}

Real
DGEFieldAdvection::computeQpOffDiagJacobian(Moose::DGJacobianType type, unsigned int jvar)
{
  Real jac = 0;

  if (jvar == _potential_id)
  {
    RealVectorValue _velocity = _mu[_qp] * _sgn[_qp] * -_grad_potential[_qp];
    RealVectorValue _velocity_neighbor =
        _mu_neighbor[_qp] * _sgn_neighbor[_qp] * -_grad_potential_neighbor[_qp];
    RealVectorValue _velocity_average = 0.5 * (_velocity + _velocity_neighbor);
    RealVectorValue _d_velocity_avg_elem = 0.5 * _mu[_qp] * _sgn[_qp] * -_grad_phi[_j][_qp];
    RealVectorValue _d_velocity_avg_neigh =
        0.5 * _mu_neighbor[_qp] * _sgn_neighbor[_qp] * -_grad_phi_neighbor[_j][_qp];

    switch (type)
    {

      case Moose::ElementElement:
        if ((_velocity_average * _normals[_qp]) >= 0.0)
          jac += (_d_velocity_avg_elem * _normals[_qp]) * std::exp(_u[_qp]) * _test[_i][_qp];
        else
          jac +=
              (_d_velocity_avg_elem * _normals[_qp]) * std::exp(_u_neighbor[_qp]) * _test[_i][_qp];
        break;

      case Moose::ElementNeighbor:
        if ((_velocity_average * _normals[_qp]) >= 0.0)
          jac += (_d_velocity_avg_neigh * _normals[_qp]) * std::exp(_u[_qp]) * _test[_i][_qp];
        else
          jac +=
              (_d_velocity_avg_neigh * _normals[_qp]) * std::exp(_u_neighbor[_qp]) * _test[_i][_qp];
        break;

      case Moose::NeighborElement:
        if ((_velocity_average * _normals[_qp]) >= 0.0)
          jac +=
              -(_d_velocity_avg_elem * _normals[_qp]) * std::exp(_u[_qp]) * _test_neighbor[_i][_qp];
        else
          jac += -(_d_velocity_avg_elem * _normals[_qp]) * std::exp(_u_neighbor[_qp]) *
                 _test_neighbor[_i][_qp];
        break;

      case Moose::NeighborNeighbor:
        if ((_velocity_average * _normals[_qp]) >= 0.0)
          jac += -(_d_velocity_avg_neigh * _normals[_qp]) * std::exp(_u[_qp]) *
                 _test_neighbor[_i][_qp];
        else
          jac += -(_d_velocity_avg_neigh * _normals[_qp]) * std::exp(_u_neighbor[_qp]) *
                 _test_neighbor[_i][_qp];
        break;
    }
  }
  return jac;
}
