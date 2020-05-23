//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "SurfaceCharge.h"

registerMooseObject("ZapdosApp", SurfaceCharge);

template <>
InputParameters
validParams<SurfaceCharge>()
{
  InputParameters params = validParams<Material>();
  params.addParam<std::string>("bc_type",
                               "Hagelaar",
                               "The name of the family of BCs being used in this model. "
                               "Options: Hagelaar (DEFAULT), Sakiyama, Lymberopoulos.");
  params.addRequiredCoupledVar("potential", "The potential that drives the advective flux.");
  params.addParam<Real>("r_ion", 0.0, "The ion reflection coefficient on this boundary.");
  params.addParam<Real>("r_electron", 0.0, "The electron reflection coefficient on this boundary.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addRequiredCoupledVar("mean_en", "Electron energy.");
  params.addRequiredCoupledVar("em", "Electron density.");
  params.addRequiredCoupledVar("ions", "All of the ions that can interact with this boundary.");
  params.addParam<Real>("ks", "The recombination coefficient (for Lymberopoulos-type BC)");
  params.addParam<Real>("se_coeff", "The secondary electron emission coefficient.");
  params.addParam<bool>(
      "secondary_electrons",
      true,
      "Whether or not to include secondary electron emission in the surface charge calculation. "
      "Note that this should be consistent with the selected boundary conditions; if a secondary "
      "electron BC is used on this boundary, this should be true. DEFAULT: true.");
  params.addRequiredParam<std::string>("potential_units", "The potential units.");
  params.addClassDescription(
      "Adds a surface charge material property based on the rate of change of the total charged "
      "flux to a boundary. (NOTE: this material is meant to be boundary-restricted.)");
  return params;
}

SurfaceCharge::SurfaceCharge(const InputParameters & parameters)
  : Material(parameters),

    // Declare material properties
    _sigma(declareProperty<Real>("surface_charge")),
    _sigma_old(getMaterialPropertyOld<Real>("surface_charge")),
    //_d_sigma_d_potential_old(getMaterialPropertyOld<Real>("d_surface_charge_d_potential")),
    //_d_sigma_d_em_old(getMaterialPropertyOld<Real>("d_surface_charge_d_em")),
    //_d_sigma_d_mean_en_old(getMaterialPropertyOld<Real>("d_surface_charge_d_mean_en")),
    _d_sigma_d_potential(declareProperty<Real>("d_surface_charge_d_potential")),
    _d_sigma_d_em(declareProperty<Real>("d_surface_charge_d_em")),
    _d_sigma_d_mean_en(declareProperty<Real>("d_surface_charge_d_mean_en")),
    _d_sigma_d_ion(declareProperty<std::vector<Real>>("d_surface_charge_d_ion")),

    // Potential derivative jacobian terms
    _d_electron_flux_d_potential(0),
    _d_ion_flux_d_potential(0),
    _d_ion_charge_flux_d_potential(0),
    _d_n_gamma_d_potential(0),
    //_d_ion_flux_d_ions(0),

    // Electron derivative jacobian terms
    _d_electron_flux_d_em(0),
    _d_n_gamma_d_em(0),

    // Mean energy derivative jacobian terms
    _d_electron_flux_d_mean_en(0),
    _d_n_gamma_d_mean_en(0),

    // Secondary electron parameters
    _include_secondary_electrons(getParam<bool>("secondary_electrons")),

    // Coupled Variables
    _muem(getMaterialProperty<Real>("muem")),
    _d_muem_d_actual_mean_en(getMaterialProperty<Real>("d_muem_d_actual_mean_en")),
    _massem(getMaterialProperty<Real>("massem")),
    _r_units(1. / getParam<Real>("position_units")),
    _r_ion(getParam<Real>("r_ion")),
    _r_electron(getParam<Real>("r_electron")),
    _kb(getMaterialProperty<Real>("k_boltz")),
    _e(getMaterialProperty<Real>("e")),
    _potential_units(getParam<std::string>("potential_units")),
    _a(0.5),
    _b(0.5),
    _grad_potential(coupledGradient("potential")),
    _mean_en(coupledValue("mean_en")),
    _em(coupledValue("em")),
    _grad_em(coupledGradient("em"))
{
  // Error checking - make sure secondary electron parameters are consistent
  if (_include_secondary_electrons && !isParamValid("se_coeff"))
    mooseError("SurfaceCharge material: secondary_electrons is set to true, but no secondary "
               "electron emission coefficient is supplied. Add se_coeff to input parameters.");
  else
    _se_coeff = getParam<Real>("se_coeff");

  std::string bc = getParam<std::string>("bc_type");
  if (bc == "Hagelaar")
  {
    _bc_type = 0;
  }
  else if (bc == "Sakiyama")
  {
    _bc_type = 1;
  }
  else if (bc == "Lymberopoulos")
  {
    _bc_type = 2;
    if (!isParamValid("ks"))
      mooseError("SurfaceCharge: bc_type = Lymberopoulos requires the electron recombination "
                 "coefficient 'ks' as input. Put the same value used in LymberopoulosElectronBC.");
    else
      _ks = getParam<Real>("ks");
  }
  else if (bc == "Comsol")
  {
    _bc_type = 3;
  }
  else
    mooseError("SurfaceCharge: bc_type = " + getParam<std::string>("bc_type") +
               " is not supported. Please select Hagelaar, Sakiyama, or Lymberopoulos. (The choice "
               "should be consistent with the BCs chosen for electrons and heavy species.)");

  // Define voltage scaling parameter
  if (_potential_units.compare("V") == 0)
    _voltage_scaling = 1.;
  else if (_potential_units.compare("kV") == 0)
    _voltage_scaling = 1000;

  // Initialize the vectors to store ion density and transport values
  _num_ions = coupledComponents("ions");

  //_d_ion_flux_d_ions.resize(_num_ions);

  // Resize the vectors to store _num_ions pointers
  _ions.resize(_num_ions);
  _mu_ions.resize(_num_ions);
  _sgn_ions.resize(_num_ions);
  _mass_ions.resize(_num_ions);
  _T_ions.resize(_num_ions);
  _grad_ions.resize(_num_ions);

  // Resize derivative vectors
  _d_ion_flux_d_ion.resize(_num_ions);
  _d_ion_charge_flux_d_ion.resize(_num_ions);
  _d_n_gamma_d_ion.resize(_num_ions);
  _d_electron_flux_d_ion.resize(_num_ions);

  for (unsigned int i = 0; i < _ions.size(); ++i)
  {
    _ions[i] = &coupledValue("ions", i);
    _grad_ions[i] = &coupledGradient("ions", i);
    _mu_ions[i] = &getMaterialProperty<Real>("mu" + (*getVar("ions", i)).name());
    _sgn_ions[i] = &getMaterialProperty<Real>("sgn" + (*getVar("ions", i)).name());
    _mass_ions[i] = &getMaterialProperty<Real>("mass" + (*getVar("ions", i)).name());
    _T_ions[i] = &getMaterialProperty<Real>("T" + (*getVar("ions", i)).name());
  }

  // Precalculate constant values
  _q_times_NA = 1.602e-19 * 6.022e23 / _voltage_scaling;
  _r_factor_ion = (1. - _r_ion) / (1. + _r_ion);
  _r_factor_electron = (1. - _r_electron) / (1. + _r_electron);
}

void
SurfaceCharge::initQpStatefulProperties()
{
  _sigma[_qp] = 0;

  //_d_sigma_d_potential[_qp] = 0;
  //_d_sigma_d_em[_qp] = 0;
  //_d_sigma_d_mean_en[_qp] = 0;
}

void
SurfaceCharge::computeQpProperties()
{
  if (_material_data_type == Moose::FACE_MATERIAL_DATA || boundaryRestricted())
  {

    _actual_mean_energy = std::exp(_mean_en[_qp] - _em[_qp]);

    _ve_thermal = std::sqrt(8 * 1.602e-19 * 2.0 / 3 * _actual_mean_energy / (M_PI * 9.11e-31));

    // _phi is kept in the InterfaceKernel!
    _d_ve_thermal_d_em =
        -0.5 / _ve_thermal * 8 * _e[_qp] * 2.0 / 3 * _actual_mean_energy / (M_PI * _massem[_qp]);

    _d_ve_thermal_d_mean_en =
        0.5 / _ve_thermal * 8 * _e[_qp] * 2.0 / 3 * _actual_mean_energy / (M_PI * _massem[_qp]);

    /* Initialize ion flux terms
     * _ion_flux - the total particle flux of ions.
     * _ion_charge_flux - the total CHARGE flux to the wall. If there are only positive or negative
     * ions this is identical to _ion_flux, but if there is a mix this will be smaller.
     */
    _ion_flux = 0.0;
    _ion_charge_flux = 0.0;
    _d_ion_flux_d_potential = 0.0;
    _d_ion_charge_flux_d_potential = 0.0;
    _d_electron_flux_d_potential = 0.0;
    _d_sigma_d_potential[_qp] = 0;

    // Ion and electron fluxes, including secondary electron contributions, are computed based on
    // the selected BC form.
    switch (_bc_type)
    {
      case 0:
        computeHagelaarFlux();
        break;
      case 1:
        computeSakiyamaFlux();
        break;
      case 2:
        computeLymberopoulosFlux();
        break;
      case 3:
        computeComsolFlux();
        break;
    }
    // Real k1, k2, k3, k4;
    // Real net_flux;
    // net_flux = (_ion_charge_flux - _electron_flux) * _q_times_NA;

    // Regardless of the case, the surface charge formulation is identical.

    _sigma[_qp] = _sigma_old[_qp] + (_ion_charge_flux - _electron_flux) * _q_times_NA * _dt;
    // k1 = net_flux;
    // k2 = (net_flux + 0.5 * k1 * _dt)*_dt;
    // k3 = (net_flux + 0.5 * k2 * _dt)*_dt;
    // k4 = (net_flux + k3 * _dt)*_dt;
    //_sigma[_qp] = _sigma_old[_qp] + (1.0/6.0)*(k1 + k2 + k3 + k4);

    // The derivative of surface charge w.r.t. potential
    // (Except the _phi and _grad_phi terms, of course.)
    /*
    _d_sigma_d_potential[_qp] =
        _d_sigma_d_potential_old[_qp] +
        (_d_ion_charge_flux_d_potential - _d_electron_flux_d_potential) * _q_times_NA * _dt;

    _d_sigma_d_em[_qp] = _d_sigma_d_em_old[_qp] + -_d_electron_flux_d_em * _q_times_NA * _dt;

    _d_sigma_d_mean_en[_qp] =
        _d_sigma_d_mean_en_old[_qp] + -_d_electron_flux_d_mean_en * _q_times_NA * _dt;
        */
    _d_sigma_d_potential[_qp] =
        (_d_ion_charge_flux_d_potential - _d_electron_flux_d_potential) * _q_times_NA * _dt;

    _d_sigma_d_em[_qp] = -_d_electron_flux_d_em * _q_times_NA * _dt;

    _d_sigma_d_mean_en[_qp] = -_d_electron_flux_d_mean_en * _q_times_NA * _dt;

    _d_sigma_d_ion[_qp].resize(_num_ions);
    for (unsigned int i = 0; i < _num_ions; ++i)
    {
      _d_sigma_d_ion[_qp][i] =
          (_d_ion_charge_flux_d_ion[i] - _d_electron_flux_d_ion[i]) * _q_times_NA * _dt;
    }
  }
  else
    _sigma[_qp] = 0.;
}

void
SurfaceCharge::computeHagelaarFlux()
{
  if (_normals[_qp] * -1 * -_grad_potential[_qp] > 0.0)
  {
    _b = 1.0;
  }
  else
  {
    _b = 0.0;
  }

  _electron_flux = _r_factor_electron * std::exp(_em[_qp]) *
                   (-(2 * _b - 1) * _muem[_qp] * -_grad_potential[_qp] * _r_units * _normals[_qp] +
                    0.5 * _ve_thermal);

  _d_electron_flux_d_potential =
      _r_factor_electron * (-(2 * _b - 1) * _muem[_qp] * _r_units *
                            std::exp(_em[_qp])); // * -_grad_phi[_j][_qp] * _r_units * _normals[_qp]

  _d_electron_flux_d_em = _r_factor_electron * std::exp(_em[_qp]) *
                          (-(2 * _b - 1) * -_grad_potential[_qp] * _r_units * _normals[_qp] *
                               (_muem[_qp] - _d_muem_d_actual_mean_en[_qp] * _actual_mean_energy) +
                           0.5 * (_d_ve_thermal_d_mean_en + _ve_thermal));

  _d_electron_flux_d_mean_en =
      _r_factor_electron * std::exp(_em[_qp]) *
      (-(2 * _b - 1) * _d_muem_d_actual_mean_en[_qp] * _actual_mean_energy * -_grad_potential[_qp] *
           _r_units * _normals[_qp] +
       0.5 * (_d_ve_thermal_d_mean_en + _ve_thermal));

  // Compute the ion fluxes.
  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    if (_normals[_qp] * (*_sgn_ions[i])[_qp] * -_grad_potential[_qp] > 0.0)
    {
      _a = 1.0;
    }
    else
    {
      _a = 0.0;
    }

    _single_ion_flux =
        std::exp((*_ions[i])[_qp]) *
        (0.5 * std::sqrt(8 * _kb[_qp] * (*_T_ions[i])[_qp] / (M_PI * (*_mass_ions[i])[_qp])) +
         (2 * _a - 1) * (*_sgn_ions[i])[_qp] * (*_mu_ions[i])[_qp] * -_grad_potential[_qp] *
             _r_units * _normals[_qp]);

    // _ion_flux is the total particle flux striking the wall. This needs to be separate from the
    // charge flux to account for negative ions striking the wall and emitting secondary electrons.
    // Otherwise the secondary electron emission would be lower than the boundary condition's
    // calculation, causing a charge imbalance.
    _ion_flux += _single_ion_flux;

    // _ion_charge_flux is the net charge per area per unit time impacting a given boundary.
    _ion_charge_flux += (*_sgn_ions[i])[_qp] * _single_ion_flux;

    _d_ion_flux_d_potential += std::exp((*_ions[i])[_qp]) * (2 * _a - 1) * (*_sgn_ions[i])[_qp] *
                               (*_mu_ions[i])[_qp] * _r_units;

    _d_ion_charge_flux_d_potential += (*_sgn_ions[i])[_qp] * std::exp((*_ions[i])[_qp]) *
                                      (2 * _a - 1) * (*_sgn_ions[i])[_qp] * (*_mu_ions[i])[_qp] *
                                      _r_units;

    _d_ion_flux_d_ion[i] = _single_ion_flux * _r_factor_ion;
    _d_ion_charge_flux_d_ion[i] = _d_ion_flux_d_ion[i] * (*_sgn_ions[i])[_qp];

    if (_include_secondary_electrons == true && (*_sgn_ions[i])[_qp] >= 0)
    {
      _d_n_gamma_d_ion[i] = (1. - _b) * _se_coeff * _d_ion_flux_d_ion[i] /
                            (_muem[_qp] * -_grad_potential[_qp] * _r_units * _normals[_qp] +
                             std::numeric_limits<double>::epsilon());

      _d_electron_flux_d_ion[i] =
          (_r_factor_electron * (-0.5 * _ve_thermal * _d_n_gamma_d_ion[i]) -
           (2.0 / (1 + _r_electron) * (1. - _b) * _se_coeff * _d_ion_flux_d_ion[i]));
    }
    else
    {
      _d_n_gamma_d_ion[i] = 0.0;
      _d_electron_flux_d_ion[i] = 0.0;
    }
  }
  _ion_flux *= _r_factor_ion;
  _ion_charge_flux *= _r_factor_ion;
  _d_ion_flux_d_potential *= _r_factor_ion;
  _d_ion_charge_flux_d_potential *= _r_factor_ion;

  // Subtract secondary electrons from the electron flux if the secondary_electrons option is set to
  // true. Otherwise the _electron_flux is already correct.
  if (_include_secondary_electrons == true)
  {
    _n_gamma = (1. - _b) * _se_coeff * _ion_flux /
               (_muem[_qp] * -_grad_potential[_qp] * _r_units * _normals[_qp] +
                std::numeric_limits<double>::epsilon());

    // All derivative terms are missing multiplication by -_grad_phi[_i][_j]. This will be added in
    // the InterfaceKernel
    _d_n_gamma_d_potential =
        (1. - _b) * _se_coeff / _muem[_qp] *
        (_d_ion_flux_d_potential / (-_grad_potential[_qp] * _r_units * _normals[_qp] +
                                    std::numeric_limits<double>::epsilon()) -
         _ion_flux / (std::pow(-_grad_potential[_qp] * _r_units * _normals[_qp], 2.) +
                      std::numeric_limits<double>::epsilon()));

    // Derivative of _n_gamma w.r.t. electron density
    // Note that the SIGN (but not the actual VALUE) of _phi is included here
    _d_n_gamma_d_em =
        (1. - _b) * _se_coeff * _ion_flux /
        (-_grad_potential[_qp] * _r_units * _normals[_qp] * (_muem[_qp] * _muem[_qp]) +
         std::numeric_limits<double>::epsilon()) *
        _d_muem_d_actual_mean_en[_qp] * _actual_mean_energy;
    /*
    _d_n_gamma_d_em = (1. - _b) * _se_coeff * _ion_flux /
                      (std::pow(_muem[_qp] * -_grad_potential[_qp] * _r_units * _normals[_qp], 2.) +
                       std::numeric_limits<double>::epsilon()) *
                      -_grad_potential[_qp] * _r_units * _normals[_qp] *
                      _d_muem_d_actual_mean_en[_qp] * _actual_mean_energy;
                      */

    _d_n_gamma_d_mean_en =
        (1. - _b) * _se_coeff * _ion_flux /
        (-_muem[_qp] * _muem[_qp] * -_grad_potential[_qp] * _r_units * _normals[_qp] +
         std::numeric_limits<double>::epsilon()) *
        _d_muem_d_actual_mean_en[_qp] * _actual_mean_energy;
    /*
    _d_n_gamma_d_mean_en =
        (1. - _b) * _se_coeff * _ion_flux /
        (std::pow(_muem[_qp] * -_grad_potential[_qp] * _r_units * _normals[_qp], 2.) +
         std::numeric_limits<double>::epsilon()) *
        -_grad_potential[_qp] * _r_units * _normals[_qp] * _d_muem_d_actual_mean_en[_qp] *
        _actual_mean_energy;
        */

    _electron_flux += (_r_factor_electron * (-0.5 * _ve_thermal * _n_gamma) -
                       (2.0 / (1 + _r_electron) * (1. - _b) * _se_coeff * _ion_flux));

    _d_electron_flux_d_potential +=
        _r_factor_electron *
        ((-0.5 * _ve_thermal * _d_n_gamma_d_potential) -
         (2.0 / (1. + _r_electron)) * (1. - _b) * _se_coeff * _d_ion_flux_d_potential);

    _d_electron_flux_d_em +=
        _r_factor_electron * -0.5 * (_d_ve_thermal_d_em * _n_gamma + _ve_thermal * _d_n_gamma_d_em);

    _d_electron_flux_d_mean_en +=
        _r_factor_electron * -0.5 *
        (_d_ve_thermal_d_mean_en * _n_gamma + _ve_thermal * _d_n_gamma_d_mean_en);
  }
}

