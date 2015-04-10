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

#include "IonizationSource.h"

template<>
InputParameters validParams<IonizationSource>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<Real>("ionization_coeff", 0.35, "The ionization coefficient of the medium");
  params.addRequiredCoupledVar("potential", "The electrical potential");
  return params;
}

IonizationSource::IonizationSource(const std::string & name, InputParameters parameters) :
    Kernel(name, parameters),
    
    _ionization_coeff(getParam<Real>("ionization_coeff")),
    _grad_potential(coupledGradient("potential")),
    _potential_id(coupled("potential"))
{}

Real
IonizationSource::computeQpResidual()
{
  return -_test[_i][_qp]*_ionization_coeff*std::exp(1.65e7/_grad_potential[_qp].size())  _u[_qp];
}

Real
IonizationSource::computeQpJacobian()
{
  return _test[_i][_qp]*_ionization_coeff*_phi[_j][_qp];
}
