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

#include "TimeDerivativeSUPG.h"

template<>
InputParameters validParams<TimeDerivativeSUPG>()
{
  InputParameters params = validParams<TimeKernel>();
  params.addParam<bool>("lumping", false, "True for mass matrix lumping, false otherwise");
  return params;
}

TimeDerivativeSUPG::TimeDerivativeSUPG(const std::string & name, InputParameters parameters) :
    TimeKernel(name, parameters),
    _lumping(getParam<bool>("lumping")),

    // Material Properties

    _tau(getMaterialProperty<Real>("tau")),
    //    _velocity(getMaterialProperty<RealVectorValue>("velocity"))
    _velocity(getMaterialProperty<RealVectorValue>("velocity"))

    // Kernel specific properties
    //    _velocity(1.0,0.0,0.0)
{
}

Real
TimeDerivativeSUPG::computeQpResidual()
{
  return _tau[_qp]*_velocity[_qp]*_grad_test[_i][_qp]*_u_dot[_qp];
}

Real
TimeDerivativeSUPG::computeQpJacobian()
{
  return _tau[_qp]*_velocity[_qp]*_grad_test[_i][_qp]*_phi[_j][_qp]*_du_dot_du[_qp];
}

void
TimeDerivativeSUPG::computeJacobian()
{
  if (_lumping)
  {
    DenseMatrix<Number> & ke = _assembly.jacobianBlock(_var.number(), _var.number());

    for (_i = 0; _i < _test.size(); _i++)
      for (_j = 0; _j < _phi.size(); _j++)
        for (_qp = 0; _qp < _qrule->n_points(); _qp++)
        {
          ke(_i, _i) += _JxW[_qp] * _coord[_qp] * computeQpJacobian();
        }
  }
  else
    TimeKernel::computeJacobian();
}
