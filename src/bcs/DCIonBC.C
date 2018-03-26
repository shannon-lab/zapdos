#include "DCIonBC.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("ZapdosApp", DCIonBC);

template <>
InputParameters
validParams<DCIonBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addRequiredCoupledVar("potential", "The electrical potential");
  params.addRequiredParam<Real>("position_units", "Units of position");
  return params;
}

DCIonBC::DCIonBC(const InputParameters & parameters)
  : IntegratedBC(parameters),

    _mu(getMaterialProperty<Real>("mu" + _var.name())),
    _sgn(getMaterialProperty<Real>("sgn" + _var.name())),
    // _vthermal_ip(getMaterialProperty<Real>("vthermal_ip")),
    _a(0.0),
    _r_units(1. / getParam<Real>("position_units")),

    // coupled variables

    _grad_potential(coupledGradient("potential")),
    _potential_id(coupled("potential"))
{
}

Real
DCIonBC::computeQpResidual()
{
  if (_normals[_qp] * _sgn[_qp] * -_grad_potential[_qp] > 0.0)
  {
    _a = 1.0;
  }
  else
  {
    _a = 0.0;
  }

  return _test[_i][_qp] * _r_units * (_a * _mu[_qp] * _sgn[_qp] * -_grad_potential[_qp] * _r_units *
                                      std::exp(_u[_qp]) * _normals[_qp]);
}

Real
DCIonBC::computeQpJacobian()
{
  if (_normals[_qp] * _sgn[_qp] * -_grad_potential[_qp] > 0.0)
  {
    _a = 1.0;
  }
  else
  {
    _a = 0.0;
  }

  return _test[_i][_qp] * _r_units * (_a * _mu[_qp] * _sgn[_qp] * -_grad_potential[_qp] * _r_units *
                                      std::exp(_u[_qp]) * _phi[_j][_qp] * _normals[_qp]);
}

Real
DCIonBC::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id)
  {
    if (_normals[_qp] * _sgn[_qp] * -_grad_potential[_qp] > 0.0)
    {
      _a = 1.0;
    }
    else
    {
      _a = 0.0;
    }
    return _test[_i][_qp] * _r_units * (_a * _mu[_qp] * _sgn[_qp] * -_grad_phi[_j][_qp] * _r_units *
                                        std::exp(_u[_qp]) * _normals[_qp]);
  }
  else
  {
    return 0.0;
  }
}
