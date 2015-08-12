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

template<>
InputParameters validParams<DiffusiveFlux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredParam<std::string>("diffusivity","What diffusivity to use");
  params.addRequiredCoupledVar("electron_density", "The electron density.");
  return params;
}

DiffusiveFlux::DiffusiveFlux(const InputParameters & parameters) :
    AuxKernel(parameters),
    
    // Input Parameters
    
    // Material properties

    _diffusivity(getMaterialProperty<Real>(getParam<std::string>("diffusivity"))),
    _electron_mult(getMaterialProperty<Real>("electron_mult")),
    
    // Coupled variables

    _grad_electron_density(coupledGradient("electron_density"))
{}

Real DiffusiveFlux::computeValue()
{  
  return -_diffusivity[_qp]*_grad_electron_density[_qp](0)*_electron_mult[_qp];
}
