#include "PotentialDriftOutflowBC.h"

registerMooseObject("ZapdosApp", PotentialDriftOutflowBC);

template <>
InputParameters
validParams<PotentialDriftOutflowBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  MooseEnum charge_sign("positive=1 negative=-1", "positive");
  params.addRequiredCoupledVar(
      "potential", "The gradient of the potential will be used to compute the advection velocity.");

  params.addParam<MooseEnum>("charge_sign", charge_sign, "The sign of the charged particle.");
  return params;
}

PotentialDriftOutflowBC::PotentialDriftOutflowBC(const InputParameters & parameters)
  : IntegratedBC(parameters),
    _charge_sign(getParam<MooseEnum>("charge_sign")),
    _potential_id(coupled("potential")),
    _grad_potential(coupledGradient("potential"))
{
}

Real
PotentialDriftOutflowBC::computeQpResidual()
{
  if (_charge_sign * -_grad_potential[_qp] * _normals[_qp] > 0.)
    return _charge_sign * -_grad_potential[_qp] * _normals[_qp] * _u[_qp];
  else
    return 0.;
}

Real
PotentialDriftOutflowBC::computeQpJacobian()
{
  if (_charge_sign * -_grad_potential[_qp] * _normals[_qp] > 0.)
    return _charge_sign * -_grad_potential[_qp] * _normals[_qp] * _phi[_j][_qp];
  else
    return 0.;
}

Real
PotentialDriftOutflowBC::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id)
    if (_charge_sign * -_grad_potential[_qp] * _normals[_qp] > 0.)
      return _charge_sign * -_grad_phi[_j][_qp] * _normals[_qp] * _u[_qp];
    else
      return 0;

  else
    return 0.;
}
