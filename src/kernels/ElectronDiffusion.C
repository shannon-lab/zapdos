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

#include "ElectronDiffusion.h"


template<>
InputParameters validParams<ElectronDiffusion>()
{
  InputParameters params = validParams<Diffusion>();

  params.addRequiredCoupledVar("Te","The electron energy used to calculate the diffusivity using the Einstein relation");

  return params;
}


ElectronDiffusion::ElectronDiffusion(const InputParameters & parameters) :
    Diffusion(parameters),
    
    // Input Parameters

    // Material Properties

    _muem(getMaterialProperty<Real>("muem")),

    // Coupled Variables

    _Te(coupledValue("Te")),
    _Te_id(coupled("Te"))

    // Unique variables
{
}

ElectronDiffusion::~ElectronDiffusion()
{
}

Real
ElectronDiffusion::computeQpResidual()
{
  return _muem[_qp]*_Te[_qp]*_grad_u[_qp] * _grad_test[_i][_qp];
}

Real
ElectronDiffusion::computeQpJacobian()
{
  return _muem[_qp]*_Te[_qp]*_grad_phi[_j][_qp] * _grad_test[_i][_qp];
}

Real ElectronDiffusion::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _Te_id)
    {
  return _muem[_qp]*_phi[_j][_qp]*_grad_u[_qp] * _grad_test[_i][_qp];
    }
  else
    {
      return 0.0;
    }
}
