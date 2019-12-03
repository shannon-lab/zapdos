//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "NeumannCircuitVoltageMoles_KV.h"

// MOOSE includes
#include "MooseVariable.h"
#include "Function.h"

registerMooseObject("ZapdosApp", NeumannCircuitVoltageMoles_KV);

template <>
InputParameters
validParams<NeumannCircuitVoltageMoles_KV>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addRequiredParam<FunctionName>("function", "The function.");
  params.addRequiredParam<UserObjectName>(
      "data_provider",
      "The name of the UserObject that can provide some data to materials, bcs, etc.");
  params.addRequiredCoupledVar("ip", "The ion density.");
  params.addRequiredCoupledVar("em", "The log of the electron density.");
  params.addRequiredCoupledVar(
      "mean_en", "The log of the product of the mean energy and the electron density.");
  params.addRequiredParam<std::string>("potential_units", "The potential units.");
  params.addRequiredParam<Real>("r",
                                "The reflection coefficient applied to both electrons and ions");
  params.addRequiredParam<Real>("position_units", "Units of position.");

  return params;
}

NeumannCircuitVoltageMoles_KV::NeumannCircuitVoltageMoles_KV(const InputParameters & parameters)
  : IntegratedBC(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _V_bat(getFunction("function")),
    _data(getUserObject<ProvideMobility>("data_provider")),
    _mean_en(coupledValue("mean_en")),
    _mean_en_id(coupled("mean_en")),
    _em(coupledValue("em")),
    _em_id(coupled("em")),
    _se_coeff(getMaterialProperty<Real>("se_coeff")),
    _eps(getMaterialProperty<Real>("eps")),
    _N_A(getMaterialProperty<Real>("N_A")),
    _muem(getMaterialProperty<Real>("muem")),
    _d_muem_d_actual_mean_en(getMaterialProperty<Real>("d_muem_d_actual_mean_en")),
    _e(getMaterialProperty<Real>("e")),
    _massem(getMaterialProperty<Real>("massem")),
    _kb(getMaterialProperty<Real>("k_boltz")),

    _potential_units(getParam<std::string>("potential_units")),
    _r(getParam<Real>("r")),

    _ion_flux(0, 0, 0),
    _n_gamma(0),
    _actual_mean_en(0),
    _v_e_th(0),
    _d_v_e_th_d_em(0),
    _d_v_e_th_d_mean_en(0),
    _v_i_th(0),
    _a(0),
    _b(0),
    _d_ion_flux_d_u(0, 0, 0),
    _d_ion_flux_d_ip(0, 0, 0),
    _d_n_gamma_d_u(0),
    _d_n_gamma_d_ip(0),
    _d_n_gamma_d_em(0),
    _d_n_gamma_d_mean_en(0),
    _numerator(0),
    _denominator(0),
    _d_numerator_d_u(0),
    _d_denominator_d_u(0),
    _d_numerator_d_ip(0),
    _d_denominator_d_ip(0),
    _d_numerator_d_em(0),
    _d_denominator_d_em(0),
    _d_numerator_d_mean_en(0),
    _d_denominator_d_mean_en(0)
//_ion_id(coupled("ions"))
{
  if (_potential_units.compare("V") == 0)
    _voltage_scaling = 1.;
  else if (_potential_units.compare("kV") == 0)
    _voltage_scaling = 1000;

  // First we need to initialize all of the ion densities and material properties.
  // Find the number of ions coupled into this BC:
  _num_ions = coupledComponents("ip");

  // Resize the vectors to store _num_ions values:
  _ip.resize(_num_ions);
  _grad_ip.resize(_num_ions);
  _T_heavy.resize(_num_ions);
  _ip_var.resize(_num_ions);
  _ion_id.resize(_num_ions);
  _muip.resize(_num_ions);
  _Dip.resize(_num_ions);
  _sgnip.resize(_num_ions);
  _mass.resize(_num_ions);

  // Retrieve the values for each ion and store in the relevant vectors.
  // Note that these need to be dereferenced to get the values inside the
  // main body of the code.
  // e.g. instead of "_ip[_qp]" it would be "(*_ip[i])[_qp]", where "i"
  // refers to a single ion species.
  for (unsigned int i = 0; i < _ip.size(); ++i)
  {
    _ip_var[i] = getVar("ip", i);
    _ip[i] = &coupledValue("ip", i);
    _grad_ip[i] = &coupledGradient("ip", i);
    _T_heavy[i] = &getMaterialProperty<Real>("T" + (*getVar("ip", i)).name());
    _ion_id[i] = _ip_var[i]->number();
    _muip[i] = &getMaterialProperty<Real>("mu" + (*getVar("ip", i)).name());
    _Dip[i] = &getMaterialProperty<Real>("diff" + (*getVar("ip", i)).name());
    _sgnip[i] = &getMaterialProperty<Real>("sgn" + (*getVar("ip", i)).name());
    _mass[i] = &getMaterialProperty<Real>("mass" + (*getVar("ip", i)).name());
  }
}

Real
NeumannCircuitVoltageMoles_KV::computeQpResidual()
{
  if (_normals[_qp] * -1.0 * -_grad_u[_qp] > 0.0)
  {
    _a = 1.0;
    _b = 0.;
  }
  else
  {
    _a = 0.0;
    _b = 1.;
  }

  _ion_flux.zero();
  _n_gamma = 0;
  _secondary_ion = 0;
  _ion_drift = 0;
  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    _ion_flux +=
        (*_sgnip[i])[_qp] * (*_muip[i])[_qp] * -_grad_u[_qp] * _r_units * std::exp((*_ip[i])[_qp]) -
        (*_Dip[i])[_qp] * std::exp((*_ip[i])[_qp]) * (*_grad_ip[i])[_qp] * _r_units;

    _secondary_ion += std::exp((*_ip[i])[_qp]) * (*_muip[i])[_qp];

    _ion_drift += std::sqrt(8 * _kb[_qp] * (*_T_heavy[i])[_qp] / (M_PI * (*_mass[i])[_qp])) *
                  std::exp((*_ip[i])[_qp]);
  }
  _n_gamma = (1. - _a) * _se_coeff[_qp] * _ion_flux * _normals[_qp] /
             (_muem[_qp] * -_grad_u[_qp] * _r_units * _normals[_qp]);

  _v_e_th = std::sqrt(8 * _data.coulomb_charge() * 2.0 / 3 * std::exp(_mean_en[_qp] - _em[_qp]) /
                      (M_PI * _massem[_qp]));

  return _test[_i][_qp] * _r_units * _eps[_qp] *
         (-2. * (1. + _r) * _u[_qp] - 2. * (1. + _r) * _V_bat.value(_t, _q_point[_qp]) +
          _data.electrode_area() * _data.coulomb_charge() * _data.ballast_resist() /
              _voltage_scaling * (-1. + _r) *
              ((-1. + (-1. + _a) * _se_coeff[_qp]) * _N_A[_qp] * _ion_drift +
               _N_A[_qp] * (std::exp(_em[_qp]) - _n_gamma) * _v_e_th)) /
         (2. * _data.electrode_area() * _data.coulomb_charge() *
          ((-1. + 2. * _a) * _muem[_qp] / _voltage_scaling * _N_A[_qp] *
               (std::exp(_em[_qp]) - _n_gamma) -
           (-1. + 2. * _b) * (-1. + (-1. + _a) * _se_coeff[_qp]) * _secondary_ion /
               _voltage_scaling * _N_A[_qp]) *
          _data.ballast_resist() * (-1. + _r));
}

