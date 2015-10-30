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

#include "CoupledDiffusion.h"


template<>
InputParameters validParams<CoupledDiffusion>()
{
  InputParameters params = validParams<Diffusion>();
  return params;
}


CoupledDiffusion::CoupledDiffusion(const InputParameters & parameters) :
    Diffusion(parameters),
    _diffusivity(getMaterialProperty<Real>("diffusivity")),
    _d_diffusivity_d_u(getMaterialProperty<Real>("d_diffusivity_d_u"))
{
}

CoupledDiffusion::~CoupledDiffusion()
{
}

Real
CoupledDiffusion::computeQpResidual()
{
  return _diffusivity[_qp] * _grad_u[_qp] * _grad_test[_i][_qp];
}

Real
CoupledDiffusion::computeQpJacobian()
{
  return (_d_diffusivity_d_u[_qp] * _phi[_j][_qp] * _grad_u[_qp] + _diffusivity[_qp] * _grad_phi[_j][_qp]) * _grad_test[_i][_qp];
}
