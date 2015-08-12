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

#include "ElectronEnergyTransport.h"

template<>
InputParameters validParams<ElectronEnergyTransport>()
{
  InputParameters params = validParams<Kernel>();
  //params.addRequiredParam<std::string>("mobility","What mobility to use");
  params.addRequiredCoupledVar("potential", "The gradient of the potential will be used to compute the advection velocity.");
  params.addRequiredCoupledVar("em", "The electron density");
  return params;
}

ElectronEnergyTransport::ElectronEnergyTransport(const InputParameters & parameters) :
    Kernel(parameters),
    
    // Input Parameters
    
    // Material properties
    
    _muem(getMaterialProperty<Real>("muem")),

    // Coupled variables
    
    _potential_id(coupled("potential")),
    _grad_potential(coupledGradient("potential")),
    _em_id(coupled("em")),
    _em(coupledValue("em")),
    _grad_em(coupledGradient("em"))
{}

Real ElectronEnergyTransport::computeQpResidual()
{   
  return -_grad_test[_i][_qp]*(-2.5*_em[_qp]*_u[_qp]*_muem[_qp]*-_grad_potential[_qp]-2.5*_muem[_qp]*_u[_qp]*(_em[_qp]*_grad_u[_qp]+_u[_qp]*_grad_em[_qp]));
}

Real ElectronEnergyTransport::computeQpJacobian()
{
  return -_grad_test[_i][_qp]*(-2.5*_em[_qp]*_phi[_j][_qp]*_muem[_qp]*-_grad_potential[_qp]-2.5*_muem[_qp]*_phi[_j][_qp]*(_em[_qp]*_grad_u[_qp]+_u[_qp]*_grad_em[_qp])-2.5*_muem[_qp]*_u[_qp]*(_em[_qp]*_grad_phi[_j][_qp]+_phi[_j][_qp]*_grad_em[_qp]));
}

Real ElectronEnergyTransport::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id)
  {
    return -_grad_test[_i][_qp]*(-2.5*_em[_qp]*_u[_qp]*_muem[_qp]*-_grad_phi[_j][_qp]);
  }
  else if (jvar == _em_id)
    {
      return -_grad_test[_i][_qp]*(-2.5*_phi[_j][_qp]*_u[_qp]*_muem[_qp]*-_grad_potential[_qp]-2.5*_muem[_qp]*_u[_qp]*(_phi[_j][_qp]*_grad_u[_qp]+_u[_qp]*_grad_phi[_j][_qp]));
    }
  return 0.0; 
}

