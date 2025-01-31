//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "DriftDiffusionDoNothingBC.h"

registerMooseObject("ZapdosApp", DriftDiffusionDoNothingBC);

InputParameters
DriftDiffusionDoNothingBC::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addParam<Real>("mu", "The mobility.");
  params.addParam<Real>("diff", "The diffusivity.");
  params.addParam<Real>("sign", "The sign of the charged particle.");
  params.addParam<bool>("use_material_props", true, "Whether to use a material for properties.");
  params.addParam<std::string>("field_property_name",
                               "field_solver_interface_property",
                               "Name of the solver interface material property.");
  params.addClassDescription("Boundary condition where the flux at the boundary is equal to the "
                             "bulk dift-diffusion equation");
  return params;
}

DriftDiffusionDoNothingBC::DriftDiffusionDoNothingBC(const InputParameters & parameters)
  : ADIntegratedBC(parameters),

    _r_units(1. / getParam<Real>("position_units")),

    _mu(getParam<bool>("use_material_props") ? getADMaterialProperty<Real>("mu" + _var.name())
                                             : _user_mu),
    _sign(getParam<bool>("use_material_props") ? getMaterialProperty<Real>("sgn" + _var.name())
                                               : _user_sign),
    _diffusivity(getParam<bool>("use_material_props")
                     ? getADMaterialProperty<Real>("diff" + _var.name())
                     : _user_diff),

    _electric_field(
        getADMaterialProperty<RealVectorValue>(getParam<std::string>("field_property_name")))
{
  auto max_qps = _fe_problem.getMaxQps();
  _user_diff.resize(max_qps);
  _user_mu.resize(max_qps);
  _user_sign.resize(max_qps);
  for (decltype(max_qps) qp = 0; qp < max_qps; ++qp)
  {
    _user_diff[qp] = getParam<Real>("diff");
    _user_mu[qp] = getParam<Real>("mu");
    _user_sign[qp] = getParam<Real>("sign");
  }
}

ADReal
DriftDiffusionDoNothingBC::computeQpResidual()
{
  return _mu[_qp] * _sign[_qp] * std::exp(_u[_qp]) * _electric_field[_qp] * _r_units *
             _normals[_qp] * _test[_i][_qp] * _r_units -
         _diffusivity[_qp] * std::exp(_u[_qp]) * _grad_u[_qp] * _r_units * _normals[_qp] *
             _test[_i][_qp] * _r_units;
}
