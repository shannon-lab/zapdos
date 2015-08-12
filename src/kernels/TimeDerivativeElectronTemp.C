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

#include "TimeDerivativeElectronTemp.h"

template<>
InputParameters validParams<TimeDerivativeElectronTemp>()
{
  InputParameters params = validParams<TimeKernel>();
  params.addParam<bool>("lumping", false, "True for mass matrix lumping, false otherwise");
  // params.addRequiredCoupledVar("em", "The electron density");
  return params;
}

TimeDerivativeElectronTemp::TimeDerivativeElectronTemp(const InputParameters & parameters) :
    TimeKernel(parameters),
    _lumping(getParam<bool>("lumping"))

    // _em(coupledValue("em")),
    // _em_dot(coupledDot("em")),
    // _dem_dot(coupledDotDu("em")),
    // _em_id(coupled("em"))
{
}

Real
TimeDerivativeElectronTemp::computeQpResidual()
{
  return _test[_i][_qp]*std::exp(_u[_qp])*_u_dot[_qp];
}

Real
TimeDerivativeElectronTemp::computeQpJacobian()
{
  return _test[_i][_qp]*(std::exp(_u[_qp])*_phi[_j][_qp]*_u_dot[_qp] + std::exp(_u[_qp])*_du_dot_du[_qp]*_phi[_j][_qp]);
}
