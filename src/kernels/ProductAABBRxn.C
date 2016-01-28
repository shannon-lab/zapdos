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

#include "ProductAABBRxn.h"

template<>
InputParameters validParams<ProductAABBRxn>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("v", "The variable that is reacting to create u.");
  return params;
}

ProductAABBRxn::ProductAABBRxn(const InputParameters & parameters) :
    Kernel(parameters),

    _coupled_var(*getVar("v",0)),
    _v(coupledValue("v")),
    _v_id(coupled("v")),
    _reaction_coeff(getMaterialProperty<Real>("k"+_coupled_var.name() + _coupled_var.name()))
{}

Real
ProductAABBRxn::computeQpResidual()
{
  return -_test[_i][_qp] * (2.) * _reaction_coeff[_qp] * std::exp(_v[_qp]) * std::exp(_v[_qp]);
}

Real
ProductAABBRxn::computeQpJacobian()
{
  return 0.0;
}

Real
ProductAABBRxn::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _v_id)
    return -_test[_i][_qp] * (2.) * _reaction_coeff[_qp] * 2. * std::exp(_v[_qp]) * std::exp(_v[_qp]) * _phi[_j][_qp];

  else
    return 0.0;
}
