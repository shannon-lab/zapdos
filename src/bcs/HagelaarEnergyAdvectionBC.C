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
  params.addRequiredCoupledVar("ions", "A list of ion densities in log form");
  params.addRequiredParam<std::vector<std::string>>(
      "emission_coeffs",
      "The species-dependent secondary electron emission coefficients for this boundary");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addParam<std::string>("field_property_name",
                               "field_solver_interface_property",
                               "Name of the solver interface material property.");
  params.addRequiredParam<Real>("secondary_electron_energy", "The secondary electron energy in eV");
  params.addClassDescription("Kinetic advective electron energy boundary condition"
                             " (Based on [!cite](hagelaar2000boundary))");
  return params;
}

HagelaarEnergyAdvectionBC::HagelaarEnergyAdvectionBC(const InputParameters & parameters)
  : ADIntegratedBC(parameters),

    _r_units(1. / getParam<Real>("position_units")),
    _r(getParam<Real>("r")),
    _num_ions(coupledComponents("ions")),
    // Coupled Variables
    _se_coeff_names(getParam<std::vector<std::string>>("emission_coeffs")),
    _se_energy(getParam<Real>("secondary_electron_energy")),
    _mumean_en(getADMaterialProperty<Real>("mumean_en")),

    _electric_field(
        getADMaterialProperty<RealVectorValue>(getParam<std::string>("field_property_name"))),

    _a(0.5),
    _ion_flux(0, 0, 0),
    _v_thermal(0),
    _n_gamma(0),
    _bc_val(0)
{
  _ip.resize(_num_ions);
  _ip_var.resize(_num_ions);
  _grad_ip.resize(_num_ions);
  _sgnip.resize(_num_ions);
  _muip.resize(_num_ions);
  _Dip.resize(_num_ions);
  _se_coeff.resize(_num_ions);

  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    _ip_var[i] = getVar("ions", i);
    _ip[i] = &adCoupledValue("ions", i);
    _grad_ip[i] = &adCoupledGradient("ions", i);
    _sgnip[i] = &getMaterialProperty<Real>("sgn" + (*getVar("ions", i)).name());
    _muip[i] = &getADMaterialProperty<Real>("mu" + (*getVar("ions", i)).name());
    _Dip[i] = &getADMaterialProperty<Real>("diff" + (*getVar("ions", i)).name());
    _se_coeff[i] = &getADMaterialProperty<Real>(_se_coeff_names[i]);
  }
}

ADReal
HagelaarEnergyAdvectionBC::computeQpResidual()
{
  // reset this value just to be safe
  _bc_val = 0;
  if (_normals[_qp] * -1.0 * _electric_field[_qp] > 0.0)
  {
    _a = 1.0;
  }
  else
  {
    _a = 0.0;
  }

  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    _ion_flux = (*_sgnip[i])[_qp] * (*_muip[i])[_qp] * _electric_field[_qp] * _r_units *
                    std::exp((*_ip[i])[_qp]) -
                (*_Dip[i])[_qp] * std::exp((*_ip[i])[_qp]) * (*_grad_ip[i])[_qp] * _r_units;
    _bc_val +=
        10. * _ion_flux * _normals[_qp] * _se_energy * (*_se_coeff[i])[_qp] * (_a - 1.) * (_r + 1.);
  }

  return _test[_i][_qp] * _r_units / (6. * (_r + 1.)) *
         (_bc_val + (_r - 1.) * (std::exp(_u[_qp]) - _se_energy * _n_gamma) *
                        (6. * _electric_field[_qp] * _r_units * _normals[_qp] * _mumean_en[_qp] *
                             (2. * _a - 1.) -
                         5. * _v_thermal));
}
