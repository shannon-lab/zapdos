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

#include "JouleHeating.h"

template<>
InputParameters validParams<JouleHeating>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredCoupledVar("potential", "The gradient of the potential will be used to compute the advection velocity.");
  return params;
}

JouleHeating::JouleHeating(const std::string & name,
                       InputParameters parameters) :
    Kernel(name, parameters),
    
    // Input Parameters
    
    // Material properties
    
    _advection_coeff_em(getMaterialProperty<Real>("EFieldAdvectionCoeff_em")),
    _D_em(getMaterialProperty<Real>("D_em")),

    // Coupled variables
    
    _potential_id(coupled("potential")),
    _grad_potential(coupledGradient("potential")),
    _em(coupledValue("em")),
    _grad_em(coupledGradient("em"))
{}

Real JouleHeating::computeQpResidual()
{
     return _test[_i][_qp]*-_grad_potential[_qp]*(_advection_coeff_em[_qp]*-_grad_potential[_qp]*_em[_qp]-_D_em[_qp]*_grad_em[_qp]);
}

Real JouleHeating::computeQpJacobian()
{
  return 0.0;
}

/* Real JouleHeating::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id)
  {
    return -_u[_qp]*_grad_potential_coeff[_qp]*_grad_phi[_j][_qp]*_potential_mult[_qp]*_grad_test[_i][_qp];
  }
  
  return 0.0; 
} */

