#include "SigmaMat.h"

registerMooseObject("ZapdosApp", SigmaMat);

template <>
InputParameters
validParams<SigmaMat>()
{
  InputParameters params = validParams<Material>();

  params.addRequiredCoupledVar("n", "The charge density.");
  params.addRequiredCoupledVar("potential", "The potential.");
  return params;
}

SigmaMat::SigmaMat(const InputParameters & parameters)
  : Material(parameters),

    // Declare material properties
    _sigma(declareProperty<Real>("sigma")),
    _sigma_old(getMaterialPropertyOld<Real>("sigma")),

    // Coupled Variables
    _n(coupledValue("n")),
    _grad_potential(coupledGradient("potential"))
{
}

void
SigmaMat::initQpStatefulProperties()
{
  _sigma[_qp] = 0;
}

void
SigmaMat::computeQpProperties()
{
  if (_material_data_type == Moose::FACE_MATERIAL_DATA || boundaryRestricted())
    _sigma[_qp] = _sigma_old[_qp] + _dt * -_grad_potential[_qp] * _n[_qp] * _normals[_qp];
  else
    _sigma[_qp] = 0.;
}
