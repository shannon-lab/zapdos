//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ADSurfaceCharge.h"
#include "MooseUtils.h"

registerADMooseObject("ZapdosApp", ADSurfaceCharge);

InputParameters
ADSurfaceCharge::validParams()
{
  InputParameters params = ADMaterial::validParams();
  params.addParam<std::string>("bc_type",
                               "Hagelaar",
                               "The name of the family of BCs being used in this model. "
                               "Options: Hagelaar (DEFAULT), Sakiyama, Lymberopoulos.");
  params.addParam<Real>("r_ion", 0.0, "The ion reflection coefficient on this boundary.");
  params.addParam<Real>("r_electron", 0.0, "The electron reflection coefficient on this boundary.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addRequiredCoupledVar("species",
                               "All of the charged species that interact with this boundary.");
  params.addParam<Real>("ks", "The recombination coefficient (for Lymberopoulos-type BC)");
  params.addParam<bool>(
      "secondary_electrons",
      true,
      "Whether or not to include secondary electron emission in the surface charge calculation. "
      "Note that this should be consistent with the selected boundary conditions; if a secondary "
      "electron BC is used on this boundary, this should be true. DEFAULT: true.");
  params.addRequiredParam<std::string>("potential_units", "The potential units.");
  params.addParam<std::string>("field_property_name",
                               "field_solver_interface_property",
                               "Name of the solver interface material property.");
  params.addClassDescription(
      "Adds a surface charge material property based on the rate of change of the total charged "
      "flux to a boundary. (NOTE: this material is meant to be boundary-restricted.)");
  return params;
}

ADSurfaceCharge::ADSurfaceCharge(const InputParameters & parameters)
  : ADMaterial(parameters),
    _sigma(declareADProperty<Real>("surface_charge")),
    _sigma_old(getMaterialPropertyOld<Real>("surface_charge")),
    _plasma_current(declareProperty<Real>("plasma_current")),

    _r_units(1. / getParam<Real>("position_units")),

    _potential_units(getParam<std::string>("potential_units")),
    _electric_field(
        getADMaterialProperty<RealVectorValue>(getParam<std::string>("field_property_name")))
{
  // Define voltage scaling parameter
  if (_potential_units.compare("V") == 0)
    _voltage_scaling = 1.;
  else if (_potential_units.compare("kV") == 0)
    _voltage_scaling = 1000;

  _num_species = coupledComponents("species");

  // Resize the vectors to store _num_species pointers
  _species.resize(_num_species);
  _grad_species.resize(_num_species);
  _mu.resize(_num_species);
  _diff.resize(_num_species);
  _sgn.resize(_num_species);

  for (unsigned int i = 0; i < _num_species; ++i)
  {
    _species[i] = &adCoupledValue("species", i);
    _grad_species[i] = &adCoupledGradient("species", i);
    _mu[i] = &getADMaterialProperty<Real>("mu" + (*getVar("species", i)).name());
    _diff[i] = &getADMaterialProperty<Real>("diff" + (*getVar("species", i)).name());
    _sgn[i] = &getMaterialProperty<Real>("sgn" + (*getVar("species", i)).name());
  }

  // Precalculate constant values
  _q_times_NA = 1.602e-19 * 6.022e23 / _voltage_scaling;
}

void
ADSurfaceCharge::initQpStatefulProperties()
{
  _sigma[_qp] = 0;
}

void
ADSurfaceCharge::computeQpProperties()
{
  if (_material_data_type == Moose::FACE_MATERIAL_DATA || boundaryRestricted())
  {

    // COMPUTE CHARGED FLUX
    _charge_flux = 0.0;
    for (unsigned int i = 0; i < _num_species; ++i)
    {
      _charge_flux += (*_sgn[i])[_qp] * std::exp((*_species[i])[_qp]) *
                      ((*_sgn[i])[_qp] * (*_mu[i])[_qp] * _electric_field[_qp] * _r_units -
                       (*_diff[i])[_qp] * (*_grad_species[i])[_qp] * _r_units) *
                      _normals[_qp];
    }

    _plasma_current[_qp] = MetaPhysicL::raw_value(_charge_flux) * 1.602e-19 * 6.022e23;

    _sigma[_qp] = _sigma_old[_qp] + _charge_flux * _q_times_NA * _dt;
  }
  else
    _sigma[_qp] = 0.;
}
