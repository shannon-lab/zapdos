//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "TM0CylindricalErAux.h"

registerMooseObject("ZapdosApp", TM0CylindricalErAux);

InputParameters
TM0CylindricalErAux::validParams()
{
  InputParameters params = AuxKernel::validParams();
  params.addRequiredCoupledVar("Hphi", "Magnetic field component Hphi.");
  params.addRequiredParam<Real>("f", "The drive frequency.");
  params.addParam<Real>("eps_r", 1., "The relative permittivity of the medium.");
  params.addClassDescription("Calculates the radial E-field for an axisymmetric "
                             "TM$_{0}$ wave.");
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
