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

#include "ReactantAARxn.h"

template<>
InputParameters validParams<ReactantAARxn>()
{
  InputParameters params = validParams<Kernel>();
  return params;
}

ReactantAARxn::ReactantAARxn(const InputParameters & parameters) :
    Kernel(parameters),
    
    _reaction_coeff(getMaterialProperty<Real>("k"+_var.name()+_var.name()))
{}

Real
ReactantAARxn::computeQpResidual()
{
  return -_test[_i][_qp] * (-2.) * _reaction_coeff[_qp] * std::exp(_u[_qp]) * std::exp(_u[_qp]);
}

Real
ReactantAARxn::computeQpJacobian()
{
  return -_test[_i][_qp] * (-2.) * _reaction_coeff[_qp] * 2. * std::exp(_u[_qp]) * std::exp(_u[_qp]) * _phi[_j][_qp];
}
