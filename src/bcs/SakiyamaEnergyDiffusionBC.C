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

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("ZapdosApp", SakiyamaEnergyDiffusionBC);

template <>
InputParameters
validParams<SakiyamaEnergyDiffusionBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addRequiredCoupledVar("em", "The electron density.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addClassDescription("Kinetic advective electron energy boundary condition"
                             "(Based on DOI: https://doi.org/10.1116/1.579300)");
  return params;
}

SakiyamaEnergyDiffusionBC::SakiyamaEnergyDiffusionBC(const InputParameters & parameters)
  : IntegratedBC(parameters),

    _r_units(1. / getParam<Real>("position_units")),

    // Coupled Variables
    _em(coupledValue("em")),
    _em_id(coupled("em")),

    _massem(getMaterialProperty<Real>("massem")),
    _e(getMaterialProperty<Real>("e")),
    _a(0.5),
    _v_thermal(0),
    _d_v_thermal_d_u(0),
    _d_v_thermal_d_em(0)
{
}

Real
SakiyamaEnergyDiffusionBC::computeQpResidual()
{

  _v_thermal =
      std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_u[_qp] - _em[_qp]) / (M_PI * _massem[_qp]));

  return _test[_i][_qp] * _r_units * ((5.0 / 3.0) * 0.25 * _v_thermal * std::exp(_u[_qp]));
}

Real
SakiyamaEnergyDiffusionBC::computeQpJacobian()
{

  _v_thermal =
      std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_u[_qp] - _em[_qp]) / (M_PI * _massem[_qp]));
  _d_v_thermal_d_u = 0.5 / _v_thermal * 8 * _e[_qp] * 2.0 / 3 * std::exp(_u[_qp] - _em[_qp]) /
                     (M_PI * _massem[_qp]) * _phi[_j][_qp];

  return _test[_i][_qp] * _r_units *
         ((5.0 / 3.0) * 0.25 * _d_v_thermal_d_u * std::exp(_u[_qp]) +
          (5.0 / 3.0) * 0.25 * _v_thermal * std::exp(_u[_qp]) * _phi[_j][_qp]);
}

Real
SakiyamaEnergyDiffusionBC::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _em_id)
  {

    _v_thermal =
        std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_u[_qp] - _em[_qp]) / (M_PI * _massem[_qp]));
    _d_v_thermal_d_em = 0.5 / _v_thermal * 8 * _e[_qp] * 2.0 / 3 * std::exp(_u[_qp] - _em[_qp]) /
                        (M_PI * _massem[_qp]) * -_phi[_j][_qp];

    return _test[_i][_qp] * _r_units * ((5.0 / 3.0) * 0.25 * _d_v_thermal_d_em * std::exp(_u[_qp]));
  }

  else
    return 0.0;
}
