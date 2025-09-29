//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "SideTotFluxIntegral.h"
#include "Zapdos.h"

// MOOSE includes
#include "MooseVariable.h"

using MetaPhysicL::raw_value;

registerMooseObject("ZapdosApp", SideTotFluxIntegral);

InputParameters
SideTotFluxIntegral::validParams()
{
  InputParameters params = SideIntegralVariablePostprocessor::validParams();
  params.addRequiredParam<std::string>(
      "mobility",
      "The name of the mobility material property that will be used in the flux computation.");
  params.addRequiredParam<Real>("r", "The reflection coefficient");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addParam<Real>(
      "user_velocity", -1., "Optional parameter if user wants to specify the thermal velocity");
  params.addParam<std::string>("field_property_name",
                               "field_solver_interface_property",
                               "Name of the solver interface material property.");
  params.addClassDescription("Returns the flux of a defined species at a boundary");
  return params;
}

SideTotFluxIntegral::SideTotFluxIntegral(const InputParameters & parameters)
  : SideIntegralVariablePostprocessor(parameters),
    _mobility(parameters.get<std::string>("mobility")),
    _mobility_coef(getMaterialProperty<Real>(_mobility)),
    _r_units(1. / getParam<Real>("position_units")),
    _r(getParam<Real>("r")),

    _T_heavy(getMaterialProperty<Real>("T_heavy")),
    _mass(getMaterialProperty<Real>("mass" + _variable->name())),
    _v_thermal(0),
    _user_velocity(getParam<Real>("user_velocity")),
    _sgn(getMaterialProperty<Real>("sgn" + _variable->name())),
    _a(0.5),

    _electric_field(
        getADMaterialProperty<RealVectorValue>(getParam<std::string>("field_property_name")))
{
}

Real
SideTotFluxIntegral::computeQpIntegral()
{
  // Output units for base case are: mol / (m^2 * s)

  if (_user_velocity > 0.)
    _v_thermal = _user_velocity;
  else
    _v_thermal =
        std::sqrt(8 * ZAPDOS_CONSTANTS::k_boltz * _T_heavy[_qp] / (libMesh::pi * _mass[_qp]));

  if (_normals[_qp] * _sgn[_qp] * _electric_field[_qp] > 0.0)
    _a = 1.0;
  else
    _a = 0.0;

  return (1. - _r) / (1. + _r) * 0.5 * _v_thermal * std::exp(_u[_qp]) +
         (1. - _r) / (1. + _r) *
             ((2 * _a - 1) * _sgn[_qp] * _mobility_coef[_qp] * raw_value(_electric_field[_qp]) *
              _r_units * std::exp(_u[_qp]) * _normals[_qp]);
}
