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

  //  params.addRequiredParam<std::string>("diffusivity","What diffusivity to use");
  params.addRequiredParam<std::string>("var_name_string","The name of the kernel variable. Required to import the correct diffusivity from the material properties file.");
  return params;
}


CoeffDiffusion::CoeffDiffusion(const InputParameters & parameters) :
    Diffusion(parameters),
    
    // Input Parameters

    //    _string(getParam<std::string>("string")),

    // Material Properties

    _diffusivity(getMaterialProperty<Real>("D_"+getParam<std::string>("var_name_string")))
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
