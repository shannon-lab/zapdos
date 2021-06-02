//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "PotentialDriftOutflowBC.h"

registerMooseObject("ZapdosApp", PotentialDriftOutflowBC);

InputParameters
PotentialDriftOutflowBC::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  MooseEnum charge_sign("positive=1 negative=-1", "positive");
  params.addParam<MooseEnum>("charge_sign", charge_sign, "The sign of the charged particle.");
  params.addParam<std::string>("field_property_name",
                               "field_solver_interface_property",
                               "Name of the solver interface material property.");
  params.addClassDescription("The drift flux boundary condition");
  return params;
}

PotentialDriftOutflowBC::PotentialDriftOutflowBC(const InputParameters & parameters)
  : ADIntegratedBC(parameters),
    _charge_sign(getParam<MooseEnum>("charge_sign")),
    _electric_field(
        getADMaterialProperty<RealVectorValue>(getParam<std::string>("field_property_name")))
{
}

ADReal
PotentialDriftOutflowBC::computeQpResidual()
{
  if (_charge_sign * _electric_field[_qp] * _normals[_qp] > 0.)
    return _charge_sign * _electric_field[_qp] * _normals[_qp] * _u[_qp];
  else
    return 0.;
}
