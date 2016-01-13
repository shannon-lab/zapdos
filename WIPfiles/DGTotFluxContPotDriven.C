#include "DGTotFluxContPotDriven.h"

#include <cmath>

template<>
InputParameters validParams<DGTotFluxContPotDriven>()
{
  InputParameters params = validParams<InterfaceKernel>();
  params.addRequiredCoupledVar("potential","The electrical potential");
  params.addRequiredCoupledVar("potential_neighbor","The neighboring electrical potential");
  return params;
}

DGTotFluxContPotDriven::DGTotFluxContPotDriven(const InputParameters & parameters) :
    InterfaceKernel(parameters),
    _potential(coupledValue("potential")),
    _grad_potential(coupledGradient("potential")),
    _potential_id(coupled("potential")),
    _potential_neighbor(coupledValue("potential_neighbor")),
    _grad_potential_neighbor(coupledGradient("potential_neighbor")),
    _potential_neighbor_id(coupled("potential_neighbor")),
    _mu(getMaterialProperty
{
  if (!parameters.isParamValid("boundary")) {
    std::cerr << "In order to use this kernel, you must specify a boundary where it will live." << std::endl;
    std::exit(1);
  }
}

Real
DGTotFluxContPotDriven::computeQpResidual(Moose::DGResidualType type)
{
  Real r = 0;

  bool is_elem;
  if (type == Moose::Element)
    is_elem = true;
  else
    is_elem = false;

  const unsigned int elem_b_order = static_cast<unsigned int> (is_elem ? _var.getOrder() : _neighbor_var.getOrder());
  const double h_elem = _current_elem->volume()/_current_side_elem->volume() * 1./std::pow(elem_b_order, 2.);

  switch (type)
  {
  case Moose::Element:
    r += 0.5 * (-_D * _grad_u[_qp] * _normals[_qp] * _test[_i][_qp] + _epsilon * _grad_test[_i][_qp] * _normals[_qp] * _D * _u[_qp]);
    r += _sigma / h_elem * _u[_qp] * _test[_i][_qp];

    r += 0.5 * (-_D_neighbor * _grad_neighbor_value[_qp] * _normals[_qp] * _test[_i][_qp] - _epsilon * _grad_test[_i][_qp] * _normals[_qp] * _D_neighbor * _neighbor_value[_qp]);
    r += - _sigma / h_elem * _neighbor_value[_qp] * _test[_i][_qp];
    break;

  case Moose::Neighbor:
    r += 0.5 * (_D * _grad_u[_qp] * _normals[_qp] + _D_neighbor * _grad_neighbor_value[_qp] * _normals[_qp]) * _test_neighbor[_i][_qp];
    r += _epsilon * 0.5 * _grad_test_neighbor[_i][_qp] * _normals[_qp] * (_D * _u[_qp] - _D_neighbor * _neighbor_value[_qp]);
    r -= _sigma / h_elem * (_u[_qp] - _neighbor_value[_qp]) * _test_neighbor[_i][_qp];
    break;
  }

  // std::cout << "Inside of DGTotFluxContPotDriven residual calculation." << std::endl;
  // std::cout << "The value of the DGTotFluxContPotDriven residual is " << r << std::endl;
  return r;
}

Real
DGTotFluxContPotDriven::computeQpJacobian(Moose::DGJacobianType type)
{
  Real r = 0;

  bool is_elem;
  if (type == Moose::ElementElement || type == Moose::ElementNeighbor)
    is_elem = true;
  else
    is_elem = false;

  const unsigned int elem_b_order = static_cast<unsigned int> (is_elem ? _var.getOrder() : _neighbor_var.getOrder());
  const double h_elem = _current_elem->volume()/_current_side_elem->volume() * 1./std::pow(elem_b_order, 2.);

  switch (type)
  {

  case Moose::ElementElement:
    r -= 0.5 * _D * _grad_phi[_j][_qp] * _normals[_qp] * _test[_i][_qp];
    r += _epsilon * 0.5 * _grad_test[_i][_qp] * _normals[_qp] * _D * _phi[_j][_qp];
    r += _sigma / h_elem * _phi[_j][_qp] * _test[_i][_qp];
    break;

  case Moose::ElementNeighbor:
    r -= 0.5 * _D * _grad_phi_neighbor[_j][_qp] * _normals[_qp] * _test[_i][_qp];
    r -= _epsilon * 0.5 * _grad_test[_i][_qp] * _normals[_qp] * _D * _phi_neighbor[_j][_qp];
    r -= _sigma / h_elem * _phi_neighbor[_j][_qp] * _test[_i][_qp];
    break;

  case Moose::NeighborElement:
    r += 0.5 * _D * _grad_phi[_j][_qp] * _normals[_qp] * _test_neighbor[_i][_qp];
    r += _epsilon * 0.5 * _grad_test_neighbor[_i][_qp] * _normals[_qp] * _D * _phi[_j][_qp];
    r -= _sigma / h_elem * _phi[_j][_qp] * _test_neighbor[_i][_qp];
    break;

  case Moose::NeighborNeighbor:
    r += 0.5 * _D_neighbor * _grad_phi_neighbor[_j][_qp] * _normals[_qp] * _test_neighbor[_i][_qp];
    r -= _epsilon * 0.5 * _grad_test_neighbor[_i][_qp] * _normals[_qp] * _D_neighbor * _phi_neighbor[_j][_qp];
    r += _sigma / h_elem * _D_neighbor * _phi_neighbor[_j][_qp] * _test_neighbor[_i][_qp];
    break;
  }

  return r;
}

