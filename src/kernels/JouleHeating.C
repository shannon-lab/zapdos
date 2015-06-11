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

JouleHeating::JouleHeating(const std::string & name,
                       InputParameters parameters) :
    Kernel(name, parameters),
    
    // Input Parameters
    
    // Material properties
    
    _advection_coeff_em(getMaterialProperty<Real>("EFieldAdvectionCoeff_em")),
    _muem(getMaterialProperty<Real>("muem")),

    // Coupled variables
    
    _potential_id(coupled("potential")),
    _grad_potential(coupledGradient("potential")),
    _em(coupledValue("em")),
    _grad_em(coupledGradient("em")),
    _em_id(coupled("em")),

    // Unique variables

    _T_em(0.0),
    _D_em(0.0)
{}

Real JouleHeating::computeQpResidual()
{
  _T_em = _u[_qp]*2.0/(3.0*_em[_qp]);
  _D_em = _muem[_qp]*_T_em;

  return _test[_i][_qp]*-_grad_potential[_qp]*(_advection_coeff_em[_qp]*-_grad_potential[_qp]*_em[_qp]-_D_em*_grad_em[_qp]);
}

Real JouleHeating::computeQpJacobian()
{
  return _test[_i][_qp]*-_grad_potential[_qp]*-_muem[_qp]*_phi[_j][_qp]*2.0/(3.0*_em[_qp])*_grad_em[_qp];
}

Real JouleHeating::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id)
  {
    return _test[_i][_qp]*-_grad_phi[_j][_qp]*_advection_coeff_em[_qp]*-_grad_potential[_qp]*_em[_qp]+_test[_i][_qp]*-_grad_potential[_qp]*_advection_coeff_em[_qp]*-_grad_phi[_j][_qp]*_em[_qp];
  }
  else if (jvar == _em_id)
    {
      return _test[_i][_qp]*-_grad_potential[_qp]*(_advection_coeff_em[_qp]*-_grad_potential[_qp]*_phi[_j][_qp]-_muem[_qp]*_u[_qp]*2.0/(3.0*_em[_qp])*_grad_phi[_j][_qp]-_muem[_qp]*_u[_qp]*2.0/(3.0*-std::pow(_em[_qp],2))*_phi[_j][_qp]*_grad_em[_qp]);
    }
  else
    {
      return 0.0; 
    }
}
