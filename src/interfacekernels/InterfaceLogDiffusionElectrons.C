#include "InterfaceLogDiffusionElectrons.h"

// MOOSE includes
#include "MooseVariable.h"

#include <cmath>

registerMooseObject("ZapdosApp", InterfaceLogDiffusionElectrons);

template <>
InputParameters
validParams<InterfaceLogDiffusionElectrons>()
{
  InputParameters params = validParams<InterfaceKernel>();
  params.addRequiredCoupledVar("mean_en_neighbor",
                               "The log of the product of the mean energy and "
                               "electron density on the slave side of the "
                               "interface.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addRequiredParam<Real>("neighbor_position_units",
                                "The units of position in the neighboring domain.");
  return params;
}

InterfaceLogDiffusionElectrons::InterfaceLogDiffusionElectrons(const InputParameters & parameters)
  : InterfaceKernel(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _r_neighbor_units(1. / getParam<Real>("neighbor_position_units")),

    _diffem(getNeighborMaterialProperty<Real>("diffem")),
    _d_diffem_d_actual_mean_en(getNeighborMaterialProperty<Real>("d_diffem_d_actual_mean_en")),
    _mean_en_neighbor_var(*getVar("mean_en_neighbor", 0)),
    _mean_en_neighbor(_mean_en_neighbor_var.slnNeighbor()),
    _mean_en_neighbor_id(coupled("mean_en_neighbor")),
    _actual_mean_en(0)
{
  if (!parameters.isParamValid("boundary"))
  {
    mooseError("In order to use the InterfaceLogDiffusionElectrons dgkernel, you must specify a "
               "boundary where it will live.");
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
      r = -_diffem[_qp] * std::exp(_neighbor_value[_qp]) * _grad_neighbor_value[_qp] *
          _r_neighbor_units * _normals[_qp] * _test[_i][_qp] * _r_units;
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
  Real jac = 0;
  switch (type)
  {
    case Moose::ElementNeighbor:
      _actual_mean_en = std::exp(_mean_en_neighbor[_qp] - _neighbor_value[_qp]);
      jac += (-_d_diffem_d_actual_mean_en[_qp] * _actual_mean_en * -_phi_neighbor[_j][_qp] *
                  std::exp(_neighbor_value[_qp]) * _grad_neighbor_value[_qp] * _r_neighbor_units -
              _diffem[_qp] * std::exp(_neighbor_value[_qp]) * _phi_neighbor[_j][_qp] *
                  _grad_neighbor_value[_qp] * _r_neighbor_units -
              _diffem[_qp] * std::exp(_neighbor_value[_qp]) * _grad_phi_neighbor[_j][_qp] *
                  _r_neighbor_units) *
             _normals[_qp] * _test[_i][_qp] * _r_units;
      break;

    default:
      break;
  }

  return jac;
}

Real
InterfaceLogDiffusionElectrons::computeQpOffDiagJacobian(Moose::DGJacobianType type,
                                                         unsigned int jvar)
{
  Real jac = 0;

  if (jvar == _mean_en_neighbor_id)
  {
    switch (type)
    {
      case Moose::ElementElement:
        jac = 0;
        break;

      case Moose::ElementNeighbor:
        _actual_mean_en = std::exp(_mean_en_neighbor[_qp] - _neighbor_value[_qp]);
        jac = -_d_diffem_d_actual_mean_en[_qp] * _actual_mean_en * _phi_neighbor[_j][_qp] *
              std::exp(_neighbor_value[_qp]) * _grad_neighbor_value[_qp] * _r_neighbor_units *
              _normals[_qp] * _test[_i][_qp] * _r_units;
        break;

      case Moose::NeighborElement:
        jac = 0;
        break;

      case Moose::NeighborNeighbor:
        jac = 0;
        break;
    }
  }

  return jac;
}
