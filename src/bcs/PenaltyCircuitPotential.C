#include "PenaltyCircuitPotential.h"

template<>
InputParameters validParams<PenaltyCircuitPotential>()
{
  InputParameters p = validParams<NonlocalIntegratedBC>();
  p.addRequiredParam<UserObjectName>("current", "The postprocessor response for calculating the current passing through the needle surface.");
  p.addRequiredParam<Real>("surface_potential", "The electrical potential applied to the surface if no current was flowing in the circuit.");
  p.addRequiredParam<std::string>("surface", "Whether you are specifying the potential on the anode or the cathode with the requirement that the other metal surface be grounded.");
  p.addRequiredParam<Real>("penalty", "The constant multiplying the penalty term.");
  p.addRequiredParam<UserObjectName>("data_provider", "The name of the UserObject that can provide some data to materials, bcs, etc.");
  p.addRequiredCoupledVar("em", "The electron variable.");
  p.addRequiredCoupledVar("ip", "The ion variable.");
  return p;
}


PenaltyCircuitPotential::PenaltyCircuitPotential(const InputParameters & parameters) :
  NonlocalIntegratedBC(parameters),
  _current_uo(getUserObject<CurrentDensityShapeSideUserObject>("current")),
  _current(_current_uo.getIntegral()),
  _current_jac(_current_uo.getJacobian()),
  _surface_potential(getParam<Real>("surface_potential")),
  _surface(getParam<std::string>("surface")),
  _p(getParam<Real>("penalty")),
  _data(getUserObject<ProvideMobility>("data_provider")),
  _var_dofs(_var.dofIndices()),
  _em_id(coupled("em")),
  _em_dofs(getVar("em", 0)->dofIndices()),
  _ip_id(coupled("ip")),
  _ip_dofs(getVar("ip", 0)->dofIndices())
{
  if (_surface.compare("anode") == 0)
    _current_sign = -1.;
  else if (_surface.compare("cathode") == 0)
    _current_sign = 1.;
}

Real
PenaltyCircuitPotential::computeQpResidual()
{
  return _test[_i][_qp] * _p * (_surface_potential - _u[_qp] + _current_sign * _current);
}

Real
PenaltyCircuitPotential::computeQpJacobian()
{
  return _test[_i][_qp] * _p * (-_phi[_j][_qp] + _current_sign * _current_jac[_var_dofs[_j]]);
}

Real
PenaltyCircuitPotential::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _em_id)
    return _test[_i][_qp] * _p * _current_sign * _current_jac[_em_dofs[_j]];

  else if (jvar == _ip_id)
    return _test[_i][_qp] * _p * _current_sign * _current_jac[_ip_dofs[_j]];

  else
    return 0;
}

Real
PenaltyCircuitPotential::computeQpNonlocalJacobian(dof_id_type dof_index)
{
  return _test[_i][_qp] * _p * _current_sign * _current_jac[dof_index];
}

Real
PenaltyCircuitPotential::computeQpNonlocalOffDiagJacobian(unsigned int jvar, dof_id_type dof_index)
{
  if (jvar == _em_id || jvar == _ip_id)
    return _test[_i][_qp] * _p * _current_sign * _current_jac[dof_index];

  return 0;
}
