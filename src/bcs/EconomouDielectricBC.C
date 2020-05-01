//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "EconomouDielectricBC.h"

#include "MooseVariable.h"

registerMooseObject("ZapdosApp", EconomouDielectricBC);

template <>
InputParameters
validParams<EconomouDielectricBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addRequiredParam<Real>("dielectric_constant", "The dielectric constant of the material.");
  params.addRequiredParam<Real>("thickness", "The thickness of the material.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addRequiredCoupledVar("mean_en", "The mean energy.");
  params.addRequiredCoupledVar("em", "The electron density.");
  params.addRequiredCoupledVar("ip", "The ion density.");
  params.addRequiredCoupledVar("potential_ion", "The ion potential");
  params.addParam<Real>("users_gamma",
                        "A secondary electron emission coeff. only used for this BC.");
  params.addRequiredParam<std::string>("potential_units", "The potential units.");
  params.addClassDescription("Dielectric boundary condition"
                             "(Based on DOI: https://doi.org/10.1116/1.579300)");
  return params;
}

EconomouDielectricBC::EconomouDielectricBC(const InputParameters & parameters)
  : IntegratedBC(parameters),
    _r_units(1. / getParam<Real>("position_units")),

    _mean_en(coupledValue("mean_en")),
    _mean_en_id(coupled("mean_en")),
    _em(coupledValue("em")),
    _em_id(coupled("em")),
    _grad_u_dot(_var.gradSlnDot()),
    _u_dot(_var.uDot()),
    _du_dot_du(_var.duDotDu()),

    _e(getMaterialProperty<Real>("e")),
    _massem(getMaterialProperty<Real>("massem")),
    _user_se_coeff(getParam<Real>("users_gamma")),

    _epsilon_d(getParam<Real>("dielectric_constant")),
    _thickness(getParam<Real>("thickness")),
    _a(0.5),
    _ion_flux(0, 0, 0),
    _v_thermal(0),
    _em_flux(0, 0, 0),
    _d_ion_flux_du(0, 0, 0),
    _d_em_flux_du(0, 0, 0),
    _d_v_thermal_d_mean_en(0),
    _d_em_flux_d_mean_en(0, 0, 0),
    _d_v_thermal_d_em(0),
    _d_em_flux_d_em(0, 0, 0),
    _d_ion_flux_d_ip(0, 0, 0),
    _d_em_flux_d_ip(0, 0, 0),
    _d_ion_flux_d_potential_ion(0, 0, 0),
    _d_em_flux_d_potential_ion(0, 0, 0),
    _potential_units(getParam<std::string>("potential_units"))

{
  if (_potential_units.compare("V") == 0)
    _voltage_scaling = 1.;
  else if (_potential_units.compare("kV") == 0)
    _voltage_scaling = 1000;

  _num_ions = coupledComponents("ip");

  _ip.resize(_num_ions);
  _ip_var.resize(_num_ions);
  _muip.resize(_num_ions);
  _sgnip.resize(_num_ions);
  _ion_id.resize(_num_ions);
  _potential_ion.resize(_num_ions);
  _potential_ion_id.resize(_num_ions);
  _grad_potential_ion.resize(_num_ions);

  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    _ip_var[i] = getVar("ip", i);
    _ip[i] = &coupledValue("ip", i);
    _muip[i] = &getMaterialProperty<Real>("mu" + (*getVar("ip", i)).name());
    _ion_id[i] = _ip_var[i]->number();
    _sgnip[i] = &getMaterialProperty<Real>("sgn" + (*getVar("ip", i)).name());
    _potential_ion[i] = &coupledValue("potential_ion", i);
    _potential_ion_id[i] = getVar("potential_ion", i)->number();
    _grad_potential_ion[i] = &coupledGradient("potential_ion", i);
  }
}

Real
EconomouDielectricBC::computeQpResidual()
{
  _ion_flux.zero();
  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    if (_normals[_qp] * (*_sgnip[i])[_qp] * -(*_grad_potential_ion[i])[_qp] > 0.0)
    {
      _a = 1.0;
    }
    else
    {
      _a = 0.0;
    }

    _ion_flux += _a * (*_sgnip[i])[_qp] * (*_muip[i])[_qp] * -(*_grad_potential_ion[i])[_qp] *
                 _r_units * std::exp((*_ip[i])[_qp]);
  }

  _v_thermal =
      std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_mean_en[_qp] - _em[_qp]) / (M_PI * _massem[_qp]));

  _em_flux =
      (0.25 * _v_thermal * std::exp(_em[_qp]) * _normals[_qp]) - (_user_se_coeff * _ion_flux);

  return _test[_i][_qp] * _r_units *
         ((_thickness / _epsilon_d) * _e[_qp] * 6.022e23 * (_ion_flux - _em_flux) * _normals[_qp] /
              _voltage_scaling +
          (_thickness / _epsilon_d) * 8.8542e-12 * -_grad_u_dot[_qp] * _r_units * _normals[_qp] -
          _u_dot[_qp]);
}

