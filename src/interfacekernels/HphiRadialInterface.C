#include "HphiRadialInterface.h"

#include <cmath>

registerMooseObject("ZapdosApp", HphiRadialInterface);

template <>
InputParameters
validParams<HphiRadialInterface>()
{
  InputParameters params = validParams<InterfaceKernel>();
  return params;
}

HphiRadialInterface::HphiRadialInterface(const InputParameters & parameters)
  : InterfaceKernel(parameters),
    _eps_r_neighbor(getNeighborMaterialProperty<Real>("eps_r")),
    _eps_r(getMaterialProperty<Real>("eps_r"))
{
  if (!parameters.isParamValid("boundary"))
  {
    mooseError("In order to use the HphiRadialInterface interface kernel, you must specify a "
               "boundary where it will live.");
  }
}

Real
HphiRadialInterface::computeQpResidual(Moose::DGResidualType type)
{
  // if (_eps_r_neighbor[_qp] < std::numeric_limits<double>::epsilon())
  //   mooseError("It doesn't appear that DG material properties got passed.");

  Real r = 0;

  switch (type)
  {
    case Moose::Element:
      r = _test[_i][_qp] * _eps_r[_qp] / _eps_r_neighbor[_qp] *
              (_grad_neighbor_value[_qp] * _normals[_qp] +
               _neighbor_value[_qp] / _q_point[_qp](0)) -
          _test[_i][_qp] * _neighbor_value[_qp] / _q_point[_qp](0);
      break;

    case Moose::Neighbor:
      r = 0.;
      break;
  }

  return r;
}

Real
HphiRadialInterface::computeQpJacobian(Moose::DGJacobianType type)
{
  Real jac = 0;
  switch (type)
  {
    case Moose::ElementNeighbor:
      jac += _test[_i][_qp] * _eps_r[_qp] / _eps_r_neighbor[_qp] *
                 (_grad_phi_neighbor[_j][_qp] * _normals[_qp] +
                  _phi_neighbor[_j][_qp] / _q_point[_qp](0)) -
             _test[_i][_qp] * _phi_neighbor[_j][_qp] / _q_point[_qp](0);
      break;

    default:
      break;
  }

  return jac;
}
