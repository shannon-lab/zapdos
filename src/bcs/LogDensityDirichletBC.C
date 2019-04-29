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

#include "LogDensityDirichletBC.h"

registerMooseObject("ZapdosApp", LogDensityDirichletBC);

template <>
InputParameters
validParams<LogDensityDirichletBC>()
{
  InputParameters params = validParams<NodalBC>();
  params.addRequiredParam<Real>("value", "Value of the BC");
  return params;
}

LogDensityDirichletBC::LogDensityDirichletBC(const InputParameters & parameters)
  : NodalBC(parameters),
    _value(getParam<Real>("value"))
{
}

Real
LogDensityDirichletBC::computeQpResidual()
{
  return (std::exp(_u[_qp]) * 6.022e23) - _value;
}

Real
LogDensityDirichletBC::computeQpJacobian()
{
  return (std::exp(_u[_qp]) * 6.022e23);
}
