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

registerADMooseObject("ZapdosApp", SecondaryElectronEnergyBC);

InputParameters
SecondaryElectronEnergyBC::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  params.addRequiredParam<Real>("r", "The reflection coefficient of the electrons.");
  params.addParam<Real>("r_ion", 0, "The reflection coefficient of the ions.");
  params.addRequiredCoupledVar("electrons", "The electron density in log form");
  params.addRequiredCoupledVar("ions", "A list of ion densities in log form");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addParam<std::string>("field_property_name",
                               "field_solver_interface_property",
                               "Name of the solver interface material property.");
  params.addRequiredParam<std::vector<std::string>>(
      "emission_coeffs", "A species-dependent list of secondary electron emission coefficients");
  params.addRequiredParam<Real>("secondary_electron_energy", "The secondary electron energy in eV");
  params.addClassDescription(
      "Kinetic secondary electron for mean electron energy boundary condition");
  return params;
}

SecondaryElectronEnergyBC::SecondaryElectronEnergyBC(const InputParameters & parameters)
  : ADIntegratedBC(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _r(getParam<Real>("r")),
    _r_ion(getParam<Real>("r_ion")),
    _kb(getMaterialProperty<Real>("k_boltz")),
    _num_ions(coupledComponents("ions")),
    _se_coeff_names(getParam<std::vector<std::string>>("emission_coeffs")),
    // Coupled Variables
    _em(adCoupledValue("electrons")),

    _muem(getADMaterialProperty<Real>("muem")),
    _massem(getMaterialProperty<Real>("massem")),
    _e(getMaterialProperty<Real>("e")),

    _se_energy(getParam<Real>("secondary_electron_energy")),
    _mumean_en(getADMaterialProperty<Real>("mumean_en")),
    _electric_field(
        getADMaterialProperty<RealVectorValue>(getParam<std::string>("field_property_name")))
{
  _ion_flux = 0;
  _a = 0.5;
  _b = 0.5;
  _v_thermal = 0.0;
  _n_gamma = 0.0;

  if (_se_coeff_names.size() != _num_ions)
    mooseError("SecondaryElectronEnergyBC with name ",
               name(),
               ": The lengths of `ions` and `emission_coeffs` must be the same");

  // Resize the vectors to store _num_ions values:
  _ip.resize(_num_ions);
  _grad_ip.resize(_num_ions);
  _muip.resize(_num_ions);
  _Tip.resize(_num_ions);
  _massip.resize(_num_ions);
  _sgnip.resize(_num_ions);
  _se_coeff.resize(_num_ions);

  // Retrieve the values for each ion and store in the relevant vectors.
  // Note that these need to be dereferenced to get the values inside the
  // main body of the code.
  // e.g. instead of "_ip[_qp]" it would be "(*_ip[i])[_qp]", where "i"
  // refers to a single ion species.
  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    _ip[i] = &adCoupledValue("ions", i);
    _grad_ip[i] = &adCoupledGradient("ions", i);
    _muip[i] = &getADMaterialProperty<Real>("mu" + (*getVar("ions", i)).name());
    _Tip[i] = &getADMaterialProperty<Real>("T" + (*getVar("ions", i)).name());
    _massip[i] = &getMaterialProperty<Real>("mass" + (*getVar("ions", i)).name());
    _sgnip[i] = &getMaterialProperty<Real>("sgn" + (*getVar("ions", i)).name());
    _se_coeff[i] = &getADMaterialProperty<Real>(_se_coeff_names[i]);
  }
}

ADReal
SecondaryElectronEnergyBC::computeQpResidual()
{
  if (_normals[_qp] * -1.0 * _electric_field[_qp] > 0.0)
  {
    _a = 1.0;
  }
  else
  {
    _a = 0.0;
  }

  _ion_flux = 0;
  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    if (_normals[_qp] * (*_sgnip[i])[_qp] * _electric_field[_qp] > 0.0)
      _b = 1.0;
    else
      _b = 0.0;
    _ion_flux += (*_se_coeff[i])[_qp] * std::exp((*_ip[i])[_qp]) *
                 (0.5 * std::sqrt(8 * _kb[_qp] * (*_Tip[i])[_qp] / (M_PI * (*_massip[i])[_qp])) +
                  (2 * _b - 1) * (*_sgnip[i])[_qp] * (*_muip[i])[_qp] * _electric_field[_qp] *
                      _r_units * _normals[_qp]);
  }

  _n_gamma = (1. - _a) * _ion_flux /
             (_muem[_qp] * _electric_field[_qp] * _r_units * _normals[_qp] +
              std::numeric_limits<double>::epsilon());

  _v_thermal =
      std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_u[_qp] - _em[_qp]) / (M_PI * _massem[_qp]));

  return _test[_i][_qp] * _r_units *
         ((1 - _r) / (1 + _r) * (-5. / 6. * _v_thermal * _n_gamma * _se_energy) -
          5. / 3. * (2. / (1 + _r)) * _se_energy * (1 - _a) * _ion_flux);
}