void
SurfaceCharge::computeSakiyamaFlux()
{
  _electron_flux = std::exp(_em[_qp]) * (0.25 * _ve_thermal);

  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    if (_normals[_qp] * (*_sgn_ions[i])[_qp] * -_grad_potential[_qp] > 0.0)
      _b = 1.0;
    else
      _b = 0.0;

    _single_ion_flux = _b * (*_sgn_ions[i])[_qp] * (*_mu_ions[i])[_qp] * -_grad_potential[_qp] *
                       _r_units * std::exp((*_ions[i])[_qp]) * _normals[_qp];

    _ion_flux += _single_ion_flux;

    _ion_charge_flux += (*_sgn_ions[i])[_qp] * _single_ion_flux;
  }

  if (_include_secondary_electrons == true)
  {
    _electron_flux -= _a * _se_coeff * _ion_flux;
  }
}

void
SurfaceCharge::computeLymberopoulosFlux()
{
  _electron_flux = _ks * std::exp(_em[_qp]) * _normals[_qp] * _normals[_qp];

  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    _single_ion_flux = (*_mu_ions[i])[_qp] * -_grad_potential[_qp] * _r_units *
                       std::exp((*_ions[i])[_qp]) * _normals[_qp];

    _ion_flux += _single_ion_flux;

    _ion_charge_flux += (*_sgn_ions[i])[_qp] * _single_ion_flux;
  }

  if (_include_secondary_electrons == true)
  {
    _electron_flux -= _se_coeff * _ion_flux;
  }
}

