#include "GAdvection.h"

template<>
InputParameters validParams<GAdvection>()
{
	InputParameters params = validParams<Kernel>();
	params.addParam<Real>("vx",0, "x-component of velocity vector");
	params.addParam<Real>("vy",0,"y-component of velocity vector");
	params.addParam<Real>("vz",0,"z-component of velocity vector");
	return params;
}

GAdvection::GAdvection(const InputParameters & parameters) :
Kernel(parameters),
_vx(getParam<Real>("vx")),
_vy(getParam<Real>("vy")),
_vz(getParam<Real>("vz"))

{
	_velocity(0)=_vx;
	_velocity(1)=_vy;
	_velocity(2)=_vz;
}

Real GAdvection::computeQpResidual()
{
	return -_u[_qp]*(_velocity*_grad_test[_i][_qp]);
}

Real GAdvection::computeQpJacobian()
{
	return -_phi[_j][_qp]*(_velocity*_grad_test[_i][_qp]);
}