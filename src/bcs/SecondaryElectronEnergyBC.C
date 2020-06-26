//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "SecondaryElectronEnergyBC.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("ZapdosApp", SecondaryElectronEnergyBC);

template <>
InputParameters
validParams<SecondaryElectronEnergyBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addRequiredParam<Real>("r", "The reflection coefficient");
  params.addRequiredCoupledVar("potential", "The electric potential");
  params.addRequiredCoupledVar("em", "The electron density.");
  params.addRequiredCoupledVar("ip", "The ion density.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  return params;
}

SecondaryElectronEnergyBC::SecondaryElectronEnergyBC(const InputParameters & parameters)
  : IntegratedBC(parameters),

    _r_units(1. / getParam<Real>("position_units")),
    _r(getParam<Real>("r")),

    // Coupled Variables
    _grad_potential(coupledGradient("potential")),
    _potential_id(coupled("potential")),
    _em(coupledValue("em")),
    _em_id(coupled("em")),

    _muem(getMaterialProperty<Real>("muem")),
    _d_muem_d_actual_mean_en(getMaterialProperty<Real>("d_muem_d_actual_mean_en")),
    _massem(getMaterialProperty<Real>("massem")),
    _e(getMaterialProperty<Real>("e")),
    _se_coeff(getMaterialProperty<Real>("se_coeff")),
    _se_energy(getMaterialProperty<Real>("se_energy")),
    _mumean_en(getMaterialProperty<Real>("mumean_en")),
    _d_mumean_en_d_actual_mean_en(getMaterialProperty<Real>("d_mumean_en_d_actual_mean_en")),
    _a(0.5),
    _b(0.5),
    _kb(getMaterialProperty<Real>("k_boltz")),
    _v_thermal(0),
    _ion_flux(0),
    _n_gamma(0),
    _d_v_thermal_d_u(0),
    _d_v_thermal_d_em(0),
    _d_ion_flux_d_potential(0),
    _d_ion_flux_d_ip(0),
    _d_n_gamma_d_potential(0),
    _d_n_gamma_d_ip(0),
    _d_n_gamma_d_u(0),
    _d_n_gamma_d_em(0),
    _actual_mean_en(0)
{
  _num_ions = coupledComponents("ip");

  // Resize the vectors to store _num_ions values:
  _ip.resize(_num_ions);
  _grad_ip.resize(_num_ions);
  _ip_var.resize(_num_ions);
  _ion_id.resize(_num_ions);
  _muip.resize(_num_ions);
  _Tip.resize(_num_ions);
  _massip.resize(_num_ions);
  _sgnip.resize(_num_ions);

  // Retrieve the values for each ion and store in the relevant vectors.
  // Note that these need to be dereferenced to get the values inside the
  // main body of the code.
  // e.g. instead of "_ip[_qp]" it would be "(*_ip[i])[_qp]", where "i"
  // refers to a single ion species.
  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    _ip_var[i] = getVar("ip", i);
    _ip[i] = &coupledValue("ip", i);
    _grad_ip[i] = &coupledGradient("ip", i);
    _ion_id[i] = _ip_var[i]->number();
    _muip[i] = &getMaterialProperty<Real>("mu" + (*getVar("ip", i)).name());
    _Tip[i] = &getMaterialProperty<Real>("T" + (*getVar("ip", i)).name());
    _massip[i] = &getMaterialProperty<Real>("mass" + (*getVar("ip", i)).name());
    _sgnip[i] = &getMaterialProperty<Real>("sgn" + (*getVar("ip", i)).name());
  }
}

Real
SecondaryElectronEnergyBC::computeQpResidual()
{
  if (_normals[_qp] * -1.0 * -_grad_potential[_qp] > 0.0)
  {
    _a = 1.0;
  }
  else
  {
    _a = 0.0;
  }

  // Ion flux is a vector, but this value is multiplied by _normals[_qp] so
  // it is a scalar quantity.
  _ion_flux = 0.0;
  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    if (_normals[_qp] * (*_sgnip[i])[_qp] * -_grad_potential[_qp] > 0.0)
      _b = 1.0;
    else
      _b = 0.0;

    _ion_flux += std::exp((*_ip[i])[_qp]) *
                 (0.5 * std::sqrt(8 * _kb[_qp] * (*_Tip[i])[_qp] / (M_PI * (*_massip[i])[_qp])) +
                  (2 * _b - 1) * (*_sgnip[i])[_qp] * (*_muip[i])[_qp] * -_grad_potential[_qp] *
                      _r_units * _normals[_qp]);
  }
  _n_gamma = (1. - _a) * _se_coeff[_qp] * _ion_flux /
             (_muem[_qp] * -_grad_potential[_qp] * _r_units * _normals[_qp] +
              std::numeric_limits<double>::epsilon());

  _v_thermal =
      std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_u[_qp] - _em[_qp]) / (M_PI * _massem[_qp]));

  return _test[_i][_qp] * _r_units *
         ((1 - _r) / (1 + _r) * (-5. / 6. * _v_thermal * _n_gamma * _se_energy[_qp]) -
          5. / 3. * (2. / (1 + _r)) * _se_energy[_qp] * (1 - _a) * _se_coeff[_qp] * _ion_flux);
}