void
SurfaceCharge::computeComsolFlux()
{
  if (_normals[_qp] * -1 * -_grad_potential[_qp] > 0.0)
  {
    _b = 1.0;
  }
  else
  {
    _b = 0.0;
  }

  _electron_flux = _r_factor_electron * std::exp(_em[_qp]) * 0.5 * _ve_thermal;

  _d_electron_flux_d_potential = 0.0;

  _d_electron_flux_d_em =
      _r_factor_electron * std::exp(_em[_qp]) * 0.5 * (_d_ve_thermal_d_em + _ve_thermal);

  _d_electron_flux_d_mean_en =
      _r_factor_electron * std::exp(_em[_qp]) * 0.5 * _d_ve_thermal_d_mean_en;

  // Compute the ion fluxes.
  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    if (_normals[_qp] * (*_sgn_ions[i])[_qp] * -_grad_potential[_qp] > 0.0)
    {
      _a = 1.0;
    }
    else
    {
      _a = 0.0;
    }

    _single_ion_flux =
        std::exp((*_ions[i])[_qp]) *
        (0.5 * std::sqrt(8 * _kb[_qp] * (*_T_ions[i])[_qp] / (M_PI * (*_mass_ions[i])[_qp])) +
         (_a * (*_sgn_ions[i])[_qp] * (*_mu_ions[i])[_qp] * -_grad_potential[_qp] * _r_units *
          _normals[_qp]));

    // _ion_flux is the total particle flux striking the wall. This needs to be separate from the
    // charge flux to account for negative ions striking the wall and emitting secondary electrons.
    // Otherwise the secondary electron emission would be lower than the boundary condition's
    // calculation, causing a charge imbalance.
    _ion_flux += _single_ion_flux;

    // _ion_charge_flux is the net charge per area per unit time impacting a given boundary.
    _ion_charge_flux += (*_sgn_ions[i])[_qp] * _single_ion_flux;

    _d_ion_flux_d_potential +=
        std::exp((*_ions[i])[_qp]) * _a * (*_sgn_ions[i])[_qp] * (*_mu_ions[i])[_qp] * _r_units;

    _d_ion_charge_flux_d_potential += (*_sgn_ions[i])[_qp] * std::exp((*_ions[i])[_qp]) * _a *
                                      (*_sgn_ions[i])[_qp] * (*_mu_ions[i])[_qp] * _r_units;

    _d_ion_flux_d_ion[i] = _single_ion_flux * _r_factor_ion;
    _d_ion_charge_flux_d_ion[i] = _d_ion_flux_d_ion[i] * (*_sgn_ions[i])[_qp];

    if (_include_secondary_electrons == true && (*_sgn_ions[i])[_qp] >= 0)
    {
      _d_electron_flux_d_ion[i] = -_se_coeff * _d_ion_flux_d_ion[i];
    }
    else
    {
      _d_electron_flux_d_ion[i] = 0.0;
    }
  }
  _ion_flux *= _r_factor_ion;
  _ion_charge_flux *= _r_factor_ion;
  _d_ion_flux_d_potential *= _r_factor_ion;
  _d_ion_charge_flux_d_potential *= _r_factor_ion;

  // Subtract secondary electrons from the electron flux if the secondary_electrons option is set to
  // true. Otherwise the _electron_flux is already correct.
  if (_include_secondary_electrons == true)
  {
    _electron_flux -= _se_coeff * _ion_flux;

    _d_electron_flux_d_potential -= _se_coeff * _d_ion_flux_d_potential;
  }
}
