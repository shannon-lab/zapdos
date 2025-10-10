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
#include "Zapdos.h"

// MOOSE includes
#include "MooseVariable.h"

using MetaPhysicL::raw_value;

registerMooseObject("ZapdosApp", SideCurrent);

InputParameters
SideCurrent::validParams()
{
  InputParameters params = SideIntegralVariablePostprocessor::validParams();
  params.addRequiredParam<std::string>(
      "mobility",
      "The name of the mobility material property that will be used in the flux computation.");
  params.addRequiredParam<Real>("r", "The reflection coefficient");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addRequiredCoupledVar("mean_en", "Electron energy.");
  params.deprecateParam("mean_en", "electron_energy", "04/01/2026");
  params.addRequiredCoupledVar("electron_energy", "The mean electron energy density in log form.");
  params.addRequiredCoupledVar("ions", "A list of ion densities in log form.");
  params.addClassDescription("Computes a side integral of current density");
  params.addParam<std::string>("field_property_name",
                               "field_solver_interface_property",
                               "Name of the solver interface material property.");
  return params;
}

SideCurrent::SideCurrent(const InputParameters & parameters)
  : SideIntegralVariablePostprocessor(parameters),
    _mobility(parameters.get<std::string>("mobility")),
    _mobility_coef(getMaterialProperty<Real>(_mobility)),
    _r_units(1. / getParam<Real>("position_units")),
    _r(getParam<Real>("r")),
    _sgn(getMaterialProperty<Real>("sgnArp")),
    _a(0.5),
    _electric_field(
        getADMaterialProperty<RealVectorValue>(getParam<std::string>("field_property_name"))),
    _mean_en(coupledValue("electron_energy"))
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

  if (_normals[_qp] * _sgn[_qp] * _electric_field[_qp] > 0.0)
  {
    _a = 1.0;
    _b = 0.0;
  }
  else
  {
    _a = 0.0;
    _b = 1.0;
  }

  _ve_thermal = std::sqrt(8 * 1.602e-19 * 2.0 / 3 * std::exp(_mean_en[_qp] - _u[_qp]) /
                          (libMesh::pi * 9.11e-31));

  _ion_flux = 0.0;

  for (unsigned int i = 0; i < _num_ions; ++i)
    _ion_flux += 0.5 *
                     std::sqrt(8 * ZAPDOS_CONSTANTS::k_boltz * (*_T_ions[i])[_qp] /
                               (libMesh::pi * (*_mass_ions[i])[_qp])) *
                     std::exp((*_ions[i])[_qp]) +
                 (2 * _a - 1) * (*_sgn_ions[i])[_qp] * (*_mu_ions[i])[_qp] *
                     raw_value(_electric_field[_qp]) * _r_units * std::exp((*_ions[i])[_qp]) *
                     _normals[_qp];

  return ((1. - _r) / (1. + _r) * _ion_flux +
          (1. - _r) / (1. + _r) *
              (-(2 * _b - 1) * _mobility_coef[_qp] * raw_value(_electric_field[_qp]) * _r_units *
                   std::exp(_u[_qp]) * _normals[_qp] +
               0.5 * _ve_thermal * std::exp(_u[_qp]))) *
         6.022e23 * 1.602e-19 * _r_units;
}
