//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "HagelaarEnergyBC.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("ZapdosApp", HagelaarEnergyBC);

template <>
InputParameters
validParams<HagelaarEnergyBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addRequiredParam<Real>("r", "The reflection coefficient");
  params.addRequiredCoupledVar("potential", "The electric potential");
  params.addRequiredCoupledVar("em", "The electron density.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  return params;
}

HagelaarEnergyBC::HagelaarEnergyBC(const InputParameters & parameters)
  : IntegratedBC(parameters),

    _r_units(1. / getParam<Real>("position_units")),
    _r(getParam<Real>("r")),

    // Coupled Variables
    _grad_potential(coupledGradient("potential")),
    _potential_id(coupled("potential")),
    _em(coupledValue("em")),
    _em_id(coupled("em")),

    _massem(getMaterialProperty<Real>("massem")),
    _e(getMaterialProperty<Real>("e")),
    //_se_coeff(getMaterialProperty<Real>("se_coeff")),
    //_se_energy(getMaterialProperty<Real>("se_energy")),
    _mumean_en(getMaterialProperty<Real>("mumean_en")),
    _d_mumean_en_d_actual_mean_en(getMaterialProperty<Real>("d_mumean_en_d_actual_mean_en")),
    _a(0.5),
    _v_thermal(0),
    _d_v_thermal_d_u(0),
    _d_v_thermal_d_em(0),
    _actual_mean_en(0)
{
}

Real
HagelaarEnergyBC::computeQpResidual()
{
  if (_normals[_qp] * -1.0 * -_grad_potential[_qp] > 0.0)
  {
    _a = 1.0;
  }
  else
  {
    _a = 0.0;
  }
  _v_thermal =
      std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_u[_qp] - _em[_qp]) / (M_PI * _massem[_qp]));

  return _test[_i][_qp] * _r_units * (1. - _r) / (1. + _r) *
         (-(2. * _a - 1.) * _mumean_en[_qp] * -_grad_potential[_qp] * _r_units * _normals[_qp] +
          5. / 6. * _v_thermal) *
         std::exp(_u[_qp]);
}

Real
HagelaarEnergyBC::computeQpJacobian()
{
  if (_normals[_qp] * -1.0 * -_grad_potential[_qp] > 0.0)
  {
    _a = 1.0;
  }
  else
  {
    _a = 0.0;
  }

  _actual_mean_en = std::exp(_u[_qp] - _em[_qp]);

  _v_thermal =
      std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_u[_qp] - _em[_qp]) / (M_PI * _massem[_qp]));

  _d_v_thermal_d_u = 0.5 / _v_thermal * 8 * _e[_qp] * 2.0 / 3 * std::exp(_u[_qp] - _em[_qp]) /
                     (M_PI * _massem[_qp]) * _phi[_j][_qp];

  return _test[_i][_qp] * _r_units * (1 - _r) / (1 + _r) *
         ((-(2. * _a - 1) * _d_mumean_en_d_actual_mean_en[_qp] * _actual_mean_en * _phi[_j][_qp] *
               -_grad_potential[_qp] * _r_units * _normals[_qp] +
           5. / 6. * _d_v_thermal_d_u) *
              std::exp(_u[_qp]) +
          (-(2. * _a - 1) * _mumean_en[_qp] * -_grad_potential[_qp] * _r_units * _normals[_qp] +
           5. / 6. * _v_thermal) *
              std::exp(_u[_qp]) * _phi[_j][_qp]);
}

Real
HagelaarEnergyBC::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id)
  {
    if (_normals[_qp] * -1.0 * -_grad_potential[_qp] > 0.0)
      _a = 1.0;
    else
      _a = 0.0;

    _v_thermal =
        std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_u[_qp] - _em[_qp]) / (M_PI * _massem[_qp]));

    return _test[_i][_qp] * _r_units * (1 - _r) / (1 + _r) *
           (-(2 * _a - 1) * _mumean_en[_qp] * -_grad_phi[_j][_qp] * _r_units * _normals[_qp] +
            5. / 6. * _v_thermal) *
           std::exp(_u[_qp]);
  }

  else if (jvar == _em_id)
  {
    if (_normals[_qp] * -1.0 * -_grad_potential[_qp] > 0.0)
    {
      _a = 1.0;
    }
    else
    {
      _a = 0.0;
    }
    _v_thermal =
        std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_u[_qp] - _em[_qp]) / (M_PI * _massem[_qp]));
    _d_v_thermal_d_em = 0.5 / _v_thermal * 8 * _e[_qp] * 2.0 / 3 * std::exp(_u[_qp] - _em[_qp]) /
                        (M_PI * _massem[_qp]) * -_phi[_j][_qp];

    _actual_mean_en = std::exp(_u[_qp] - _em[_qp]);

    return _test[_i][_qp] * _r_units * (1 - _r) / (1 + _r) *
           (-(2 * _a - 1) * _d_mumean_en_d_actual_mean_en[_qp] * _actual_mean_en * -_phi[_j][_qp] *
                -_grad_potential[_qp] * _r_units * _normals[_qp] +
            5. / 6. * _d_v_thermal_d_em) *
           std::exp(_u[_qp]);
  }
  else
    return 0.0;
}
