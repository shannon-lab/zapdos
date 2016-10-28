#include "DriftDiffusion.h"

template<>
InputParameters validParams<DriftDiffusion>()
{
	InputParameters params = validParams<Kernel>();
	params.addRequiredCoupledVar("potential", "The gradient of the potential will be used to compute the advection velocity.");
	params.addRequiredParam<Real>("position_units", "Units of position.");
	return params;
}

// This diffusion kernel should only be used with species whose values are in the logarithmic form.

DriftDiffusion::DriftDiffusion(const InputParameters & parameters) :
	Kernel(parameters),

	_r_units(1. / getParam<Real>("position_units")),

	_mu(getMaterialProperty<Real>("mu" + _var.name())),
	_sign(getMaterialProperty<Real>("sgn" + _var.name())),
	_diffusivity(getMaterialProperty<Real>("diff" + _var.name())),

	// Coupled variables
	_potential_id(coupled("potential")),
	_grad_potential(coupledGradient("potential"))
{}

DriftDiffusion::~DriftDiffusion()
{}

Real
DriftDiffusion::computeQpResidual()
{
	return _mu[_qp] * _sign[_qp] * std::exp(_u[_qp]) * -_grad_potential[_qp] * _r_units * -_grad_test[_i][_qp] * _r_units
			- _diffusivity[_qp] * std::exp(_u[_qp]) * _grad_u[_qp] * _r_units * -_grad_test[_i][_qp] * _r_units;
}

Real
DriftDiffusion::computeQpJacobian()
{
	return _mu[_qp] * _sign[_qp] * std::exp(_u[_qp]) * _phi[_j][_qp] * -_grad_potential[_qp] * _r_units * -_grad_test[_i][_qp] * _r_units
			- _diffusivity[_qp] * (std::exp(_u[_qp]) * _grad_phi[_j][_qp] * _r_units + std::exp(_u[_qp]) * _phi[_j][_qp] * _grad_u[_qp] * _r_units) * -_grad_test[_i][_qp] * _r_units;
}

Real DriftDiffusion::computeQpOffDiagJacobian(unsigned int jvar)
{
	if (jvar == _potential_id) {
		return _mu[_qp] * _sign[_qp] * std::exp(_u[_qp]) * -_grad_phi[_j][_qp] * _r_units * -_grad_test[_i][_qp] * _r_units;
	} else {
		return 0.;
	}
}

