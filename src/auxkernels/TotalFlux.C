//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "TotalFlux.h"

#include "metaphysicl/raw_type.h"

using MetaPhysicL::raw_value;

registerMooseObject("ZapdosApp", TotalFlux);
registerMooseObject("ZapdosApp", ADTotalFlux);

template <bool is_ad>
InputParameters
TotalFluxTempl<is_ad>::validParams()
{
  InputParameters params = AuxKernel::validParams();
  params.addParam<std::string>("field_property_name",
                               "field_solver_interface_property",
                               "Name of the solver interface material property.");
  params.addRequiredCoupledVar("density_log", "The electron density");
  params.addParam<int>(
      "component", 0, "The component of the TotalFlux vector. (0 = x, 1 = y, 2 = z)");
  params.addClassDescription("Returns the total flux of the specified species");

  return params;
}

template <bool is_ad>
TotalFluxTempl<is_ad>::TotalFluxTempl(const InputParameters & parameters)
  : AuxKernel(parameters),

    _component(getParam<int>("component")),
    _density_var(*getVar("density_log", 0)),
    _density_log(coupledValue("density_log")),
    _grad_density_log(coupledGradient("density_log")),
    _electric_field(
        getADMaterialProperty<RealVectorValue>(getParam<std::string>("field_property_name"))),
    _mu(getGenericMaterialProperty<Real, is_ad>("mu" + _density_var.name())),
    _sgn(getMaterialProperty<Real>("sgn" + _density_var.name())),
    _diff(getGenericMaterialProperty<Real, is_ad>("diff" + _density_var.name()))
{
}

template <bool is_ad>
Real
TotalFluxTempl<is_ad>::computeValue()
{
  return _sgn[_qp] * raw_value(_mu[_qp]) * raw_value(_electric_field[_qp](_component)) *
            
             std::exp(_density_log[_qp]) -
         raw_value(_diff[_qp]) * std::exp(_density_log[_qp]) * _grad_density_log[_qp](_component);
}

template class TotalFluxTempl<false>;
template class TotalFluxTempl<true>;