Real
SecondaryElectronEnergyBC::computeQpJacobian()
{
  if (_normals[_qp] * -1.0 * -_grad_potential[_qp] > 0.0)
  {
    _a = 1.0;
  }
  else
  {
    _a = 0.0;
  }

  _ion_flux = 0.0;
  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    if (_normals[_qp] * (*_sgnip[i])[_qp] * -_grad_potential[_qp] > 0.0)
      _b = 1.0;
    else
      _b = 0.0;

    _ion_flux += std::exp((*_ip[i])[_qp]) *
                 (0.5 * std::sqrt(8 * _kb[_qp] * (*_Tip[i])[_qp] / (M_PI * (*_massip[i])[_qp])) +
                  (2 * _b - 1) * (*_sgnip[i])[_qp] * (*_muip[i])[_qp] * -_grad_potential[_qp] *
                      _r_units * _normals[_qp]);
  }
  _n_gamma = (1. - _a) * _se_coeff[_qp] * _ion_flux /
             (_muem[_qp] * -_grad_potential[_qp] * _r_units * _normals[_qp] +
              std::numeric_limits<double>::epsilon());

  _actual_mean_en = std::exp(_u[_qp] - _em[_qp]);

  _d_n_gamma_d_u = -1. * (1. - _a) * _se_coeff[_qp] * _ion_flux /
                   (_muem[_qp] * _muem[_qp] * -_grad_potential[_qp] * _r_units * _normals[_qp] +
                    std::numeric_limits<double>::epsilon()) *
                   _d_muem_d_actual_mean_en[_qp] * _actual_mean_en * _phi[_j][_qp];

  _v_thermal =
      std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_u[_qp] - _em[_qp]) / (M_PI * _massem[_qp]));

  _d_v_thermal_d_u = 0.5 / _v_thermal * 8 * _e[_qp] * 2.0 / 3 * _actual_mean_en /
                     (M_PI * _massem[_qp]) * _phi[_j][_qp];

  return _test[_i][_qp] * _r_units * (1 - _r) / (1 + _r) *
         (-5. / 6. * _v_thermal * _d_n_gamma_d_u * _se_energy[_qp] -
          5. / 6. * _d_v_thermal_d_u * _n_gamma * _se_energy[_qp]);
}

