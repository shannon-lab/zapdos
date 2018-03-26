#include "TM0CylindricalErAux.h"

registerMooseObject("ZapdosApp", TM0CylindricalErAux);

template <>
InputParameters
validParams<TM0CylindricalErAux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("Hphi", "Magnetic field component Hphi.");
  params.addRequiredParam<Real>("f", "The drive frequency.");
  params.addParam<Real>("eps_r", 1., "The relative permittivity of the medium.");
  return params;
}

TM0CylindricalErAux::TM0CylindricalErAux(const InputParameters & parameters)
  : AuxKernel(parameters),
    _grad_Hphi(coupledGradient("Hphi")),
    _omega(2. * libMesh::pi * getParam<Real>("f")),
    _eps_r(getParam<Real>("eps_r")),
    _eps0(8.85e-12)
{
}

Real
TM0CylindricalErAux::computeValue()
{
  return _grad_Hphi[_qp](1) / (-_omega * _eps0 * _eps_r);
}
