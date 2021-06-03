//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "HagelaarEnergyAdvectionBC.h"

registerMooseObject("ZapdosApp", HagelaarEnergyAdvectionBC);

InputParameters
HagelaarEnergyAdvectionBC::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  params.addRequiredParam<Real>("r", "The reflection coefficient");
  params.addRequiredCoupledVar("potential", "The electric potential");
  params.addRequiredCoupledVar("ip", "The ion density.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addClassDescription("Kinetic advective electron energy boundary condition"
                             "(Based on DOI:https://doi.org/10.1063/1.2715745)");
  return params;
}

HagelaarEnergyAdvectionBC::HagelaarEnergyAdvectionBC(const InputParameters & parameters)
  : ADIntegratedBC(parameters),

    _r_units(1. / getParam<Real>("position_units")),
    _r(getParam<Real>("r")),

    // Coupled Variables
    _grad_potential(adCoupledGradient("potential")),
    _ip_var(*getVar("ip", 0)),
    _ip(adCoupledValue("ip")),
    _grad_ip(adCoupledGradient("ip")),

    _sgnip(getMaterialProperty<Real>("sgn" + _ip_var.name())),
    _muip(getADMaterialProperty<Real>("mu" + _ip_var.name())),
    _Dip(getADMaterialProperty<Real>("diff" + _ip_var.name())),
    _se_coeff(getMaterialProperty<Real>("se_coeff")),
    _se_energy(getMaterialProperty<Real>("se_energy")),
    _mumean_en(getADMaterialProperty<Real>("mumean_en")),
    _a(0.5),
    _ion_flux(0, 0, 0),
    _v_thermal(0),
    _n_gamma(0)
{
}

ADReal
HagelaarEnergyAdvectionBC::computeQpResidual()
{
  if (_normals[_qp] * -1.0 * -_grad_potential[_qp] > 0.0)
  {
    _a = 1.0;
  }
  else
  {
    _a = 0.0;
  }

  _ion_flux = _sgnip[_qp] * _muip[_qp] * -_grad_potential[_qp] * _r_units * std::exp(_ip[_qp]) -
              _Dip[_qp] * std::exp(_ip[_qp]) * _grad_ip[_qp] * _r_units;

  return _test[_i][_qp] * _r_units / (6. * (_r + 1.)) *
         (10. * _ion_flux * _normals[_qp] * _se_energy[_qp] * _se_coeff[_qp] * (_a - 1.) *
              (_r + 1.) +
          (_r - 1.) * (std::exp(_u[_qp]) - _se_energy[_qp] * _n_gamma) *
              (6. * -_grad_potential[_qp] * _r_units * _normals[_qp] * _mumean_en[_qp] *
                   (2. * _a - 1.) -
               5. * _v_thermal));
}
