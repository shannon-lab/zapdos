/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "NeumannCircuitVoltageMoles_KV.h"
#include "Function.h"

template<>
InputParameters validParams<NeumannCircuitVoltageMoles_KV>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addRequiredParam<FunctionName>("function", "The function.");
  params.addRequiredParam<UserObjectName>("data_provider","The name of the UserObject that can provide some data to materials, bcs, etc.");
  params.addRequiredCoupledVar("ip","The ion density.");
  params.addRequiredCoupledVar("em","The log of the electron density.");
  params.addRequiredCoupledVar("mean_en","The log of the product of the mean energy and the electron density.");
  params.addRequiredParam<std::string>("potential_units", "The potential units.");
  params.addRequiredParam<Real>("r", "The reflection coefficient applied to both electrons and ions");

  return params;
}

NeumannCircuitVoltageMoles_KV::NeumannCircuitVoltageMoles_KV(const InputParameters & parameters) :
    IntegratedBC(parameters),
    _V_bat(getFunction("function")),
    _data(getUserObject<ProvideMobility>("data_provider")),
    _ip_var(*getVar("ip",0)),
    _ip(coupledValue("ip")),
    _grad_ip(coupledGradient("ip")),
    _ip_id(coupled("ip")),
    _mean_en(coupledValue("mean_en")),
    _mean_en_id(coupled("mean_en")),
    _em(coupledValue("em")),
    _em_id(coupled("em")),
    _se_coeff(getMaterialProperty<Real>("se_coeff")),
    _muip(getMaterialProperty<Real>("mu"+_ip_var.name())),
    _eps(getMaterialProperty<Real>("eps")),
    _N_A(getMaterialProperty<Real>("N_A")),
    _sgnip(getMaterialProperty<Real>("sgn" + _ip_var.name())),
    _Dip(getMaterialProperty<Real>("diff" + _ip_var.name())),
  _muem(getMaterialProperty<Real>("muem")),
  _d_muem_d_actual_mean_en(getMaterialProperty<Real>("d_muem_d_actual_mean_en")),
  _e(getMaterialProperty<Real>("e")),
  _mem(getMaterialProperty<Real>("mem")),
  _T_heavy(getMaterialProperty<Real>("T_heavy")),
  _kb(getMaterialProperty<Real>("k_boltz")),
  _mass(getMaterialProperty<Real>("mass" + _ip_var.name())),

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
{
  if (_potential_units.compare("V") == 0)
    _voltage_scaling = 1.;
  else if (_potential_units.compare("kV") == 0)
    _voltage_scaling = 1000;
}

Real
NeumannCircuitVoltageMoles_KV::computeQpResidual()
{
  if ( _normals[_qp] * -1.0 * -_grad_u[_qp] > 0.0)
  {
    _a = 1.0;
    _b = 0.;
  }
  else
  {
    _a = 0.0;
    _b = 1.;
  }

  _ion_flux = _sgnip[_qp] * _muip[_qp] * -_grad_u[_qp] * std::exp(_ip[_qp]) - _Dip[_qp] * std::exp(_ip[_qp]) * _grad_ip[_qp];
  _n_gamma = (1. - _a) * _se_coeff[_qp] * _ion_flux * _normals[_qp] / (_muem[_qp] * -_grad_u[_qp] * _normals[_qp]);
  _v_e_th = std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_mean_en[_qp] - _em[_qp]) / (M_PI * _mem[_qp]));
  _v_i_th = std::sqrt(8 * _kb[_qp] * _T_heavy[_qp] / (M_PI * _mass[_qp]));

  return _test[_i][_qp] * _eps[_qp] * (-2. * (1. + _r) * _u[_qp] - 2. * (1. + _r) * _V_bat.value(_t, _q_point[_qp]) + _data.electrode_area() * _data.coulomb_charge() * _data.ballast_resist() / _voltage_scaling * (-1. + _r) * ((-1. + (-1. + _a) * _se_coeff[_qp]) * _N_A[_qp] * std::exp(_ip[_qp]) * _v_i_th + _N_A[_qp] * (std::exp(_em[_qp]) - _n_gamma) * _v_e_th)) / (2. * _data.electrode_area() * _data.coulomb_charge() * ((-1. + 2. * _a) * _muem[_qp] / _voltage_scaling * _N_A[_qp] * (std::exp(_em[_qp]) - _n_gamma) - (-1. + 2. * _b) * (-1. + (-1. + _a) * _se_coeff[_qp]) * _muip[_qp] / _voltage_scaling * _N_A[_qp] * std::exp(_ip[_qp])) * _data.ballast_resist() * (-1. + _r));
}

