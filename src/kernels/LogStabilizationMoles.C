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

#include "LogStabilizationMoles.h"


template<>
InputParameters validParams<LogStabilizationMoles>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<Real>("offset","The offset parameter that goes into the exponential function");
  return params;
}


LogStabilizationMoles::LogStabilizationMoles(const InputParameters & parameters) :
    Kernel(parameters),
    _offset(getParam<Real>("offset"))
{
}

LogStabilizationMoles::~LogStabilizationMoles()
{
}

Real
LogStabilizationMoles::computeQpResidual()
{
  return -_test[_i][_qp] * std::exp(-(_offset + _u[_qp]));
}

Real
LogStabilizationMoles::computeQpJacobian()
{
  return -_test[_i][_qp] * std::exp(-(_offset + _u[_qp])) * -_phi[_j][_qp];
}
