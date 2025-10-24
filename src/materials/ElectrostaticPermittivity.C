//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ElectrostaticPermittivity.h"
#include "MooseUtils.h"
#include "Zapdos.h"

registerMooseObject("ZapdosApp", ElectrostaticPermittivity);

InputParameters
ElectrostaticPermittivity::validParams()
{
  InputParameters params = Material::validParams();

  params.addRequiredCoupledVar("potential", "The electrostatic potential");
  params.addParam<MaterialPropertyName>("permittivity",
                                        "The name of the plasma/material permittivity (if not "
                                        "provided, the permittivity of free space will be used)");
  params.addClassDescription(
      "Provides the electrostatic permittivity value as a material property.");

  return params;
}

ElectrostaticPermittivity::ElectrostaticPermittivity(const InputParameters & parameters)
  : Material(parameters),
    _supplied_permittivity(isParamValid("permittivity")),
    _permittivity(_supplied_permittivity ? getADMaterialProperty<Real>("permittivity")
                                         : getGenericZeroMaterialProperty<Real, true>()),
    _diffpotential(declareADProperty<Real>("diff" + (*getVar("potential", 0)).name()))
{
}

void
ElectrostaticPermittivity::computeQpProperties()
{
  if (!_supplied_permittivity)
    _diffpotential[_qp] = ZAPDOS_CONSTANTS::eps_0;
  else
    _diffpotential[_qp] = _permittivity[_qp];
}
