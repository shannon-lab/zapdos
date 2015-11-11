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

#include "EFieldAdvection.h"

template<>
InputParameters validParams<EFieldAdvection>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("potential", "The gradient of the potential will be used to compute the advection velocity.");
  return params;
}

EFieldAdvection::EFieldAdvection(const InputParameters & parameters) :
    Kernel(parameters),
    
    _mu(getMaterialProperty<Real>("mu" + _var.name())),
    _sign(getMaterialProperty<Real>("sgn" + _var.name())),
    
    // Coupled variables
    
    _potential_id(coupled("potential")),
    _grad_potential(coupledGradient("potential"))
{}

Real EFieldAdvection::computeQpResidual()
{   
  return _mu[_qp]*_sign[_qp]*std::exp(_u[_qp])*-_grad_potential[_qp]*-_grad_test[_i][_qp];
}

Real EFieldAdvection::computeQpJacobian()
{
  return _mu[_qp]*_sign[_qp]*std::exp(_u[_qp])*_phi[_j][_qp]*-_grad_potential[_qp]*-_grad_test[_i][_qp];
}

Real EFieldAdvection::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id)
  {
    return _mu[_qp]*_sign[_qp]*std::exp(_u[_qp])*-_grad_phi[_j][_qp]*-_grad_test[_i][_qp];
  }
  else
    return 0.0; 
}

