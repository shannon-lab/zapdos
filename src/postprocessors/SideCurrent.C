//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "SideCurrent.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("ZapdosApp", SideCurrent);

template <>
InputParameters
validParams<SideCurrent>()
{
  InputParameters params = validParams<SideIntegralVariablePostprocessor>();
  // params.addRequiredParam<std::string>("diffusivity", "The name of the diffusivity material
  // property that will be used in the flux computation.");
  params.addRequiredParam<std::string>(
      "mobility",
      "The name of the mobility material property that will be used in the flux computation.");
  params.addRequiredCoupledVar("potential", "The potential that drives the advective flux.");
  params.addRequiredParam<Real>("r", "The reflection coefficient");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addRequiredCoupledVar("mean_en", "Electron energy.");
  params.addRequiredCoupledVar("ions", "All of the ions that can interact with this boundary.");
  params.addRequiredCoupledVar("Arp", "Argon ion density. (temporary)");
  return params;
}

SideCurrent::SideCurrent(const InputParameters & parameters)
  : SideIntegralVariablePostprocessor(parameters),
    _mobility(parameters.get<std::string>("mobility")),
    _mobility_coef(getMaterialProperty<Real>(_mobility)),
    _r_units(1. / getParam<Real>("position_units")),
    _r(getParam<Real>("r")),
    _kb(getMaterialProperty<Real>("k_boltz")),
    _T_heavy(getMaterialProperty<Real>("TArp")),
    _mass(getMaterialProperty<Real>("massArp")),
    _e(getMaterialProperty<Real>("e")),
    _sgn(getMaterialProperty<Real>("sgnArp")),
    _a(0.5),
    _grad_potential(coupledGradient("potential")),
    _mean_en(coupledValue("mean_en")),
    _Arp(coupledValue("Arp")),
    _muArp(getMaterialProperty<Real>("muArp"))
{
  _num_ions = coupledComponents("ions");

  // Resize the vectors to store _num_ions pointers
  _ions.resize(_num_ions);
  _mu_ions.resize(_num_ions);
  _sgn_ions.resize(_num_ions);
  _mass_ions.resize(_num_ions);
  _T_ions.resize(_num_ions);
  _grad_ions.resize(_num_ions);

  for (unsigned int i = 0; i < _ions.size(); ++i)
  {
    _ions[i] = &coupledValue("ions", i);
    _grad_ions[i] = &coupledGradient("ions", i);
    _mu_ions[i] = &getMaterialProperty<Real>("mu" + (*getVar("ions", i)).name());
    _sgn_ions[i] = &getMaterialProperty<Real>("sgn" + (*getVar("ions", i)).name());
    _mass_ions[i] = &getMaterialProperty<Real>("mass" + (*getVar("ions", i)).name());
    _T_ions[i] = &getMaterialProperty<Real>("T" + (*getVar("ions", i)).name());
  }
}

Real
SideCurrent::computeQpIntegral()
{
  // Output units for base case are: mol / (m^2 * s)
  // _v_thermal = std::sqrt(8 * _kb[_qp] * _T_heavy[_qp] / (M_PI * _mass[_qp]));

  if (_normals[_qp] * _sgn[_qp] * -_grad_potential[_qp] > 0.0)
  {
    _a = 1.0;
    _b = 0.0;
  }
  else
  {
    _a = 0.0;
    _b = 1.0;
  }

  _ve_thermal =
      std::sqrt(8 * 1.602e-19 * 2.0 / 3 * std::exp(_mean_en[_qp] - _u[_qp]) / (M_PI * 9.11e-31));

  _ion_flux = 0.0;

  for (unsigned int i = 0; i < _num_ions; ++i)
    _ion_flux += 0.5 *
                     std::sqrt(8 * _kb[_qp] * (*_T_ions[i])[_qp] / (M_PI * (*_mass_ions[i])[_qp])) *
                     std::exp((*_ions[i])[_qp]) +
                 (2 * _a - 1) * (*_sgn_ions[i])[_qp] * (*_mu_ions[i])[_qp] * -_grad_potential[_qp] *
                     _r_units * std::exp((*_ions[i])[_qp]) * _normals[_qp];

  return ((1. - _r) / (1. + _r) * _ion_flux +
          (1. - _r) / (1. + _r) *
              (-(2 * _b - 1) * _mobility_coef[_qp] * -_grad_potential[_qp] * _r_units *
                   std::exp(_u[_qp]) * _normals[_qp] +
               0.5 * _ve_thermal * std::exp(_u[_qp]))) *
         6.022e23 * 1.602e-19 * _r_units;
  /*
  return ((1. - _r) / (1. + _r) * 0.5 * _v_thermal * std::exp(_Arp[_qp]) +
          (1. - _r) / (1. + _r) *
              ((2 * _a - 1) * _sgn[_qp] * _muArp[_qp] * -_grad_potential[_qp] * _r_units *
               std::exp(_Arp[_qp]) * _normals[_qp]) +
          (1. - _r) / (1. + _r) *
              (-(2 * _b - 1) * _mobility_coef[_qp] * -_grad_potential[_qp] * _r_units *
                   std::exp(_u[_qp]) * _normals[_qp] +
               0.5 * _ve_thermal * std::exp(_u[_qp]))) *
         6.022e23 * 1.602e-19 * _r_units;
         */
}
