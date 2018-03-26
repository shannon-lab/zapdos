#include "TM0CylindricalEr.h"

registerMooseObject("ZapdosApp", TM0CylindricalEr);

template <>
InputParameters
validParams<TM0CylindricalEr>()
{
  InputParameters params = validParams<Kernel>();
  // params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addRequiredParam<Real>("f", "The drive frequency.");
  params.addRequiredCoupledVar("Hphi", "The phi component of the magnetic field.");
  return params;
}

TM0CylindricalEr::TM0CylindricalEr(const InputParameters & parameters)
  : Kernel(parameters),

    // _r_units(1. / getParam<Real>("position_units")),
    _omega(2. * libMesh::pi * getParam<Real>("f")),
    _eps_r(getMaterialProperty<Real>("eps_r")),
    _mu0(4. * libMesh::pi * 1e-7),
    _eps0(8.85e-12),
    _Hphi(coupledValue("Hphi")),
    _grad_Hphi(coupledGradient("Hphi")),
    _Hphi_id(coupled("Hphi"))
{
}

TM0CylindricalEr::~TM0CylindricalEr() {}

Real
TM0CylindricalEr::computeQpResidual()
{
  return _test[_i][_qp] * (_grad_Hphi[_qp](1) + _omega * _eps0 * _eps_r[_qp] * _u[_qp]);
}

Real
TM0CylindricalEr::computeQpJacobian()
{
  return _test[_i][_qp] * (_omega * _eps0 * _eps_r[_qp] * _phi[_j][_qp]);
}

Real
TM0CylindricalEr::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _Hphi_id)
    return _test[_i][_qp] * (_grad_phi[_j][_qp](1));

  else
    return 0.;
}
