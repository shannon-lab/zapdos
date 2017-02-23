#include "PotentialDriftOutflowBC.h"

template<>
InputParameters validParams<PotentialDriftOutflowBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  MooseEnum charge_sign("positive=1
  params.addRequiredCoupledVar("potential", "The gradient of the potential will be used to compute the advection velocity.");

  params.addParam<Real>("sign", "The sign of the charged particle.");
  return params;
}

PotentialDriftOutflowBC::PotentialDriftOutflowBC(const InputParameters & parameters) :
    IntegratedBC(parameters),

    _r_units(1. / getParam<Real>("position_units")),

    _mu(getParam<bool>("use_material_props") ? getMaterialProperty<Real>("mu" + _var.name()) : _user_mu),
    _sign(getParam<bool>("use_material_props") ? getMaterialProperty<Real>("sgn" + _var.name()) : _user_sign),
    _diffusivity(getParam<bool>("use_material_props") ? getMaterialProperty<Real>("diff" + _var.name()) : _user_diff),

    // Coupled variables
    _potential_id(coupled("potential")),
    _grad_potential(isCoupled("potential") ? coupledGradient("potential") : _minus_e_field)
{
  if (!(isCoupled("potential") || parameters.isParamSetByUser("EField")))
    mooseError("You must either couple in a potential variable or set an EField.");

  if (!(isCoupled("potential")))
    _minus_e_field.resize(_fe_problem.getMaxQps(), RealGradient(-getParam<Real>("EField")));
  _user_diff.set().resize(_fe_problem.getMaxQps(), Real(getParam<Real>("diff")));
  _user_mu.set().resize(_fe_problem.getMaxQps(), Real(getParam<Real>("mu")));
  _user_sign.set().resize(_fe_problem.getMaxQps(), Real(getParam<Real>("sign")));
}

PotentialDriftOutflowBC::~PotentialDriftOutflowBC()
{}

Real
PotentialDriftOutflowBC::computeQpResidual()
{
  return _mu[_qp] * _sign[_qp] * std::exp(_u[_qp]) * -_grad_potential[_qp] * _r_units * _normals[_qp] * _test[_i][_qp] * _r_units
    - _diffusivity[_qp] * std::exp(_u[_qp]) * _grad_u[_qp] * _r_units * _normals[_qp] * _test[_i][_qp] * _r_units;
}

Real
PotentialDriftOutflowBC::computeQpJacobian()
{
  return _mu[_qp] * _sign[_qp] * std::exp(_u[_qp]) * _phi[_j][_qp] * -_grad_potential[_qp] * _r_units * _normals[_qp] * _test[_i][_qp] * _r_units
    - _diffusivity[_qp] * (std::exp(_u[_qp]) * _grad_phi[_j][_qp] * _r_units + std::exp(_u[_qp]) * _phi[_j][_qp] * _grad_u[_qp] * _r_units) * _normals[_qp] * _test[_i][_qp] * _r_units;
}

Real PotentialDriftOutflowBC::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id) {
    return _mu[_qp] * _sign[_qp] * std::exp(_u[_qp]) * -_grad_phi[_j][_qp] * _r_units * _normals[_qp] * _test[_i][_qp] * _r_units;
  }
  else {
    return 0.;
  }
}
