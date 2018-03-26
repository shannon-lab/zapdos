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

#include "AbsValueAux.h"

registerMooseObject("ZapdosApp", AbsValueAux);

template <>
InputParameters
validParams<AbsValueAux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("u", "Variable we want absolute value of.");
  return params;
}

AbsValueAux::AbsValueAux(const InputParameters & parameters)
  : AuxKernel(parameters), _u(coupledValue("u"))
{
}

Real
AbsValueAux::computeValue()
{
  return std::abs(_u[_qp]);
}