Real
NeumannCircuitVoltageMoles_KV::computeQpJacobian()
{
  if ( _normals[_qp] * -1.0 * -_grad_u[_qp] > 0.0)
  {
    _a = 1.0;
    _b = 0.;
  }
  else
  {
    _a = 0.0;
    _b = 1.;
  }

  _ion_flux = _sgnip[_qp] * _muip[_qp] * -_grad_u[_qp] * std::exp(_ip[_qp]) - _Dip[_qp] * std::exp(_ip[_qp]) * _grad_ip[_qp];
  _d_ion_flux_d_u = _sgnip[_qp] * _muip[_qp] * -_grad_phi[_j][_qp] * std::exp(_ip[_qp]);
  _n_gamma = (1. - _a) * _se_coeff[_qp] * _ion_flux * _normals[_qp] / (_muem[_qp] * -_grad_u[_qp] * _normals[_qp]);
  _d_n_gamma_d_u = (1. - _a) * _se_coeff[_qp] / _muem[_qp] * (_d_ion_flux_d_u * _normals[_qp] / (-_grad_u[_qp] * _normals[_qp]) - _ion_flux * _normals[_qp] / (std::pow(-_grad_u[_qp] * _normals[_qp], 2.)) * -_grad_phi[_j][_qp] * _normals[_qp]);
  _v_e_th = std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_mean_en[_qp] - _em[_qp]) / (M_PI * _mem[_qp]));
  _v_i_th = std::sqrt(8 * _kb[_qp] * _T_heavy[_qp] / (M_PI * _mass[_qp]));

  _numerator = (-2. * (1. + _r) * _u[_qp] - 2. * (1. + _r) * _V_bat.value(_t, _q_point[_qp]) + _data.electrode_area() * _data.coulomb_charge() * _data.ballast_resist() / _voltage_scaling * (-1. + _r) * ((-1. + (-1. + _a) * _se_coeff[_qp]) * _N_A[_qp] * std::exp(_ip[_qp]) * _v_i_th + _N_A[_qp] * (std::exp(_em[_qp]) - _n_gamma) * _v_e_th));
  _denominator = (2. * _data.electrode_area() * _data.coulomb_charge() * ((-1. + 2. * _a) * _muem[_qp] / _voltage_scaling * _N_A[_qp] * (std::exp(_em[_qp]) - _n_gamma) - (-1. + 2. * _b) * (-1. + (-1. + _a) * _se_coeff[_qp]) * _muip[_qp] / _voltage_scaling * _N_A[_qp] * std::exp(_ip[_qp])) * _data.ballast_resist() * (-1. + _r));

  _d_denominator_d_u = 2. * _data.ballast_resist() * _e[_qp] * _data.electrode_area() * (-1. + _r) * (-1. + 2. * _a) * _muem[_qp] / _voltage_scaling * _N_A[_qp] * -_d_n_gamma_d_u;
  _d_numerator_d_u = -2. * (1. + _r) * _phi[_j][_qp] + _data.electrode_area() * _e[_qp] * _data.ballast_resist() / _voltage_scaling* (-1. + _r) * _N_A[_qp] * -_d_n_gamma_d_u * _v_e_th;

  return _test[_i][_qp] * _eps[_qp] * (_d_numerator_d_u * _denominator - _d_denominator_d_u * _numerator) / (_denominator * _denominator);
}