Real
EconomouDielectricBC::computeQpJacobian()
{
  _d_ion_flux_du.zero();

  // Check if any of the 'potential_ion' variables are the same as _potential.
  // If any are, add the Jacobian contribution.
  _iter_potential = std::find(_potential_ion_id.begin(), _potential_ion_id.end(), _var.number());
  if (_iter_potential != _potential_ion_id.end())
  {
    _ip_index = std::distance(_potential_ion_id.begin(), _iter_potential);
    if (_normals[_qp] * (*_sgnip[_ip_index])[_qp] * -(*_grad_potential_ion[_ip_index])[_qp] > 0.0)
    {
      _a = 1.0;
    }
    else
    {
      _a = 0.0;
    }

    _d_ion_flux_du += (_a * (*_sgnip[_ip_index])[_qp] * (*_muip[_ip_index])[_qp] *
                       -_grad_phi[_j][_qp] * _r_units * std::exp((*_ip[_ip_index])[_qp]));
  }

  return _test[_i][_qp] * _r_units *
         ((_thickness / _epsilon_d) * _e[_qp] * 6.022e23 * _d_ion_flux_du * _normals[_qp] /
              _voltage_scaling +
          (_thickness / _epsilon_d) * 8.854e-12 * _du_dot_du[_qp] * -_grad_phi[_j][_qp] * _r_units *
              _normals[_qp] -
          _du_dot_du[_qp] * _phi[_j][_qp]);
}

Real
EconomouDielectricBC::computeQpOffDiagJacobian(unsigned int jvar)
{
  _iter = std::find(_ion_id.begin(), _ion_id.end(), jvar);
  _iter_potential = std::find(_potential_ion_id.begin(), _potential_ion_id.end(), jvar);
  if (jvar == _mean_en_id)
  {
    _v_thermal = std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_mean_en[_qp] - _em[_qp]) /
                           (M_PI * _massem[_qp]));
    _d_v_thermal_d_mean_en = 0.5 / _v_thermal * 8 * _e[_qp] * 2.0 / 3 *
                             std::exp(_mean_en[_qp] - _em[_qp]) / (M_PI * _massem[_qp]) *
                             _phi[_j][_qp];

    _d_em_flux_d_mean_en = (0.25 * _d_v_thermal_d_mean_en * std::exp(_em[_qp]) * _normals[_qp]);

    return _test[_i][_qp] * _r_units * (_thickness / _epsilon_d) *
           (-_e[_qp] * 6.022e23 * _d_em_flux_d_mean_en) * _normals[_qp] / _voltage_scaling;
  }

  else if (jvar == _em_id)
  {
    _v_thermal = std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_mean_en[_qp] - _em[_qp]) /
                           (M_PI * _massem[_qp]));
    _d_v_thermal_d_em = 0.5 / _v_thermal * 8 * _e[_qp] * 2.0 / 3 *
                        std::exp(_mean_en[_qp] - _em[_qp]) / (M_PI * _massem[_qp]) * -_phi[_j][_qp];

    _d_em_flux_d_em = ((0.25 * _d_v_thermal_d_em * std::exp(_em[_qp]) +
                        0.25 * _v_thermal * std::exp(_em[_qp]) * _phi[_j][_qp]) *
                       _normals[_qp]);

    return _test[_i][_qp] * _r_units * (_thickness / _epsilon_d) *
           (-_e[_qp] * 6.022e23 * _d_em_flux_d_em) * _normals[_qp] / _voltage_scaling;
  }

  else if (_iter != _ion_id.end())
  {
    _ip_index = std::distance(_ion_id.begin(), _iter);
    if (_normals[_qp] * (*_sgnip[_ip_index])[_qp] * -(*_grad_potential_ion[_ip_index])[_qp] > 0.0)
    {
      _a = 1.0;
    }
    else
    {
      _a = 0.0;
    }

    _d_ion_flux_d_ip = (_a * (*_sgnip[_ip_index])[_qp] * (*_muip[_ip_index])[_qp] *
                        -(*_grad_potential_ion[_ip_index])[_qp] * _r_units *
                        std::exp((*_ip[_ip_index])[_qp]) * _phi[_j][_qp]);

    _d_em_flux_d_ip = -_user_se_coeff * _d_ion_flux_d_ip;

    return _test[_i][_qp] * _r_units * (_thickness / _epsilon_d) * _e[_qp] * 6.022e23 *
           (_d_ion_flux_d_ip - _d_em_flux_d_ip) * _normals[_qp] / _voltage_scaling;
  }

  else if (_iter_potential != _potential_ion_id.end())
  {
    _ip_index = std::distance(_potential_ion_id.begin(), _iter_potential);
    if (_normals[_qp] * (*_sgnip[_ip_index])[_qp] * -(*_grad_potential_ion[_ip_index])[_qp] > 0.0)
    {
      _a = 1.0;
    }
    else
    {
      _a = 0.0;
    }

    _d_ion_flux_d_potential_ion =
        (_a * (*_sgnip[_ip_index])[_qp] * (*_muip[_ip_index])[_qp] * -_grad_phi[_j][_qp] *
         _r_units * std::exp((*_ip[_ip_index])[_qp]));

    _d_em_flux_d_potential_ion = -_user_se_coeff * _d_ion_flux_d_potential_ion;

    return _test[_i][_qp] * _r_units * (_thickness / _epsilon_d) * _e[_qp] * 6.022e23 *
           (_d_ion_flux_d_potential_ion - _d_em_flux_d_potential_ion) * _normals[_qp] /
           _voltage_scaling;
  }

  else
    return 0.0;
}