Real
NeumannCircuitVoltageMoles_KV::computeQpJacobian()
{
  if (_normals[_qp] * -1.0 * -_grad_u[_qp] > 0.0)
  {
    _a = 1.0;
    _b = 0.;
  }
  else
  {
    _a = 0.0;
    _b = 1.;
  }

  // Reset the terms to zero to prevent double counting
  _d_ion_flux_d_u.zero();
  _ion_flux.zero();
  _secondary_ion = 0;
  _ion_drift = 0;

  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    _ion_flux +=
        (*_sgnip[i])[_qp] * (*_muip[i])[_qp] * -_grad_u[_qp] * _r_units * std::exp((*_ip[i])[_qp]) -
        (*_Dip[i])[_qp] * std::exp((*_ip[i])[_qp]) * (*_grad_ip[i])[_qp] * _r_units;

    _d_ion_flux_d_u += (*_sgnip[i])[_qp] * (*_muip[i])[_qp] * -_grad_phi[_j][_qp] * _r_units *
                       std::exp((*_ip[i])[_qp]);

    _secondary_ion += std::exp((*_ip[i])[_qp]) * (*_muip[i])[_qp];

    _ion_drift += std::sqrt(8 * _kb[_qp] * (*_T_heavy[i])[_qp] / (M_PI * (*_mass[i])[_qp])) *
                  std::exp((*_ip[i])[_qp]);
  }
  _n_gamma = (1. - _a) * _se_coeff[_qp] * _ion_flux * _normals[_qp] /
             (_muem[_qp] * -_grad_u[_qp] * _r_units * _normals[_qp]);

  _d_n_gamma_d_u =
      (1. - _a) * _se_coeff[_qp] / _muem[_qp] *
      (_d_ion_flux_d_u * _normals[_qp] / (-_grad_u[_qp] * _r_units * _normals[_qp]) -
       _ion_flux * _normals[_qp] / (std::pow(-_grad_u[_qp] * _r_units * _normals[_qp], 2.)) *
           -_grad_phi[_j][_qp] * _r_units * _normals[_qp]);

  _v_e_th = std::sqrt(8 * _data.coulomb_charge() * 2.0 / 3 * std::exp(_mean_en[_qp] - _em[_qp]) /
                      (M_PI * _massem[_qp]));

  _numerator = (-2. * (1. + _r) * _u[_qp] - 2. * (1. + _r) * _V_bat.value(_t, _q_point[_qp]) +
                _data.electrode_area() * _data.coulomb_charge() * _data.ballast_resist() /
                    _voltage_scaling * (-1. + _r) *
                    ((-1. + (-1. + _a) * _se_coeff[_qp]) * _N_A[_qp] * _ion_drift +
                     _N_A[_qp] * (std::exp(_em[_qp]) - _n_gamma) * _v_e_th));
  _denominator = (2. * _data.electrode_area() * _data.coulomb_charge() *
                  ((-1. + 2. * _a) * _muem[_qp] / _voltage_scaling * _N_A[_qp] *
                       (std::exp(_em[_qp]) - _n_gamma) -
                   (-1. + 2. * _b) * (-1. + (-1. + _a) * _se_coeff[_qp]) * _secondary_ion /
                       _voltage_scaling * _N_A[_qp]) *
                  _data.ballast_resist() * (-1. + _r));

  _d_denominator_d_u = 2. * _data.ballast_resist() * _data.coulomb_charge() *
                       _data.electrode_area() * (-1. + _r) * (-1. + 2. * _a) * _muem[_qp] /
                       _voltage_scaling * _N_A[_qp] * -_d_n_gamma_d_u;
  _d_numerator_d_u = -2. * (1. + _r) * _phi[_j][_qp] +
                     _data.electrode_area() * _data.coulomb_charge() * _data.ballast_resist() /
                         _voltage_scaling * (-1. + _r) * _N_A[_qp] * -_d_n_gamma_d_u * _v_e_th;

  return _test[_i][_qp] * _r_units * _eps[_qp] *
         (_d_numerator_d_u * _denominator - _d_denominator_d_u * _numerator) /
         (_denominator * _denominator);
}

