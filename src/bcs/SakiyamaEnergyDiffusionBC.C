//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "SakiyamaEnergyDiffusionBC.h"
#include "Zapdos.h"

registerMooseObject("ZapdosApp", SakiyamaEnergyDiffusionBC);

InputParameters
SakiyamaEnergyDiffusionBC::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  params.addRequiredCoupledVar("electrons", "The electron density in log form");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addClassDescription("Kinetic advective electron energy boundary condition"
                             " (Based on [!cite](sakiyama2007nonthermal))");
  return params;
}

SakiyamaEnergyDiffusionBC::SakiyamaEnergyDiffusionBC(const InputParameters & parameters)
  : ADIntegratedBC(parameters),

    _r_units(1. / getParam<Real>("position_units")),

    // Coupled Variables
    _em(adCoupledValue("electrons")),

    _massem(getMaterialProperty<Real>("mass" + (*getVar("electrons", 0)).name())),
    _v_thermal(0)
{
}

ADReal
SakiyamaEnergyDiffusionBC::computeQpResidual()
{
  using std::exp;
  using std::sqrt;

  _v_thermal = sqrt(8 * ZAPDOS_CONSTANTS::e * 2.0 / 3 * exp(_u[_qp] - _em[_qp]) /
                    (libMesh::pi * _massem[_qp]));

  return _test[_i][_qp] * _r_units * ((5.0 / 3.0) * 0.25 * _v_thermal * exp(_u[_qp]));
}
