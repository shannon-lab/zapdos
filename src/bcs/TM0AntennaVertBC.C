//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "TM0AntennaVertBC.h"
#include "Zapdos.h"

registerMooseObject("ZapdosApp", TM0AntennaVertBC);

InputParameters
TM0AntennaVertBC::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  params.addRequiredParam<Real>("f", "The drive frequency.");
  params.addParam<Real>("eps_r", 1., "The relative permittivity.");
  params.addParam<bool>(
      "time_dependent", false, "Whether the antenna boundary condition should oscillate in time.");
  params.addClassDescription(
      "A simple vertical antenna BC of the azimuthal component of the magnetizing field.");
  return params;
}

TM0AntennaVertBC::TM0AntennaVertBC(const InputParameters & parameters)
  : ADIntegratedBC(parameters),
    _omega(2. * libMesh::pi * getParam<Real>("f")),
    _eps_r(getParam<Real>("eps_r")),
    _eps0(8.85e-12),
    _time_dependent(getParam<bool>("time_dependent"))
{
}

ADReal
TM0AntennaVertBC::computeQpResidual()
{
  if (_time_dependent)
    return _test[_i][_qp] * (-_u[_qp] / _q_point[_qp](0) +
                             _omega * _eps_r * ZAPDOS_CONSTANTS::eps_0 * std::cos(_omega * _t));

  else
    return _test[_i][_qp] *
           (-_u[_qp] / _q_point[_qp](0) + _omega * _eps_r * ZAPDOS_CONSTANTS::eps_0);
}
