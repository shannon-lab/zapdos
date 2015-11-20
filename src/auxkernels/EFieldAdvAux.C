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

#include "EFieldAdvAux.h"

template<>
InputParameters validParams<EFieldAdvAux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("potential", "The gradient of the potential will be used to compute the advection velocity.");
  params.addRequiredCoupledVar("density_log","The variable representing the log of the density.");
  return params;
}

EFieldAdvAux::EFieldAdvAux(const InputParameters & parameters) :
    AuxKernel(parameters),
    
    // Coupled variables

    _density_var(*getVar("density_log",0)),
    _density_log(coupledValue("density_log")),
    _grad_potential(coupledGradient("potential")),

    // Material properties

    _mu(getMaterialProperty<Real>("mu" + _density_var.name())),
    _sgn(getMaterialProperty<Real>("sgn" + _density_var.name()))
{}

Real EFieldAdvAux::computeValue()
{  
  return _sgn[_qp] * _mu[_qp] * std::exp(_density_log[_qp]) * -_grad_potential[_qp](0);
}