Real
NeumannCircuitVoltageMoles_KV::computeQpOffDiagJacobian(unsigned int jvar)
{
  // std::find is relatively fast and has a complexity of O(n) (where n = _num_ions). Since the
  // number of coupled ions is usually small (maybe up to 10-20 in complex simulations) it should
  // not be too inefficient to run this, but std::binary_search is a possible alternative at
  // O(log(n)) (note that the _ion_id vector must be sorted for binary_search to work. This needs to
  // be done only once at runtime so it would not incur a significant cost to the simulation).
  _iter = std::find(_ion_id.begin(), _ion_id.end(), jvar);
  if (_iter != _ion_id.end())
  {
    // _ip_index is the index of the ion vectors (_sgn_ions, _mu_ions, _ions, etc.) where
    // _ion_id[_ip_index] == jvar. The residual derivative terms will only be applied to
    // the ion associated with this index.
    _ip_index = std::distance(_ion_id.begin(), _iter);
    if (_normals[_qp] * -1.0 * -_grad_u[_qp] > 0.0)
    {
      _a = 1.0;
      _b = 0.;
    }
    else
    {
      _a = 0.0;
      _b = 1.;
    }

    // Reset the terms to zero to prevent double counting
    _ion_flux.zero();
    _secondary_ion = 0;
    _ion_drift = 0;
    for (unsigned int i = 0; i < _num_ions; ++i)
    {
      _ion_flux += (*_sgnip[i])[_qp] * (*_muip[i])[_qp] * -_grad_u[_qp] * _r_units *
                       std::exp((*_ip[i])[_qp]) -
                   (*_Dip[i])[_qp] * std::exp((*_ip[i])[_qp]) * (*_grad_ip[i])[_qp] * _r_units;

      _secondary_ion += std::exp((*_ip[i])[_qp]) * (*_muip[i])[_qp];

      _ion_drift += std::sqrt(8 * _kb[_qp] * (*_T_heavy[i])[_qp] / (M_PI * (*_mass[i])[_qp])) *
                    std::exp((*_ip[i])[_qp]);
    }
    _n_gamma = (1. - _a) * _se_coeff[_qp] * _ion_flux * _normals[_qp] /
               (_muem[_qp] * -_grad_u[_qp] * _r_units * _normals[_qp]);

    _d_ion_flux_d_ip = (*_sgnip[_ip_index])[_qp] * (*_muip[_ip_index])[_qp] * -_grad_u[_qp] *
                           _r_units * std::exp((*_ip[_ip_index])[_qp]) * _phi[_j][_qp] -
                       (*_Dip[_ip_index])[_qp] *
                           (std::exp((*_ip[_ip_index])[_qp]) * _phi[_j][_qp] *
                                (*_grad_ip[_ip_index])[_qp] * _r_units +
                            std::exp((*_ip[_ip_index])[_qp]) * _grad_phi[_j][_qp] * _r_units);

    _d_n_gamma_d_ip = (1. - _a) * _se_coeff[_qp] * _d_ion_flux_d_ip * _normals[_qp] /
                      (_muem[_qp] * -_grad_u[_qp] * _r_units * _normals[_qp]);

    _v_e_th = std::sqrt(8 * _data.coulomb_charge() * 2.0 / 3 * std::exp(_mean_en[_qp] - _em[_qp]) /
                        (M_PI * _massem[_qp]));

    _numerator = (-2. * (1. + _r) * _u[_qp] - 2. * (1. + _r) * _V_bat.value(_t, _q_point[_qp]) +
                  _data.electrode_area() * _data.coulomb_charge() * _data.ballast_resist() /
                      _voltage_scaling * (-1. + _r) *
                      ((-1. + (-1. + _a) * _se_coeff[_qp]) * _N_A[_qp] * _ion_drift +
                       _N_A[_qp] * (std::exp(_em[_qp]) - _n_gamma) * _v_e_th));
    _denominator = (2. * _data.electrode_area() * _data.coulomb_charge() *
                    ((-1. + 2. * _a) * _muem[_qp] / _voltage_scaling * _N_A[_qp] *
                         (std::exp(_em[_qp]) - _n_gamma) -
                     (-1. + 2. * _b) * (-1. + (-1. + _a) * _se_coeff[_qp]) * _secondary_ion /
                         _voltage_scaling * _N_A[_qp]) *
                    _data.ballast_resist() * (-1. + _r));

    _d_numerator_d_ip = _data.electrode_area() * _data.coulomb_charge() * _data.ballast_resist() /
                        _voltage_scaling * (-1. + _r) *
                        ((-1. + (-1. + _a) * _se_coeff[_qp]) * _N_A[_qp] *
                             (std::sqrt(8 * _kb[_qp] * (*_T_heavy[_ip_index])[_qp] /
                                        (M_PI * (*_mass[_ip_index])[_qp])) *
                              std::exp((*_ip[_ip_index])[_qp])) *
                             _phi[_j][_qp] +
                         _N_A[_qp] * (-_d_n_gamma_d_ip) * _v_e_th);
    _d_denominator_d_ip =
        (2. * _data.electrode_area() * _data.coulomb_charge() *
         ((-1. + 2. * _a) * _muem[_qp] / _voltage_scaling * _N_A[_qp] * (-_d_n_gamma_d_ip) -
          (-1. + 2. * _b) * (-1. + (-1. + _a) * _se_coeff[_qp]) * (*_muip[_ip_index])[_qp] /
              _voltage_scaling * _N_A[_qp] * std::exp((*_ip[_ip_index])[_qp]) * _phi[_j][_qp]) *
         _data.ballast_resist() * (-1. + _r));

    return _test[_i][_qp] * _r_units * _eps[_qp] *
           (_d_numerator_d_ip * _denominator - _d_denominator_d_ip * _numerator) /
           (_denominator * _denominator);
  }
  else if (jvar == _em_id)
  {
    if (_normals[_qp] * -1.0 * -_grad_u[_qp] > 0.0)
    {
      _a = 1.0;
      _b = 0.;
    }
    else
    {
      _a = 0.0;
      _b = 1.;
    }
    _ion_flux.zero();
    _n_gamma = 0;
    _secondary_ion = 0;
    _ion_drift = 0;
    for (unsigned int i = 0; i < _num_ions; ++i)
    {
      _ion_flux += (*_sgnip[i])[_qp] * (*_muip[i])[_qp] * -_grad_u[_qp] * _r_units *
                       std::exp((*_ip[i])[_qp]) -
                   (*_Dip[i])[_qp] * std::exp((*_ip[i])[_qp]) * (*_grad_ip[i])[_qp] * _r_units;

      _secondary_ion += std::exp((*_ip[i])[_qp]) * (*_muip[i])[_qp];

      _ion_drift += std::sqrt(8 * _kb[_qp] * (*_T_heavy[i])[_qp] / (M_PI * (*_mass[i])[_qp])) *
                    std::exp((*_ip[i])[_qp]);
    }
    _n_gamma = (1. - _a) * _se_coeff[_qp] * _ion_flux * _normals[_qp] /
               (_muem[_qp] * -_grad_u[_qp] * _r_units * _normals[_qp]);

    _actual_mean_en = std::exp(_mean_en[_qp] - _em[_qp]);

    _d_n_gamma_d_em = -1. * (1. - _a) * _se_coeff[_qp] * _ion_flux * _normals[_qp] /
                      (std::pow(_muem[_qp] * -_grad_u[_qp] * _r_units * _normals[_qp], 2.)) *
                      -_grad_u[_qp] * _r_units * _normals[_qp] * _d_muem_d_actual_mean_en[_qp] *
                      _actual_mean_en * -_phi[_j][_qp];

    _v_e_th = std::sqrt(8 * _data.coulomb_charge() * 2.0 / 3 * std::exp(_mean_en[_qp] - _em[_qp]) /
                        (M_PI * _massem[_qp]));
    _d_v_e_th_d_em = 0.5 / _v_e_th * 8 * _data.coulomb_charge() * 2.0 / 3 * _actual_mean_en /
                     (M_PI * _massem[_qp]) * -_phi[_j][_qp];

    _numerator = (-2. * (1. + _r) * _u[_qp] - 2. * (1. + _r) * _V_bat.value(_t, _q_point[_qp]) +
                  _data.electrode_area() * _data.coulomb_charge() * _data.ballast_resist() /
                      _voltage_scaling * (-1. + _r) *
                      ((-1. + (-1. + _a) * _se_coeff[_qp]) * _N_A[_qp] * _ion_drift +
                       _N_A[_qp] * (std::exp(_em[_qp]) - _n_gamma) * _v_e_th));
    _denominator = (2. * _data.electrode_area() * _data.coulomb_charge() *
                    ((-1. + 2. * _a) * _muem[_qp] / _voltage_scaling * _N_A[_qp] *
                         (std::exp(_em[_qp]) - _n_gamma) -
                     (-1. + 2. * _b) * (-1. + (-1. + _a) * _se_coeff[_qp]) * _secondary_ion /
                         _voltage_scaling * _N_A[_qp]) *
                    _data.ballast_resist() * (-1. + _r));

    _d_numerator_d_em =
        _data.electrode_area() * _data.coulomb_charge() * _data.ballast_resist() /
        _voltage_scaling * (-1. + _r) *
        (_N_A[_qp] * (std::exp(_em[_qp]) - _n_gamma) * _d_v_e_th_d_em +
         _N_A[_qp] * (std::exp(_em[_qp]) * _phi[_j][_qp] - _d_n_gamma_d_em) * _v_e_th);
    _d_denominator_d_em =
        (2. * _data.electrode_area() * _data.coulomb_charge() *
         (((-1. + 2. * _a) * _d_muem_d_actual_mean_en[_qp] * _actual_mean_en * -_phi[_j][_qp] /
           _voltage_scaling * _N_A[_qp] * (std::exp(_em[_qp]) - _n_gamma)) +
          ((-1. + 2. * _a) * _muem[_qp] / _voltage_scaling * _N_A[_qp] *
           (std::exp(_em[_qp]) * _phi[_j][_qp] - _d_n_gamma_d_em))) *
         _data.ballast_resist() * (-1. + _r));

    return _test[_i][_qp] * _r_units * _eps[_qp] *
           (_d_numerator_d_em * _denominator - _d_denominator_d_em * _numerator) /
           (_denominator * _denominator);
  }

  else if (jvar == _mean_en_id)
  {
    if (_normals[_qp] * -1.0 * -_grad_u[_qp] > 0.0)
    {
      _a = 1.0;
      _b = 0.;
    }
    else
    {
      _a = 0.0;
      _b = 1.;
    }
    _ion_flux.zero();
    _n_gamma = 0;
    _secondary_ion = 0;
    _ion_drift = 0;
    for (unsigned int i = 0; i < _num_ions; ++i)
    {
      _ion_flux += (*_sgnip[i])[_qp] * (*_muip[i])[_qp] * -_grad_u[_qp] * _r_units *
                       std::exp((*_ip[i])[_qp]) -
                   (*_Dip[i])[_qp] * std::exp((*_ip[i])[_qp]) * (*_grad_ip[i])[_qp] * _r_units;

      _secondary_ion += std::exp((*_ip[i])[_qp]) * (*_muip[i])[_qp];

      _ion_drift += std::sqrt(8 * _kb[_qp] * (*_T_heavy[i])[_qp] / (M_PI * (*_mass[i])[_qp])) *
                    std::exp((*_ip[i])[_qp]);
    }
    _n_gamma = (1. - _a) * _se_coeff[_qp] * _ion_flux * _normals[_qp] /
               (_muem[_qp] * -_grad_u[_qp] * _r_units * _normals[_qp]);

    _actual_mean_en = std::exp(_mean_en[_qp] - _em[_qp]);
    _d_n_gamma_d_mean_en = -1. * (1. - _a) * _se_coeff[_qp] * _ion_flux * _normals[_qp] /
                           (std::pow(_muem[_qp] * -_grad_u[_qp] * _r_units * _normals[_qp], 2.)) *
                           -_grad_u[_qp] * _r_units * _normals[_qp] *
                           _d_muem_d_actual_mean_en[_qp] * _actual_mean_en * _phi[_j][_qp];
    _v_e_th = std::sqrt(8 * _data.coulomb_charge() * 2.0 / 3 * std::exp(_mean_en[_qp] - _em[_qp]) /
                        (M_PI * _massem[_qp]));
    _d_v_e_th_d_mean_en = 0.5 / _v_e_th * 8 * _data.coulomb_charge() * 2.0 / 3 * _actual_mean_en /
                          (M_PI * _massem[_qp]) * _phi[_j][_qp];

    _numerator = (-2. * (1. + _r) * _u[_qp] - 2. * (1. + _r) * _V_bat.value(_t, _q_point[_qp]) +
                  _data.electrode_area() * _data.coulomb_charge() * _data.ballast_resist() /
                      _voltage_scaling * (-1. + _r) *
                      ((-1. + (-1. + _a) * _se_coeff[_qp]) * _N_A[_qp] * _ion_drift +
                       _N_A[_qp] * (std::exp(_em[_qp]) - _n_gamma) * _v_e_th));
    _denominator = (2. * _data.electrode_area() * _data.coulomb_charge() *
                    ((-1. + 2. * _a) * _muem[_qp] / _voltage_scaling * _N_A[_qp] *
                         (std::exp(_em[_qp]) - _n_gamma) -
                     (-1. + 2. * _b) * (-1. + (-1. + _a) * _se_coeff[_qp]) * _secondary_ion /
                         _voltage_scaling * _N_A[_qp]) *
                    _data.ballast_resist() * (-1. + _r));

    _d_numerator_d_mean_en = _data.electrode_area() * _data.coulomb_charge() *
                             _data.ballast_resist() / _voltage_scaling * (-1. + _r) *
                             (_N_A[_qp] * (std::exp(_em[_qp]) - _n_gamma) * _d_v_e_th_d_mean_en +
                              _N_A[_qp] * (-_d_n_gamma_d_mean_en) * _v_e_th);
    _d_denominator_d_mean_en =
        (2. * _data.electrode_area() * _data.coulomb_charge() *
         (((-1. + 2. * _a) * _d_muem_d_actual_mean_en[_qp] * _actual_mean_en * _phi[_j][_qp] /
           _voltage_scaling * _N_A[_qp] * (std::exp(_em[_qp]) - _n_gamma)) +
          ((-1. + 2. * _a) * _muem[_qp] / _voltage_scaling * _N_A[_qp] * (-_d_n_gamma_d_mean_en))) *
         _data.ballast_resist() * (-1. + _r));

    return _test[_i][_qp] * _r_units * _eps[_qp] *
           (_d_numerator_d_mean_en * _denominator - _d_denominator_d_mean_en * _numerator) /
           (_denominator * _denominator);
  }

  else
    return 0.0;
}
