//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "TM0CylindricalEzAux.h"
#include "Zapdos.h"

registerMooseObject("ZapdosApp", TM0CylindricalEzAux);

InputParameters
TM0CylindricalEzAux::validParams()
{
  InputParameters params = AuxKernel::validParams();
  params.addRequiredCoupledVar("azimuthal_magnetic_field",
                               "The azimuthal component of the magnetic field, $H_{\\phi}$.");
  params.addRequiredParam<Real>("f", "The drive frequency.");
  params.addParam<Real>("eps_r", 1., "The relative permittivity of the medium.");
  params.addClassDescription("Calculates the axial E-field for an axisymmetric "
                             "TM$_{0}$ wave.");
  return params;
}

TM0CylindricalEzAux::TM0CylindricalEzAux(const InputParameters & parameters)
  : AuxKernel(parameters),
    _grad_Hphi(coupledGradient("azimuthal_magnetic_field")),
    _Hphi(coupledValue("azimuthal_magnetic_field")),
    _omega(2. * libMesh::pi * getParam<Real>("f")),
    _eps_r(getParam<Real>("eps_r"))
{
}

Real
TM0CylindricalEzAux::computeValue()
{
  return (_Hphi[_qp] / _q_point[_qp](0) + _grad_Hphi[_qp](0)) /
         (_omega * ZAPDOS_CONSTANTS::eps_0 * _eps_r);
}
