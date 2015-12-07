#include "DGEFieldAdvection.h"

template<>
InputParameters validParams<DGEFieldAdvection>()
{
	InputParameters params = validParams<DGKernel>();
	return params;
}

DGEFieldAdvection::DGEFieldAdvection(const InputParameters & parameters) :
    DGKernel(parameters),

    _mu(getMaterialProperty<Real>("mu" + _var.name())),
    _sgn(getMaterialProperty<Real>("sgn" + _var.name())),
    _mu_neighbor(getNeighborMaterialProperty<Real>("mu" + _var.name())),
    _sgn_neighbor(getNeighborMaterialProperty<Real>("sgn" + _var.name())),
    _potential_id(coupled("potential")),
    _grad_potential(coupledGradient("potential"))
{
}

Real
DGEFieldAdvection::computeQpResidual(Moose::DGResidualType type)
{
	Real r = 0;
        RealVectorValue _velocity = _mu[_qp] * _sgn[_qp] * -_grad_potential[_qp];
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
DGEFieldAdvection::computeQpJacobian(Moose::DGJacobianType type)
{
	Real r = 0;
        RealVectorValue _velocity = _mu[_qp] * _sgn[_qp] * -_grad_potential[_qp];

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
