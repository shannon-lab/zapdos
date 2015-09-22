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

#include "MultipliedValueBC.h"

template<>
InputParameters validParams<MultipliedValueBC>()
{
  InputParameters params = validParams<NodalBC>();
  params.addRequiredCoupledVar("v", "The variable whose value we are to match.");
  params.addRequiredParam<Real>("mult","The multiplication factor.");
  return params;
}

MultipliedValueBC::MultipliedValueBC(const InputParameters & parameters) :
    NodalBC(parameters),
    _v(coupledValue("v")),
    _v_num(coupled("v")),

    _mult(getParam<Real>("mult"))
{
}

Real
MultipliedValueBC::computeQpResidual()
{
  return _u[_qp] - _mult*_v[_qp];
}

Real
MultipliedValueBC::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _v_num)
    return -_mult;
  else
    return 0.;
}

