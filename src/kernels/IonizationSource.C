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

IonizationSource::IonizationSource(const std::string & name, InputParameters parameters) :
    Kernel(name, parameters),
    
    _ionization_coeff(getParam<Real>("ionization_coeff")),
    _potential_id(coupled("potential")),
    _velocity_coeff(getMaterialProperty<Real>("velocity_coeff")),
    _grad_potential(coupledGradient("potential"))
{}

/* Scaling potential such that variable magnitudes are on the same order of magnitude.
This scaling is evident anywhere where you see the potential multiplied by 1.0e4 */

Real
IonizationSource::computeQpResidual()
{
  return -_test[_i][_qp]*_ionization_coeff*std::exp(-1.65e7/(1.0e4*_grad_potential[_qp].size()+1.0))*_velocity_coeff[_qp]/(1.0e4)*1.0e4*_grad_potential[_qp].size()*_u[_qp];
}

Real
IonizationSource::computeQpJacobian()
{
  return -_test[_i][_qp]*_ionization_coeff*std::exp(-1.65e7/(1.0e4*_grad_potential[_qp].size()+1.0))*_velocity_coeff[_qp]/(1.0e4)*1.0e4*_grad_potential[_qp].size()*_phi[_j][_qp];
}

Real
IonizationSource::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id)
  {
    return _test[_i][_qp]*_ionization_coeff*_velocity_coeff[_qp]/(1.0e4)*_u[_qp]*1.0e4*_grad_potential[_qp]*_grad_phi[_j][_qp]*std::exp(-1.65e7/(1.0e4*_grad_potential[_qp].size()+1.0))*(1.65e7/(_grad_potential[_qp]*_grad_potential[_qp]*1.0e8+1.0)-1.0/(1.0e4*_grad_potential[_qp].size()+1.0));
  }
  
  return 0.0;
}
