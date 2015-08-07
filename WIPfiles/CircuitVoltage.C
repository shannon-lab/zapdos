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
  params.addRequiredParam<UserObjectName>("data_provider","The name of the UserObject that can provide some data to materials, bcs, etc.");
  return params;
}

CircuitVoltage::CircuitVoltage(const std::string & name, InputParameters parameters) :
    NodalBC(name, parameters),
    _func(getFunction("function")),
    _ip(coupledValue("ip")),
    _grad_ip(coupledGradient("ip")),

    _data(getUserObject<ProvideMobility>("data_provider"))
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
  return _u[_qp]+f()-_data.coulomb_charge()*(std::exp(_ip[_qp])*(_data.mu_ip()*-_grad_u[_qp]-_data.diff_ip()*_grad_ip[_qp]))*_data.electrode_area()*_data.ballast_resist();
}
