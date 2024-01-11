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

registerMooseObject("ZapdosApp", EconomouDielectricBC);

InputParameters
EconomouDielectricBC::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  params.addRequiredParam<Real>("dielectric_constant", "The dielectric constant of the material.");
  params.addRequiredParam<Real>("thickness", "The thickness of the material.");
  params.addRequiredParam<Real>("position_units", "Units of position.");

  params.addRequiredCoupledVar("mean_en", "The mean energy.");
  params.deprecateCoupledVar("mean_en", "electron_energy", "06/01/2024");
  params.addRequiredCoupledVar("em", "The electron density.");
  params.deprecateCoupledVar("em", "electrons", "06/01/2024");
  params.addRequiredCoupledVar("ip", "The ion density.");
  params.deprecateCoupledVar("ip", "ions", "06/01/2024");
  params.addRequiredCoupledVar("potential_ion", "The ion potential");
  params.deprecateCoupledVar("potential_ion", "ion_potentials", "06/01/2024");
  params.addParam<std::vector<Real>>("users_gamma",
                                     "A secondary electron emission coeff. only used for this BC.");
  params.deprecateParam("users_gamma", "emission_coeffs", "06/01/2024");

  params.addRequiredCoupledVar("electron_energy", "The mean electron energy density. In log form");
  params.addRequiredCoupledVar("electrons", "The electron density in log form");
  params.addRequiredCoupledVar("ions", "A list of ion densities in log form");
  params.addRequiredCoupledVar("ion_potentials",
                               "The effective potential for each ion provided in 'ions'");
  params.addParam<std::vector<Real>>(
      "emission_coeffs",
      "The secondary electron emission coefficient for each ion provided in `ions`");
  params.addRequiredParam<std::string>("potential_units", "The potential units.");

  params.addClassDescription("Dielectric boundary condition"
                             "(Based on DOI: https://doi.org/10.1116/1.579300)");
  return params;
}

EconomouDielectricBC::EconomouDielectricBC(const InputParameters & parameters)
  : ADIntegratedBC(parameters),
    _r_units(1. / getParam<Real>("position_units")),

    _mean_en(adCoupledValue("electron_energy")),
    _em(adCoupledValue("electrons")),
    _grad_u_dot(_var.gradSlnDot()), // TODO: make an AD version of this in MOOSE
    _u_dot(_var.adUDot()),

    _e(getMaterialProperty<Real>("e")),
    _massem(getMaterialProperty<Real>("massem")),
    _user_se_coeff(getParam<std::vector<Real>>("emission_coeffs")),

    _epsilon_d(getParam<Real>("dielectric_constant")),
    _thickness(getParam<Real>("thickness")),
    _a(0.5),
    _ion_flux(0, 0, 0),
    _temp_flux(0, 0, 0),
    _v_thermal(0),
    _em_flux(0, 0, 0),
    _potential_units(getParam<std::string>("potential_units"))

{
  if (_potential_units.compare("V") == 0)
    _voltage_scaling = 1.;
  else if (_potential_units.compare("kV") == 0)
    _voltage_scaling = 1000;

  _num_ions = coupledComponents("ions");

  _ip.resize(_num_ions);
  _ip_var.resize(_num_ions);
  _muip.resize(_num_ions);
  _sgnip.resize(_num_ions);
  _potential_ion.resize(_num_ions);
  _grad_potential_ion.resize(_num_ions);

  bool fill_potential_vector = false;
  // There are two checks in the next loop:
  //
  //   1. There are effective potentials, but potential_ion and ip vectors are not the same length.
  //   If so, throw error.
  //
  //   2. There are no effective potentials, and potential_ion = potential. If so, ensure
  //   potential_ion is still same size as _ip.
  if (coupledComponents("ion_potentials") != _num_ions)
  {
    if ((coupledComponents("ion_potentials") == 1) &&
        (getVar("ion_potentials", 0)->number() == _var.number()))
    {
      fill_potential_vector = true;
    }
    else
    {
      mooseError(
          "EconomouDielectricBC with name ", name(), ": `ion` and `ion_potentials` vectors are not same length. There are "
          "two "
          "possible options: \n 1) Ions respond to an effective potential. If so, make sure each "
          "ion has an associated effective potential. \n 2) Ions and electrons respond to the same "
          "potential. If so, set potential_ion equal to this potential.\n");
    }

    if (_user_se_coeff.size() != _num_ions)
      mooseError(
          "EconomouDielectricBC with name ", name(), ": The lengths of `ions` and `emission_coeffs` must be the same");
  }

  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    _ip_var[i] = getVar("ions", i);
    _ip[i] = &adCoupledValue("ions", i);
    _muip[i] = &getADMaterialProperty<Real>("mu" + (*getVar("ions", i)).name());
    _sgnip[i] = &getMaterialProperty<Real>("sgn" + (*getVar("ions", i)).name());

    if (fill_potential_vector)
    {
      _potential_ion[i] = &adCoupledValue("ion_potentials", 0);
      _grad_potential_ion[i] = &adCoupledGradient("ion_potentials", 0);
    }
    else
    {
      _potential_ion[i] = &adCoupledValue("ion_potentials", i);
      _grad_potential_ion[i] = &adCoupledGradient("ion_potentials", i);
    }
  }
}

ADReal
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
    _temp_flux = _a * (*_sgnip[i])[_qp] * (*_muip[i])[_qp] * -(*_grad_potential_ion[i])[_qp] *
                 _r_units * std::exp((*_ip[i])[_qp]);
    _ion_flux += _temp_flux;
    _em_flux -= _user_se_coeff[i] * _temp_flux;
  }

  _v_thermal =
      std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_mean_en[_qp] - _em[_qp]) / (M_PI * _massem[_qp]));

  _em_flux += (0.25 * _v_thermal * std::exp(_em[_qp]) * _normals[_qp]);

  return _test[_i][_qp] * _r_units *
         ((_thickness / _epsilon_d) * _e[_qp] * 6.022e23 * (_ion_flux - _em_flux) * _normals[_qp] /
              _voltage_scaling +
          (_thickness / _epsilon_d) * 8.8542e-12 * -_grad_u_dot[_qp] * _r_units * _normals[_qp] -
          _u_dot[_qp]);
}
