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
  params.addParam<Real>("ionization_coeff", 0.35, "The ionization coefficient of the medium");
  params.addRequiredCoupledVar("potential", "The electrical potential");
  return params;
}

IonizationSource::IonizationSource(const InputParameters & parameters) :
    Kernel(parameters),
    
    _ionization_coeff(getParam<Real>("ionization_coeff")),
    _potential_id(coupled("potential")),
    _grad_potential(coupledGradient("potential"))
{}

/* Scaling potential such that variable magnitudes are on the same order of magnitude.
This scaling is evident anywhere where you see the potential multiplied by 1.0e4 */

Real
IonizationSource::computeQpResidual()
{
  return -_test[_i][_qp]*_ionization_coeff*(.0382+2.9e5/760.0)/(1.0e4)*1.0e4*_grad_potential[_qp].size()*_u[_qp];
}

Real
IonizationSource::computeQpJacobian()
{
  return -_test[_i][_qp]*_ionization_coeff*(.0382+2.9e5/760.0)/(1.0e4)*1.0e4*_grad_potential[_qp].size()*_phi[_j][_qp];
}

Real
IonizationSource::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id)
  {
    return -_test[_i][_qp]*_ionization_coeff*(.0382+2.9e5/760.0)/(1.0e4)*1.0e4*_grad_potential[_qp]/_grad_potential[_qp].size()*_grad_phi[_j][_qp]*_u[_qp];
  }
  
  return 0.0;
}
