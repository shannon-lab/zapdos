//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "SakiyamaElectronDiffusionBC.h"

registerMooseObject("ZapdosApp", SakiyamaElectronDiffusionBC);

template <>
InputParameters
validParams<SakiyamaElectronDiffusionBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  //params.addRequiredParam<Real>("r", "The reflection coefficient");
  params.addRequiredCoupledVar("mean_en", "The mean energy.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addClassDescription(
    "Kinetic electron boundary condition"
    "(Based on DOI: https://doi.org/10.1116/1.579300)");
  return params;
}

SakiyamaElectronDiffusionBC::SakiyamaElectronDiffusionBC(const InputParameters & parameters)
  : IntegratedBC(parameters),

    _r_units(1. / getParam<Real>("position_units")),

    // Coupled Variables
    _mean_en(coupledValue("mean_en")),
    _mean_en_id(coupled("mean_en")),

    _massem(getMaterialProperty<Real>("massem")),
    _e(getMaterialProperty<Real>("e")),
    _a(0.5),
    _v_thermal(0),
    _d_v_thermal_d_u(0),
    _d_v_thermal_d_mean_en(0),
    _actual_mean_en(0)
{
}

Real
SakiyamaElectronDiffusionBC::computeQpResidual()
{

  _v_thermal =
      std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_mean_en[_qp] - _u[_qp]) / (M_PI * _massem[_qp]));

  return _test[_i][_qp] * _r_units *
         (0.25 * _v_thermal * std::exp(_u[_qp]));
}

Real
SakiyamaElectronDiffusionBC::computeQpJacobian()
{

  _actual_mean_en = std::exp(_mean_en[_qp] - _u[_qp]);
  _v_thermal =
      std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_mean_en[_qp] - _u[_qp]) / (M_PI * _massem[_qp]));
  _d_v_thermal_d_u = 0.5 / _v_thermal * 8 * _e[_qp] * 2.0 / 3 * std::exp(_mean_en[_qp] - _u[_qp]) /
                     (M_PI * _massem[_qp]) * -_phi[_j][_qp];

  return _test[_i][_qp] * _r_units *
         (0.25 * _d_v_thermal_d_u * std::exp(_u[_qp]) +
          0.25 * _v_thermal * std::exp(_u[_qp]) * _phi[_j][_qp]);
}

Real
SakiyamaElectronDiffusionBC::computeQpOffDiagJacobian(unsigned int jvar)
{

  if (jvar == _mean_en_id)
  {

    _v_thermal = std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_mean_en[_qp] - _u[_qp]) /
                           (M_PI * _massem[_qp]));
    _d_v_thermal_d_mean_en = 0.5 / _v_thermal * 8 * _e[_qp] * 2.0 / 3 *
                             std::exp(_mean_en[_qp] - _u[_qp]) / (M_PI * _massem[_qp]) *
                             _phi[_j][_qp];
    _actual_mean_en = std::exp(_mean_en[_qp] - _u[_qp]);

    return _test[_i][_qp] * _r_units *
           (0.25 * _d_v_thermal_d_mean_en * std::exp(_u[_qp]));
  }

  else
    return 0.0;
}
