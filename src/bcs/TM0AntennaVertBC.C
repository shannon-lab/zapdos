#include "TM0AntennaVertBC.h"

template<>
InputParameters validParams<TM0AntennaVertBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addRequiredParam<Real>("f", "The drive frequency.");
  params.addParam<Real>("eps_r", 1., "The relative permittivity.");
  return params;
}

TM0AntennaVertBC::TM0AntennaVertBC(const InputParameters & parameters) :
  IntegratedBC(parameters),
  _omega(2. * libMesh::pi * getParam<Real>("f")),
  _eps_r(getParam<Real>("eps_r")),
  _eps0(8.85e-12)
{}

Real
TM0AntennaVertBC::computeQpResidual()
{
  return _test[_i][_qp] * (-_u[_qp] / _q_point[_qp](0) + _omega * _eps_r * _eps0);// * std::cos(_omega * _t));
}

Real
TM0AntennaVertBC::computeQpJacobian()
{
  return _test[_i][_qp] * (-_phi[_j][_qp] / _q_point[_qp](0));
}
