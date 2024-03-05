//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "TM0CylindricalEr.h"

registerMooseObject("ZapdosApp", TM0CylindricalEr);

InputParameters
TM0CylindricalEr::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addRequiredParam<Real>("f", "The drive frequency.");
  params.addRequiredCoupledVar("Hphi", "The phi component of the magnetic field.");
  params.addClassDescription(
      "The axisymmetric wave equation for the radial component of the electric field.");
  return params;
}

TM0CylindricalEr::TM0CylindricalEr(const InputParameters & parameters)
  : ADKernel(parameters),

    _omega(2. * libMesh::pi * getParam<Real>("f")),
    _eps_r(getADMaterialProperty<Real>("eps_r")),
    _mu0(4. * libMesh::pi * 1e-7),
    _eps0(8.85e-12),
    _Hphi(adCoupledValue("Hphi")),
    _grad_Hphi(adCoupledGradient("Hphi"))
{
}

ADReal
TM0CylindricalEr::computeQpResidual()
{
  return _test[_i][_qp] * (_grad_Hphi[_qp](1) + _omega * _eps0 * _eps_r[_qp] * _u[_qp]);
}