Real
NeumannCircuitVoltageMoles_KV::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _ip_id)
  {
    if ( _normals[_qp] * -1.0 * -_grad_u[_qp] > 0.0)
    {
      _a = 1.0;
      _b = 0.;
    }
    else
    {
      _a = 0.0;
      _b = 1.;
    }

    _ion_flux = _sgnip[_qp] * _muip[_qp] * -_grad_u[_qp] * std::exp(_ip[_qp]) - _Dip[_qp] * std::exp(_ip[_qp]) * _grad_ip[_qp];
    _d_ion_flux_d_ip = _sgnip[_qp] * _muip[_qp] * -_grad_u[_qp] * std::exp(_ip[_qp]) * _phi[_j][_qp] - _Dip[_qp] * (std::exp(_ip[_qp]) * _phi[_j][_qp] * _grad_ip[_qp] + std::exp(_ip[_qp]) * _grad_phi[_j][_qp]);
    _n_gamma = (1. - _a) * _se_coeff[_qp] * _ion_flux * _normals[_qp] / (_muem[_qp] * -_grad_u[_qp] * _normals[_qp]);
    _d_n_gamma_d_ip  = (1. - _a) * _se_coeff[_qp] * _d_ion_flux_d_ip * _normals[_qp] / (_muem[_qp] * -_grad_u[_qp] * _normals[_qp]);
    _v_e_th = std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_mean_en[_qp] - _em[_qp]) / (M_PI * _mem[_qp]));
    _v_i_th = std::sqrt(8 * _kb[_qp] * _T_heavy[_qp] / (M_PI * _mass[_qp]));

    _numerator = (-2. * (1. + _r) * _u[_qp] - 2. * (1. + _r) * _V_bat.value(_t, _q_point[_qp]) + _data.electrode_area() * _data.coulomb_charge() * _data.ballast_resist() / _voltage_scaling * (-1. + _r) * ((-1. + (-1. + _a) * _se_coeff[_qp]) * _N_A[_qp] * std::exp(_ip[_qp]) * _v_i_th + _N_A[_qp] * (std::exp(_em[_qp]) - _n_gamma) * _v_e_th));
    _denominator = (2. * _data.electrode_area() * _data.coulomb_charge() * ((-1. + 2. * _a) * _muem[_qp] / _voltage_scaling * _N_A[_qp] * (std::exp(_em[_qp]) - _n_gamma) - (-1. + 2. * _b) * (-1. + (-1. + _a) * _se_coeff[_qp]) * _muip[_qp] / _voltage_scaling * _N_A[_qp] * std::exp(_ip[_qp])) * _data.ballast_resist() * (-1. + _r));

    _d_numerator_d_ip = _data.electrode_area() * _data.coulomb_charge() * _data.ballast_resist() / _voltage_scaling * (-1. + _r) * ((-1. + (-1. + _a) * _se_coeff[_qp]) * _N_A[_qp] * std::exp(_ip[_qp]) * _phi[_j][_qp] * _v_i_th + _N_A[_qp] * (-_d_n_gamma_d_ip) * _v_e_th);
    _d_denominator_d_ip = (2. * _data.electrode_area() * _data.coulomb_charge() * ((-1. + 2. * _a) * _muem[_qp] / _voltage_scaling * _N_A[_qp] * (-_d_n_gamma_d_ip) - (-1. + 2. * _b) * (-1. + (-1. + _a) * _se_coeff[_qp]) * _muip[_qp] / _voltage_scaling * _N_A[_qp] * std::exp(_ip[_qp]) * _phi[_j][_qp]) * _data.ballast_resist() * (-1. + _r));

    return _test[_i][_qp] * _eps[_qp] * (_d_numerator_d_ip * _denominator - _d_denominator_d_ip * _numerator) / (_denominator * _denominator);
  }

  else if (jvar == _em_id)
  {
    if ( _normals[_qp] * -1.0 * -_grad_u[_qp] > 0.0)
    {
      _a = 1.0;
      _b = 0.;
    }
    else
    {
      _a = 0.0;
      _b = 1.;
    }

    _ion_flux = _sgnip[_qp] * _muip[_qp] * -_grad_u[_qp] * std::exp(_ip[_qp]) - _Dip[_qp] * std::exp(_ip[_qp]) * _grad_ip[_qp];
    _n_gamma = (1. - _a) * _se_coeff[_qp] * _ion_flux * _normals[_qp] / (_muem[_qp] * -_grad_u[_qp] * _normals[_qp]);
    _actual_mean_en = std::exp(_mean_en[_qp] - _em[_qp]);
    _d_n_gamma_d_em = -1. * (1. - _a) * _se_coeff[_qp] * _ion_flux * _normals[_qp] / (std::pow(_muem[_qp] * -_grad_u[_qp] * _normals[_qp], 2.)) * -_grad_u[_qp] * _normals[_qp] * _d_muem_d_actual_mean_en[_qp] * _actual_mean_en * -_phi[_j][_qp];
    _v_e_th = std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_mean_en[_qp] - _em[_qp]) / (M_PI * _mem[_qp]));
    _d_v_e_th_d_em = 0.5 / _v_e_th * 8 * _e[_qp] * 2.0 / 3 * _actual_mean_en / (M_PI * _mem[_qp]) * -_phi[_j][_qp];
    _v_i_th = std::sqrt(8 * _kb[_qp] * _T_heavy[_qp] / (M_PI * _mass[_qp]));

    _numerator = (-2. * (1. + _r) * _u[_qp] - 2. * (1. + _r) * _V_bat.value(_t, _q_point[_qp]) + _data.electrode_area() * _data.coulomb_charge() * _data.ballast_resist() / _voltage_scaling * (-1. + _r) * ((-1. + (-1. + _a) * _se_coeff[_qp]) * _N_A[_qp] * std::exp(_ip[_qp]) * _v_i_th + _N_A[_qp] * (std::exp(_em[_qp]) - _n_gamma) * _v_e_th));
    _denominator = (2. * _data.electrode_area() * _data.coulomb_charge() * ((-1. + 2. * _a) * _muem[_qp] / _voltage_scaling * _N_A[_qp] * (std::exp(_em[_qp]) - _n_gamma) - (-1. + 2. * _b) * (-1. + (-1. + _a) * _se_coeff[_qp]) * _muip[_qp] / _voltage_scaling * _N_A[_qp] * std::exp(_ip[_qp])) * _data.ballast_resist() * (-1. + _r));

    _d_numerator_d_em = _data.electrode_area() * _data.coulomb_charge() * _data.ballast_resist() / _voltage_scaling * (-1. + _r) * (_N_A[_qp] * (std::exp(_em[_qp]) - _n_gamma) * _d_v_e_th_d_em + _N_A[_qp] * (std::exp(_em[_qp]) * _phi[_j][_qp] - _d_n_gamma_d_em) * _v_e_th);
    _d_denominator_d_em = (2. * _data.electrode_area() * _data.coulomb_charge() * (((-1. + 2. * _a) * _d_muem_d_actual_mean_en[_qp] * _actual_mean_en * -_phi[_j][_qp] / _voltage_scaling * _N_A[_qp] * (std::exp(_em[_qp]) - _n_gamma)) + ((-1. + 2. * _a) * _muem[_qp] / _voltage_scaling * _N_A[_qp] * (std::exp(_em[_qp]) * _phi[_j][_qp] - _d_n_gamma_d_em))) * _data.ballast_resist() * (-1. + _r));

    return _test[_i][_qp] * _eps[_qp] * (_d_numerator_d_em * _denominator - _d_denominator_d_em * _numerator) / (_denominator * _denominator);
  }

  else if (jvar == _mean_en_id)
  {
    if ( _normals[_qp] * -1.0 * -_grad_u[_qp] > 0.0)
    {
      _a = 1.0;
      _b = 0.;
    }
    else
    {
      _a = 0.0;
      _b = 1.;
    }

    _ion_flux = _sgnip[_qp] * _muip[_qp] * -_grad_u[_qp] * std::exp(_ip[_qp]) - _Dip[_qp] * std::exp(_ip[_qp]) * _grad_ip[_qp];
    _n_gamma = (1. - _a) * _se_coeff[_qp] * _ion_flux * _normals[_qp] / (_muem[_qp] * -_grad_u[_qp] * _normals[_qp]);
    _actual_mean_en = std::exp(_mean_en[_qp] - _em[_qp]);
    _d_n_gamma_d_mean_en = -1. * (1. - _a) * _se_coeff[_qp] * _ion_flux * _normals[_qp] / (std::pow(_muem[_qp] * -_grad_u[_qp] * _normals[_qp], 2.)) * -_grad_u[_qp] * _normals[_qp] * _d_muem_d_actual_mean_en[_qp] * _actual_mean_en * _phi[_j][_qp];
    _v_e_th = std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_mean_en[_qp] - _em[_qp]) / (M_PI * _mem[_qp]));
    _d_v_e_th_d_mean_en = 0.5 / _v_e_th * 8 * _e[_qp] * 2.0 / 3 * _actual_mean_en / (M_PI * _mem[_qp]) * _phi[_j][_qp];
    _v_i_th = std::sqrt(8 * _kb[_qp] * _T_heavy[_qp] / (M_PI * _mass[_qp]));

    _numerator = (-2. * (1. + _r) * _u[_qp] - 2. * (1. + _r) * _V_bat.value(_t, _q_point[_qp]) + _data.electrode_area() * _data.coulomb_charge() * _data.ballast_resist() / _voltage_scaling * (-1. + _r) * ((-1. + (-1. + _a) * _se_coeff[_qp]) * _N_A[_qp] * std::exp(_ip[_qp]) * _v_i_th + _N_A[_qp] * (std::exp(_em[_qp]) - _n_gamma) * _v_e_th));
    _denominator = (2. * _data.electrode_area() * _data.coulomb_charge() * ((-1. + 2. * _a) * _muem[_qp] / _voltage_scaling * _N_A[_qp] * (std::exp(_em[_qp]) - _n_gamma) - (-1. + 2. * _b) * (-1. + (-1. + _a) * _se_coeff[_qp]) * _muip[_qp] / _voltage_scaling * _N_A[_qp] * std::exp(_ip[_qp])) * _data.ballast_resist() * (-1. + _r));

    _d_numerator_d_mean_en = _data.electrode_area() * _data.coulomb_charge() * _data.ballast_resist() / _voltage_scaling * (-1. + _r) * (_N_A[_qp] * (std::exp(_em[_qp]) - _n_gamma) * _d_v_e_th_d_mean_en + _N_A[_qp] * (-_d_n_gamma_d_mean_en) * _v_e_th);
    _d_denominator_d_mean_en = (2. * _data.electrode_area() * _data.coulomb_charge() * (((-1. + 2. * _a) * _d_muem_d_actual_mean_en[_qp] * _actual_mean_en * _phi[_j][_qp] / _voltage_scaling * _N_A[_qp] * (std::exp(_em[_qp]) - _n_gamma)) + ((-1. + 2. * _a) * _muem[_qp] / _voltage_scaling * _N_A[_qp] * (-_d_n_gamma_d_mean_en))) * _data.ballast_resist() * (-1. + _r));

    return _test[_i][_qp] * _eps[_qp] * (_d_numerator_d_mean_en * _denominator - _d_denominator_d_mean_en * _numerator) / (_denominator * _denominator);
  }

  else
    return 0.0;
}
