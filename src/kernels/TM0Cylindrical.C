#include "TM0Cylindrical.h"

registerMooseObject("ZapdosApp", TM0Cylindrical);

template <>
InputParameters
validParams<TM0Cylindrical>()
{
  InputParameters params = validParams<Kernel>();
  // params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addRequiredParam<Real>("f", "The drive frequency.");
  return params;
}

TM0Cylindrical::TM0Cylindrical(const InputParameters & parameters)
  : Kernel(parameters),

    // _r_units(1. / getParam<Real>("position_units")),
    _omega(2. * libMesh::pi * getParam<Real>("f")),
    _eps_r(getMaterialProperty<Real>("eps_r")),
    _mu0(4. * libMesh::pi * 1e-7),
    _eps0(8.85e-12)
{
}

TM0Cylindrical::~TM0Cylindrical() {}

Real
TM0Cylindrical::computeQpResidual()
{
  return -_grad_test[_i][_qp] * _grad_u[_qp] -
         _test[_i][_qp] * _u[_qp] / std::pow(_q_point[_qp](0), 2) +
         _test[_i][_qp] * std::pow(_omega, 2) * _mu0 * _eps_r[_qp] * _eps0 * _u[_qp];
}

Real
TM0Cylindrical::computeQpJacobian()
{
  return -_grad_test[_i][_qp] * _grad_phi[_j][_qp] -
         _test[_i][_qp] * _phi[_j][_qp] / std::pow(_q_point[_qp](0), 2) +
         _test[_i][_qp] * std::pow(_omega, 2) * _mu0 * _eps_r[_qp] * _eps0 * _phi[_j][_qp];
}
