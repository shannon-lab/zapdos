#include "DGAdvection.h"

template<>
InputParameters validParams<DGAdvection>()
{
  InputParameters params = validParams<DGKernel>();
  params.addParam<Real>("vx",0,"x-component of velocity vector");
  params.addParam<Real>("vy",0,"y-component of velocity vector");
  params.addParam<Real>("vz",0,"z-component of velocity vector");
  return params;
}

DGAdvection::DGAdvection(const InputParameters & parameters) :
    DGKernel(parameters),
    _vx(getParam<Real>("vx")),
    _vy(getParam<Real>("vy")),
    _vz(getParam<Real>("vz"))
{
  _velocity(0)=_vx;
  _velocity(1)=_vy;
  _velocity(2)=_vz;
}

Real
DGAdvection::computeQpResidual(Moose::DGResidualType type)
{
  // std::cout << "Current side is " << _current_side << std::endl;
  // std::cout << "Current element volume is " << _current_elem_volume << std::endl;
  // std::cout << "Current side volume is " << _current_side_volume << std::endl;
  Real r = 0;

  switch (type)
  {
    case Moose::Element:
      if ( (_velocity * _normals[_qp]) >= 0.0)
        r += (_velocity * _normals[_qp]) * _u[_qp] * _test[_i][_qp];
      else
        r += (_velocity * _normals[_qp]) * _u_neighbor[_qp] * _test[_i][_qp];
      break;

    case Moose::Neighbor:
      if ( (_velocity * _normals[_qp]) >= 0.0)
        r += -(_velocity * _normals[_qp]) * _u[_qp] * _test_neighbor[_i][_qp];
      else
        r += -(_velocity * _normals[_qp]) * _u_neighbor[_qp] * _test_neighbor[_i][_qp];
      break;
  }
  return r;
}

Real
DGAdvection::computeQpJacobian(Moose::DGJacobianType type)
{
  Real r = 0;

  switch (type)
  {

    case Moose::ElementElement:
      if ( (_velocity * _normals[_qp]) >= 0.0)
        r += (_velocity * _normals[_qp]) * _phi[_j][_qp] * _test[_i][_qp];
      else
        r += 0.0;
      break;

    case Moose::ElementNeighbor:
      if ( (_velocity * _normals[_qp]) >= 0.0)
        r += 0.0;
      else
        r += (_velocity * _normals[_qp]) * _phi_neighbor[_j][_qp] * _test[_i][_qp];
      break;

    case Moose::NeighborElement:
      if ( (_velocity * _normals[_qp]) >= 0.0)
        r += -(_velocity * _normals[_qp]) * _phi[_j][_qp] * _test_neighbor[_i][_qp];
      else
        r += 0.0;
      break;

    case Moose::NeighborNeighbor:
      if ( (_velocity * _normals[_qp]) >= 0.0)
        r += 0.0;
      else
        r += -(_velocity * _normals[_qp]) * _phi_neighbor[_j][_qp] * _test_neighbor[_i][_qp];
      break;
  }
  return r;
}
