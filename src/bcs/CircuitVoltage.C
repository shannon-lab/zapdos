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

#include "CircuitVoltage.h"
#include "Function.h"

template<>
InputParameters validParams<CircuitVoltage>()
{
  InputParameters params = validParams<NodalBC>();
  params.addRequiredParam<FunctionName>("function", "The forcing function.");
  params.addRequiredCoupledVar("ip","The ion density.");
  return params;
}

CircuitVoltage::CircuitVoltage(const std::string & name, InputParameters parameters) :
    NodalBC(name, parameters),
    _func(getFunction("function")),
    _ip(coupledValue("ip")),
    _grad_ip(coupledGradient("ip")),
    _muip(getMaterialProperty<Real>("muip")),
    _diffip(getMaterialProperty<Real>("diffip")),
    _electrode_area(getMaterialProperty<Real>("electrode_area")),
    _ballast_resist(getMaterialProperty<Real>("ballast_resist")),
    _e(getMaterialProperty<Real>("e"))
{
}

Real
CircuitVoltage::f()
{
  return _func.value(_t, *_current_node);
}

Real
CircuitVoltage::computeQpResidual()
{
  return _u[_qp]+f()-_e[_qp]*(std::exp(_ip[_qp])*(_muip[_qp]*-_grad_u[_qp]-_diffip[_qp]*_grad_ip[_qp]))*_ballast_resist[_qp];
}
