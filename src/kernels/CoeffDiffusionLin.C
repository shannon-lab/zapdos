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

#include "CoeffDiffusionLin.h"


template<>
InputParameters validParams<CoeffDiffusionLin>()
{
  InputParameters params = validParams<Diffusion>();
  return params;
}

// This diffusion kernel should only be used with species whose values are in the logarithmic form.

CoeffDiffusionLin::CoeffDiffusionLin(const InputParameters & parameters) :
    Diffusion(parameters),
    
    _diffusivity(getMaterialProperty<Real>("diff" + _var.name()))
{
}

CoeffDiffusionLin::~CoeffDiffusionLin()
{
}

Real
CoeffDiffusionLin::computeQpResidual()
{
  return -_diffusivity[_qp] * _grad_u[_qp] * -_grad_test[_i][_qp];
}

Real
CoeffDiffusionLin::computeQpJacobian()
{
  return -_diffusivity[_qp] * _grad_phi[_j][_qp] * -_grad_test[_i][_qp];
}
