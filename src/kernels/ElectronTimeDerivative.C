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

#include "ElectronTimeDerivative.h"

template<>
InputParameters validParams<ElectronTimeDerivative>()
{
  InputParameters params = validParams<TimeKernel>();
  params.addParam<bool>("lumping", false, "True for mass matrix lumping, false otherwise");
  return params;
}

ElectronTimeDerivative::ElectronTimeDerivative(const InputParameters & parameters) :
    TimeKernel(parameters),
    _lumping(getParam<bool>("lumping"))

{
}

Real
ElectronTimeDerivative::computeQpResidual()
{
  return _test[_i][_qp]*std::exp(_u[_qp])*_u_dot[_qp];
}

Real
ElectronTimeDerivative::computeQpJacobian()
{
  return _test[_i][_qp]*(std::exp(_u[_qp])*_phi[_j][_qp]*_u_dot[_qp] + std::exp(_u[_qp])*_du_dot_du[_qp]*_phi[_j][_qp]);
}
