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

#include "ReactantFirstOrderRxn.h"

template<>
InputParameters validParams<ReactantFirstOrderRxn>()
{
  InputParameters params = validParams<Kernel>();
  return params;
}

ReactantFirstOrderRxn::ReactantFirstOrderRxn(const InputParameters & parameters) :
    Kernel(parameters),
    
    _reaction_coeff(getMaterialProperty<Real>("k"+_var.name()))
{}

Real
ReactantFirstOrderRxn::computeQpResidual()
{
  return -_test[_i][_qp]*(-1.)*_reaction_coeff[_qp] * std::exp(_u[_qp]);
}

Real
ReactantFirstOrderRxn::computeQpJacobian()
{
  return -_test[_i][_qp]*(-1.)*_reaction_coeff[_qp] * std::exp(_u[_qp]) * _phi[_j][_qp];
}
