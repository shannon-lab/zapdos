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

#include "ElectronTemperatureDirichletBC.h"

registerMooseObject("ZapdosApp", ElectronTemperatureDirichletBC);

template <>
InputParameters
validParams<ElectronTemperatureDirichletBC>()
{
  InputParameters params = validParams<NodalBC>();
  params.addRequiredParam<Real>("value", "Value of the BC");
  params.addRequiredCoupledVar("em", "The electron density.");
  params.addParam<Real>("penalty_value", 1.0, "The penalty value for the Dirichlet BC.");
  return params;
}

ElectronTemperatureDirichletBC::ElectronTemperatureDirichletBC(const InputParameters & parameters)
  : NodalBC(parameters),
    _em(coupledValue("em")),
    _em_id(coupled("em")),
    _value(getParam<Real>("value")),
    _penalty_value(getParam<Real>("penalty_value"))
{
}

Real
ElectronTemperatureDirichletBC::computeQpResidual()
{
  return _penalty_value * (2.0 / 3 * std::exp(_u[_qp] - _em[_qp]) - _value);
}

Real
ElectronTemperatureDirichletBC::computeQpJacobian()
{
  return _penalty_value * (2.0 / 3 * std::exp(_u[_qp] - _em[_qp]));
}

Real
ElectronTemperatureDirichletBC::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _em_id)
    return _penalty_value * (-2.0 / 3 * std::exp(_u[_qp] - _em[_qp]));
  else
    return 0.;
}
