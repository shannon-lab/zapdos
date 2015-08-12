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
  params.addRequiredCoupledVar("em", "The electron density.");
  return params;
}

JouleHeating::JouleHeating(const InputParameters & parameters) :
    Kernel(parameters),
    
    // Input Parameters
    
    // Material properties
    
    _muem(getMaterialProperty<Real>("muem")),

    // Coupled variables
    
    _potential_id(coupled("potential")),
    _grad_potential(coupledGradient("potential")),
    _em(coupledValue("em")),
    _grad_em(coupledGradient("em")),
    _em_id(coupled("em"))

    // Unique variables
{}

Real JouleHeating::computeQpResidual()
{
  return _test[_i][_qp]*-_grad_potential[_qp]*(-_muem[_qp]*-_grad_potential[_qp]*_em[_qp]-_muem[_qp]*_u[_qp]*_grad_em[_qp]);
}

Real JouleHeating::computeQpJacobian()
{
  return _test[_i][_qp]*-_grad_potential[_qp]*(-_muem[_qp]*_phi[_j][_qp]*_grad_em[_qp]);
}

Real JouleHeating::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id)
    {
      return _test[_i][_qp]*-_grad_phi[_j][_qp]*(-_muem[_qp]*-_grad_potential[_qp]*_em[_qp]-_muem[_qp]*_u[_qp]*_grad_em[_qp])+_test[_i][_qp]*-_grad_potential[_qp]*(-_muem[_qp]*-_grad_phi[_j][_qp]*_em[_qp]);
    }
  else if (jvar == _em_id)
    {
      return _test[_i][_qp]*-_grad_potential[_qp]*(-_muem[_qp]*-_grad_potential[_qp]*_phi[_j][_qp]-_muem[_qp]*_u[_qp]*_grad_phi[_j][_qp]);
    }
  else
    {
      return 0.0; 
    }
}
