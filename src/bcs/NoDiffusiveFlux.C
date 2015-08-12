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

#include "NoDiffusiveFlux.h"

template<>
InputParameters validParams<NoDiffusiveFlux>()
{
  InputParameters params = validParams<IntegratedBC>();
  return params;
}

NoDiffusiveFlux::NoDiffusiveFlux(const InputParameters & parameters) :
  IntegratedBC(parameters),

  // Material Properties

  _velocity(getMaterialProperty<RealVectorValue>("velocity"))
{}

Real
NoDiffusiveFlux::computeQpResidual()
{
  return _test[_i][_qp] * _u[_qp] * _velocity[_qp] * _normals[_qp];
}

Real
NoDiffusiveFlux::computeQpJacobian()
{
  return _test[_i][_qp] * _phi[_j][_qp] * _velocity[_qp] * _normals[_qp];
}

