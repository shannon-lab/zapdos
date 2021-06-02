//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "Sigma.h"
#include "Assembly.h"

registerMooseObject("ZapdosApp", Sigma);

InputParameters
Sigma::validParams()
{
  InputParameters params = AuxKernel::validParams();
  params.addParam<std::string>("field_property_name",
                               "field_solver_interface_property",
                               "Name of the solver interface material property.");
  params.addRequiredCoupledVar("n", "The density of the ions.");
  params.addClassDescription(
      "Calculates the surface charge due to a simplified version of the ion flux "
      "to a boundary.");
  return params;
}

Sigma::Sigma(const InputParameters & parameters)
  : AuxKernel(parameters),
    _u_old(uOld()),
    _n(coupledValue("n")),
    _electric_field(
        getADMaterialProperty<RealVectorValue>(getParam<std::string>("field_property_name")))
{
}

Real
Sigma::computeValue()
{
  return _u_old[_qp] + _dt * raw_value(_electric_field[_qp]) * _n[_qp] * _assembly.normals()[_qp];
}
