#include "TM0AntennaVertBC.h"

registerMooseObject("ZapdosApp", TM0AntennaVertBC);

template <>
InputParameters
validParams<TM0AntennaVertBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addRequiredParam<Real>("f", "The drive frequency.");
  params.addParam<Real>("eps_r", 1., "The relative permittivity.");
  params.addParam<bool>(
      "time_dependent", false, "Whether the antenna boundary condition should oscillate in time.");
  return params;
}

TM0AntennaVertBC::TM0AntennaVertBC(const InputParameters & parameters)
  : IntegratedBC(parameters),
    _omega(2. * libMesh::pi * getParam<Real>("f")),
    _eps_r(getParam<Real>("eps_r")),
    _eps0(8.85e-12),
    _time_dependent(getParam<bool>("time_dependent"))
{
}

Real
TM0AntennaVertBC::computeQpResidual()
{
  if (_time_dependent)
    return _test[_i][_qp] *
           (-_u[_qp] / _q_point[_qp](0) + _omega * _eps_r * _eps0 * std::cos(_omega * _t));

  else
    return _test[_i][_qp] * (-_u[_qp] / _q_point[_qp](0) + _omega * _eps_r * _eps0);
}

Real
TM0AntennaVertBC::computeQpJacobian()
{
  return _test[_i][_qp] * (-_phi[_j][_qp] / _q_point[_qp](0));
}
