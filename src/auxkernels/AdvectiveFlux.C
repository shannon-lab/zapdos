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

#include "AdvectiveFlux.h"

template<>
InputParameters validParams<AdvectiveFlux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredParam<std::string>("mobility","What mobility to use");
  params.addRequiredCoupledVar("potential", "The gradient of the potential will be used to compute the advection velocity.");
  params.addRequiredCoupledVar("electron_density", "The electron density.");
  return params;
}

AdvectiveFlux::AdvectiveFlux(const InputParameters & parameters) :
    AuxKernel(parameters),
    
    // Input Parameters
    
    // Material properties

    _mobility(getMaterialProperty<Real>(getParam<std::string>("mobility"))),
    _electron_mult(getMaterialProperty<Real>("electron_mult")),
    _potential_mult(getMaterialProperty<Real>("potential_mult")),
    
    // Coupled variables
    
    _electron_density(coupledValue("electron_density")),
    _grad_potential(coupledGradient("potential"))
{}

Real AdvectiveFlux::computeValue()
{  
  return -_mobility[_qp]*_electron_density[_qp]*_electron_mult[_qp]*_grad_potential[_qp](0)*_potential_mult[_qp];
}
