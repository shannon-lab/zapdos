#include "TM0CylindricalEzAux.h"

registerMooseObject("ZapdosApp", TM0CylindricalEzAux);

template <>
InputParameters
validParams<TM0CylindricalEzAux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("Hphi", "Magnetic field component Hphi.");
  params.addRequiredParam<Real>("f", "The drive frequency.");
  params.addParam<Real>("eps_r", 1., "The relative permittivity of the medium.");
  return params;
}

TM0CylindricalEzAux::TM0CylindricalEzAux(const InputParameters & parameters)
  : AuxKernel(parameters),
    _grad_Hphi(coupledGradient("Hphi")),
    _Hphi(coupledValue("Hphi")),
    _omega(2. * libMesh::pi * getParam<Real>("f")),
    _eps_r(getParam<Real>("eps_r")),
    _eps0(8.85e-12)
{
}

Real
TM0CylindricalEzAux::computeValue()
{
  return (_Hphi[_qp] / _q_point[_qp](0) + _grad_Hphi[_qp](0)) / (_omega * _eps0 * _eps_r);
}
