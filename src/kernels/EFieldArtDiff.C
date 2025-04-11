//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "EFieldArtDiff.h"

registerMooseObject("ZapdosApp", EFieldArtDiff);

InputParameters
EFieldArtDiff::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addParam<Real>("scale", 1., "Amount to scale artificial diffusion.");
  params.addRequiredParam<Real>("position_units", "Units of position");
  params.addParam<std::string>("field_property_name",
                               "field_solver_interface_property",
                               "Name of the solver interface material property.");
  params.addClassDescription("Generic artificial electric field driven advection term "
                             "(Densities must be in logarithmic form)");
  return params;
}

EFieldArtDiff::EFieldArtDiff(const InputParameters & parameters)
  : ADKernel(parameters),

    _scale(getParam<Real>("scale")),
    _r_units(1. / getParam<Real>("position_units")),

    // Material properties
    _mu(getADMaterialProperty<Real>("mu" + _var.name())),
    _electric_field(
        getADMaterialProperty<RealVectorValue>(getParam<std::string>("field_property_name")))
{
}

ADReal
EFieldArtDiff::computeQpResidual()
{
  ADReal vd_mag = _mu[_qp] * (-_electric_field[_qp]).norm() * _r_units;
  ADReal delta = vd_mag * _current_elem->hmax() / (2.0 * _r_units);

  return -_grad_test[_i][_qp] * _r_units * (-delta * std::exp(_u[_qp]) * _grad_u[_qp] * _r_units) *
         _scale;
}
