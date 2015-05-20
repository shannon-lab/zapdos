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
  // Start with the parameters from our parent
  InputParameters params = validParams<Diffusion>();

  // No parameters are necessary here because we're going to get
  // permeability and viscosity from the Material
  // so we just return params...

  params.addParam<std::string>("string","What diffusivity to use");
  return params;
}


CoeffDiffusion::CoeffDiffusion(const std::string & name, InputParameters parameters) :
    Diffusion(name, parameters),
    
    // Input Parameters

    _string(getParam<std::string>("string")),

    // Material Properties

    _diffusivity(getMaterialProperty<Real>(getParam<std::string>("string")))
{
}

CoeffDiffusion::~CoeffDiffusion()
{
}

Real
CoeffDiffusion::computeQpResidual()
{
  // Use the MaterialProperty references we stored earlier
  return _diffusivity[_qp] * _grad_u[_qp] * _grad_test[_i][_qp];
}

Real
CoeffDiffusion::computeQpJacobian()
{
  // Use the MaterialProperty references we stored earlier
  return _diffusivity[_qp] * _grad_phi[_j][_qp] * _grad_test[_i][_qp];
}
