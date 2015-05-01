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

#include "ConstTimesDiffusion.h"


template<>
InputParameters validParams<ConstTimesDiffusion>()
{
  // Start with the parameters from our parent
  InputParameters params = validParams<Diffusion>();

  // No parameters are necessary here because we're going to get
  // permeability and viscosity from the Material
  // so we just return params...

  return params;
}


ConstTimesDiffusion::ConstTimesDiffusion(const std::string & name, InputParameters parameters) :
    Diffusion(name, parameters),

    _diffusivity(getMaterialProperty<Real>("diffusivity"))
{
}

ConstTimesDiffusion::~ConstTimesDiffusion()
{
}

Real
ConstTimesDiffusion::computeQpResidual()
{
  // Use the MaterialProperty references we stored earlier
  return _diffusivity[_qp] * _grad_u[_qp] * _grad_test[_i][_qp];
}

Real
ConstTimesDiffusion::computeQpJacobian()
{
  // Use the MaterialProperty references we stored earlier
  return _diffusivity[_qp] * _grad_phi[_j][_qp] * _grad_test[_i][_qp];
}
