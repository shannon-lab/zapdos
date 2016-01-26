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

#include "InterfaceLogDiffusionElectrons.h"

#include <cmath>

template<>
InputParameters validParams<InterfaceLogDiffusionElectrons>()
{
  InputParameters params = validParams<InterfaceKernel>();
  params.addRequiredCoupledVar("mean_en_neighbor", "The log of the product of the mean energy and electron density on the slave side of the interface.");
  return params;
}

InterfaceLogDiffusionElectrons::InterfaceLogDiffusionElectrons(const InputParameters & parameters) :
    InterfaceKernel(parameters),
    _diffem(getNeighborMaterialProperty<Real>("diffem")),
    _d_diffem_d_actual_mean_en(getNeighborMaterialProperty<Real>("d_diffem_d_actual_mean_en")),
    _mean_en_neighbor_var(*getVar("mean_en_neighbor", 0)),
    _mean_en_neighbor(_mean_en_neighbor_var.slnNeighbor()),
    _mean_en_neighbor_id(coupled("mean_en_neighbor")),
    _actual_mean_en(0)
{
  if (!parameters.isParamValid("boundary"))
  {
    mooseError("In order to use the InterfaceLogDiffusionElectrons dgkernel, you must specify a boundary where it will live.");
  }
}

Real
InterfaceLogDiffusionElectrons::computeQpResidual(Moose::DGResidualType type)
{
  // if (_diffem[_qp] < std::numeric_limits<double>::epsilon())
  //   mooseError("It doesn't appear that DG material properties got passed.");

  Real r = 0;

  switch (type)
  {
  case Moose::Element:
    r = -_diffem[_qp] * std::exp(_neighbor_value[_qp]) * _grad_neighbor_value[_qp] * _normals[_qp] * _test[_i][_qp];
    break;

  case Moose::Neighbor:
    r = 0.;
    break;
  }

  return r;
}

Real
InterfaceLogDiffusionElectrons::computeQpJacobian(Moose::DGJacobianType type)
{
  return 0.;
}

Real
InterfaceLogDiffusionElectrons::computeQpOffDiagJacobian(Moose::DGJacobianType type, unsigned int jvar)
{
  Real jac = 0;

  if (jvar == _neighbor_var.number())
  {
    _actual_mean_en = std::exp(_mean_en_neighbor[_qp] - _neighbor_value[_qp]);
    jac = (-_d_diffem_d_actual_mean_en[_qp] * _actual_mean_en * -_phi_neighbor[_j][_qp] * std::exp(_neighbor_value[_qp]) * _grad_neighbor_value[_qp] - _diffem[_qp] * std::exp(_neighbor_value[_qp]) * _phi_neighbor[_j][_qp] * _grad_neighbor_value[_qp] - _diffem[_qp] * std::exp(_neighbor_value[_qp]) * _grad_phi_neighbor[_j][_qp]) * _normals[_qp] * _test[_i][_qp];
  }

  else if (jvar == _mean_en_neighbor_id)
  {
    switch (type)
    {
      case Moose::ElementNeighbor:
        _actual_mean_en = std::exp(_mean_en_neighbor[_qp] - _neighbor_value[_qp]);
        jac =  -_d_diffem_d_actual_mean_en[_qp] * _actual_mean_en * _phi_neighbor[_j][_qp] * std::exp(_neighbor_value[_qp]) * _grad_neighbor_value[_qp] * _normals[_qp] * _test[_i][_qp];
        break;
    }
  }

  return jac;
}
