//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "DriftDiffusionFluxAux.h"

using MetaPhysicL::raw_value;

registerMooseObject("ZapdosApp", DriftDiffusionFluxAux);

InputParameters
DriftDiffusionFluxAux::validParams()
{
  InputParameters params = AuxKernel::validParams();
  params.addParam<bool>("positive_charge",
                        true,
                        "Whether the potential is advecting positive "
                        "charges. Should be set to false if charges are "
                        "negative.");
  params.addRequiredCoupledVar("u", "The drift-diffusing species.");
  params.addParam<int>("component", 0, "The flux component you want to see.");
  params.addParam<std::string>("field_property_name",
                               "field_solver_interface_property",
                               "Name of the solver interface material property.");
  params.addClassDescription("Returns the drift-diffusion flux of the specified species");
  return params;
}

DriftDiffusionFluxAux::DriftDiffusionFluxAux(const InputParameters & parameters)
  : AuxKernel(parameters),
    _sgn(getParam<bool>("positive_charge") ? 1 : -1),
    _electric_field(
        getADMaterialProperty<RealVectorValue>(getParam<std::string>("field_property_name"))),
    _u(coupledValue("u")),
    _grad_u(coupledGradient("u")),
    _component(getParam<int>("component"))
{
}

Real
DriftDiffusionFluxAux::computeValue()
{
  return _sgn * raw_value(_electric_field[_qp](_component)) * _u[_qp] - _grad_u[_qp](_component);
}
