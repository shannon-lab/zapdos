#include "DGCoeffDiffusion.h"

// MOOSE includes
#include "MooseVariable.h"

#include <cmath>

registerMooseObject("ZapdosApp", DGCoeffDiffusion);

template <>
InputParameters
validParams<DGCoeffDiffusion>()
{
  InputParameters params = validParams<DGKernel>();
  // See header file for sigma and epsilon
  params.addRequiredParam<Real>("sigma", "sigma");
  params.addRequiredParam<Real>("epsilon", "epsilon");
  return params;
}

DGCoeffDiffusion::DGCoeffDiffusion(const InputParameters & parameters)
  : DGKernel(parameters),
    _epsilon(getParam<Real>("epsilon")),
    _sigma(getParam<Real>("sigma")),
    _diff(getMaterialProperty<Real>("diff" + _var.name())),
    _diff_neighbor(getNeighborMaterialProperty<Real>("diff" + _var.name()))
{
}

Real
DGCoeffDiffusion::computeQpResidual(Moose::DGResidualType type)
{
  Real r = 0;

  const unsigned int elem_b_order = static_cast<unsigned int>(_var.order());
  const double h_elem =
      _current_elem->volume() / _current_side_elem->volume() * 1. / std::pow(elem_b_order, 2.);

  switch (type)
  {
    case Moose::Element:
      r += 0.5 * (-_diff[_qp] * std::exp(_u[_qp]) * _grad_u[_qp] * _normals[_qp] * _test[_i][_qp] +
                  _epsilon * _grad_test[_i][_qp] * _normals[_qp] * std::exp(_u[_qp]));
      r += _sigma / h_elem * std::exp(_u[_qp]) * _test[_i][_qp];

      r += 0.5 * (-_diff_neighbor[_qp] * std::exp(_u_neighbor[_qp]) * _grad_u_neighbor[_qp] *
                      _normals[_qp] * _test[_i][_qp] -
                  _epsilon * _grad_test[_i][_qp] * _normals[_qp] * std::exp(_u_neighbor[_qp]));
      r += -_sigma / h_elem * std::exp(_u_neighbor[_qp]) * _test[_i][_qp];
      break;

    case Moose::Neighbor:
      r += 0.5 * (_diff[_qp] * std::exp(_u[_qp]) * _grad_u[_qp] * _normals[_qp] +
                  _diff_neighbor[_qp] * std::exp(_u_neighbor[_qp]) * _grad_u_neighbor[_qp] *
                      _normals[_qp]) *
           _test_neighbor[_i][_qp];
      r += _epsilon * 0.5 * _grad_test_neighbor[_i][_qp] * _normals[_qp] *
           (std::exp(_u[_qp]) - std::exp(_u_neighbor[_qp]));
      r -= _sigma / h_elem * (std::exp(_u[_qp]) - std::exp(_u_neighbor[_qp])) *
           _test_neighbor[_i][_qp];
      break;
  }

  return r;
}

Real
DGCoeffDiffusion::computeQpJacobian(Moose::DGJacobianType type)
{
  Real r = 0;

  const unsigned int elem_b_order = static_cast<unsigned int>(_var.order());
  const double h_elem =
      _current_elem->volume() / _current_side_elem->volume() * 1. / std::pow(elem_b_order, 2.);

  switch (type)
  {

    case Moose::ElementElement:
      r -= 0.5 * _diff[_qp] * (std::exp(_u[_qp]) * _grad_phi[_j][_qp] +
                               std::exp(_u[_qp]) * _phi[_j][_qp] * _grad_u[_qp]) *
           _normals[_qp] * _test[_i][_qp];
      r += _epsilon * 0.5 * _grad_test[_i][_qp] * _normals[_qp] * std::exp(_u[_qp]) * _phi[_j][_qp];
      r += _sigma / h_elem * std::exp(_u[_qp]) * _phi[_j][_qp] * _test[_i][_qp];
      break;

    case Moose::ElementNeighbor:
      r -= 0.5 * _diff_neighbor[_qp] *
           (std::exp(_u_neighbor[_qp]) * _grad_phi_neighbor[_j][_qp] +
            std::exp(_u_neighbor[_qp]) * _phi_neighbor[_j][_qp] * _grad_u_neighbor[_qp]) *
           _normals[_qp] * _test[_i][_qp];
      r -= _epsilon * 0.5 * _grad_test[_i][_qp] * _normals[_qp] * std::exp(_u_neighbor[_qp]) *
           _phi_neighbor[_j][_qp];
      r -= _sigma / h_elem * std::exp(_u_neighbor[_qp]) * _phi_neighbor[_j][_qp] * _test[_i][_qp];
      break;

    case Moose::NeighborElement:
      r += 0.5 * _diff[_qp] * (std::exp(_u[_qp]) * _grad_phi[_j][_qp] +
                               std::exp(_u[_qp]) * _phi[_j][_qp] * _grad_u[_qp]) *
           _normals[_qp] * _test_neighbor[_i][_qp];
      r += _epsilon * 0.5 * _grad_test_neighbor[_i][_qp] * _normals[_qp] * std::exp(_u[_qp]) *
           _phi[_j][_qp];
      r -= _sigma / h_elem * std::exp(_u[_qp]) * _phi[_j][_qp] * _test_neighbor[_i][_qp];
      break;

    case Moose::NeighborNeighbor:
      r += 0.5 * _diff_neighbor[_qp] *
           (std::exp(_u_neighbor[_qp]) * _grad_phi_neighbor[_j][_qp] +
            std::exp(_u_neighbor[_qp]) * _phi_neighbor[_j][_qp] * _grad_u_neighbor[_qp]) *
           _normals[_qp] * _test_neighbor[_i][_qp];
      r -= _epsilon * 0.5 * _grad_test_neighbor[_i][_qp] * _normals[_qp] *
           std::exp(_u_neighbor[_qp]) * _phi_neighbor[_j][_qp];
      r += _sigma / h_elem * std::exp(_u_neighbor[_qp]) * _phi_neighbor[_j][_qp] *
           _test_neighbor[_i][_qp];
      break;
  }

  return r;
}
