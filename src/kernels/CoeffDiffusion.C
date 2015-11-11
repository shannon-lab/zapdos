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

#include "CoeffDiffusion.h"


template<>
InputParameters validParams<CoeffDiffusion>()
{
  InputParameters params = validParams<Diffusion>();
  return params;
}


CoeffDiffusion::CoeffDiffusion(const InputParameters & parameters) :
    Diffusion(parameters),
    
    _diffusivity(getMaterialProperty<Real>("diff" + _var.name()))
{
}

CoeffDiffusion::~CoeffDiffusion()
{
}

Real
CoeffDiffusion::computeQpResidual()
{
  return -_diffusivity[_qp] * std::exp(_u[_qp]) * _grad_u[_qp] * -_grad_test[_i][_qp];
}

Real
CoeffDiffusion::computeQpJacobian()
{
  return -_diffusivity[_qp] * (std::exp(_u[_qp]) * _grad_phi[_j][_qp] + std::exp(_u[_qp]) * _phi[_j][_qp] * _grad_u[_qp]) * -_grad_test[_i][_qp];
}