Real
SecondaryElectronEnergyBC::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (_normals[_qp] * -1.0 * -_grad_potential[_qp] > 0.0)
    _a = 1.0;
  else
    _a = 0.0;

  _iter = std::find(_ion_id.begin(), _ion_id.end(), jvar);
  if (jvar == _potential_id)
  {
    _ion_flux = 0.0;
    _d_ion_flux_d_potential = 0.0;
    for (unsigned int i = 0; i < _num_ions; ++i)
    {
      if (_normals[_qp] * (*_sgnip[i])[_qp] * -_grad_potential[_qp] > 0.0)
        _b = 1.0;
      else
        _b = 0.0;

      _ion_flux += std::exp((*_ip[i])[_qp]) *
                   (0.5 * std::sqrt(8 * _kb[_qp] * (*_Tip[i])[_qp] / (M_PI * (*_massip[i])[_qp])) +
                    (2 * _b - 1) * (*_sgnip[i])[_qp] * (*_muip[i])[_qp] * -_grad_potential[_qp] *
                        _r_units * _normals[_qp]);

      _d_ion_flux_d_potential += (2 * _b - 1) * (*_sgnip[i])[_qp] * (*_muip[i])[_qp] *
                                 -_grad_phi[_j][_qp] * _r_units * std::exp((*_ip[i])[_qp]) *
                                 _normals[_qp];
    }

    _d_n_gamma_d_potential =
        (1. - _a) * _se_coeff[_qp] / _muem[_qp] *
        (_d_ion_flux_d_potential / (-_grad_potential[_qp] * _r_units * _normals[_qp] +
                                    std::numeric_limits<double>::epsilon()) -
         _ion_flux /
             (std::pow(-_grad_potential[_qp] * _r_units * _normals[_qp], 2.) +
              std::numeric_limits<double>::epsilon()) *
             -_grad_phi[_j][_qp] * _r_units * _normals[_qp]);

    _v_thermal =
        std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_u[_qp] - _em[_qp]) / (M_PI * _massem[_qp]));

    return _test[_i][_qp] * _r_units *
           ((1 - _r) / (1 + _r) * -5 / 6 * _v_thermal * _d_n_gamma_d_potential * _se_energy[_qp] -
            5. / 3. * (2. / (1. + _r)) * _se_energy[_qp] * (1 - _a) * _se_coeff[_qp] *
                _d_ion_flux_d_potential);
  }

  else if (jvar == _em_id)
  {
    _ion_flux = 0.0;
    for (unsigned int i = 0; i < _num_ions; ++i)
    {
      if (_normals[_qp] * (*_sgnip[i])[_qp] * -_grad_potential[_qp] > 0.0)
        _b = 1.0;
      else
        _b = 0.0;

      _ion_flux += std::exp((*_ip[i])[_qp]) *
                   (0.5 * std::sqrt(8 * _kb[_qp] * (*_Tip[i])[_qp] / (M_PI * (*_massip[i])[_qp])) +
                    (2 * _b - 1) * (*_sgnip[i])[_qp] * (*_muip[i])[_qp] * -_grad_potential[_qp] *
                        _r_units * _normals[_qp]);
    }

    _actual_mean_en = std::exp(_u[_qp] - _em[_qp]);

    _v_thermal =
        std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_u[_qp] - _em[_qp]) / (M_PI * _massem[_qp]));

    _d_v_thermal_d_em = 0.5 / _v_thermal * 8 * _e[_qp] * 2.0 / 3 * _actual_mean_en /
                        (M_PI * _massem[_qp]) * -_phi[_j][_qp];

    _n_gamma = (1. - _a) * _se_coeff[_qp] * _ion_flux /
               (_muem[_qp] * -_grad_potential[_qp] * _r_units * _normals[_qp] +
                std::numeric_limits<double>::epsilon());

    _d_n_gamma_d_em = -1. * (1. - _a) * _se_coeff[_qp] * _ion_flux /
                      (_muem[_qp] * _muem[_qp] * -_grad_potential[_qp] * _r_units * _normals[_qp] +
                       std::numeric_limits<double>::epsilon()) *
                      _d_muem_d_actual_mean_en[_qp] * _actual_mean_en * -_phi[_j][_qp];

    return _test[_i][_qp] * _r_units *
           ((1 - _r) / (1 + _r) * (-5. / 6.) *
            (_d_v_thermal_d_em * _n_gamma * _se_energy[_qp] +
             _v_thermal * _d_n_gamma_d_em * _se_energy[_qp]));
  }
  else if (_iter != _ion_id.end())
  {
    _ip_index = std::distance(_ion_id.begin(), _iter);
    if (_normals[_qp] * (*_sgnip[_ip_index])[_qp] * -_grad_potential[_qp] > 0.0)
    {
      _b = 1.0;
    }
    else
    {
      _b = 0.0;
    }

    _v_thermal =
        std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_u[_qp] - _em[_qp]) / (M_PI * _massem[_qp]));

    _d_ion_flux_d_ip = std::exp((*_ip[_ip_index])[_qp]) * _phi[_j][_qp] *
                       (0.5 * std::sqrt(8 * _kb[_qp] * (*_Tip[_ip_index])[_qp] /
                                        (M_PI * (*_massip[_ip_index])[_qp])) +
                        (2 * _b - 1) * (*_sgnip[_ip_index])[_qp] * (*_muip[_ip_index])[_qp] *
                            -_grad_potential[_qp] * _r_units * _normals[_qp]);

    _d_n_gamma_d_ip = (1. - _a) * _se_coeff[_qp] * _d_ion_flux_d_ip /
                      (_muem[_qp] * -_grad_potential[_qp] * _r_units * _normals[_qp] +
                       std::numeric_limits<double>::epsilon());

    return _test[_i][_qp] * _r_units *
           ((1 - _r) / (1 + _r) * -5. / 6. * _v_thermal * _d_n_gamma_d_ip * _se_energy[_qp] -
            5. / 3. * (2. / (1. + _r)) * _se_energy[_qp] * (1 - _a) * _se_coeff[_qp] *
                _d_ion_flux_d_ip);
  }
  else
    return 0.0;
}
