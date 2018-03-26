/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "DiffusiveFlux.h"

registerMooseObject("ZapdosApp", DiffusiveFlux);

template <>
InputParameters
validParams<DiffusiveFlux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("density_log", "The variable representing the log of the density.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  return params;
}

DiffusiveFlux::DiffusiveFlux(const InputParameters & parameters)
  : AuxKernel(parameters),
    _r_units(1. / getParam<Real>("position_units")),

    // Coupled variables

    _grad_density_log(coupledGradient("density_log")),
    _density_var(*getVar("density_log", 0)),
    _density_log(coupledValue("density_log")),

    // Material properties

    _diff(getMaterialProperty<Real>("diff" + _density_var.name()))
{
}

Real
DiffusiveFlux::computeValue()
{
  return -_diff[_qp] * std::exp(_density_log[_qp]) * _grad_density_log[_qp](0) * _r_units * 6.02e23;
}
