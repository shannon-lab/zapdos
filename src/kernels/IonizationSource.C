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
//#include "math.h"

template<>
InputParameters validParams<IonizationSource>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("potential", "The electrical potential");
  return params;
}

IonizationSource::IonizationSource(const InputParameters & parameters) :
    Kernel(parameters),
    
    // Material properties

    _velocity(getMaterialProperty<RealVectorValue>("velocity")),

    /*    _ionization_coeff(getMaterialProperty<Real>("ionization_coeff")),
    _velocity_coeff(getMaterialProperty<Real>("velocity_coeff")),
    _ion_activation_energy(getMaterialProperty<Real>("ion_activation_energy")),
    _potential_mult(getMaterialProperty<Real>("potential_mult")), */
    
    // Coupled variables
    
    _potential_id(coupled("potential")),
    _grad_potential(coupledGradient("potential"))
{}

/* Scaling potential such that variable magnitudes are on the same order of magnitude.
This scaling is evident anywhere where you see the potential multiplied by _potential_mult[_qp] */

Real
IonizationSource::computeQpResidual()
{
  /* return -_test[_i][_qp]*_ionization_coeff[_qp]*std::exp(-_ion_activation_energy[_qp]/(_potential_mult[_qp]*_grad_potential[_qp].size()+1.0))*_velocity_coeff[_qp]*_potential_mult[_qp]*_grad_potential[_qp].size()*_u[_qp]; */
  return -_test[_i][_qp]*std::max(std::exp(-1.0/(_grad_potential[_qp].size()+1.0e-6))*_velocity[_qp].size()*_u[_qp],0.0);
}

Real
IonizationSource::computeQpJacobian()
{
  /* return -_test[_i][_qp]*_ionization_coeff[_qp]*std::exp(-_ion_activation_energy[_qp]/(_potential_mult[_qp]*_grad_potential[_qp].size()+1.0))*_velocity_coeff[_qp]*_potential_mult[_qp]*_grad_potential[_qp].size()*_phi[_j][_qp]; */
  return -_test[_i][_qp]*std::exp(-1.0/(_grad_potential[_qp].size()+1.0e-6))*_velocity[_qp].size()*_phi[_j][_qp];
}

/* Real
IonizationSource::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id)
  {
    return _test[_i][_qp]*_ionization_coeff[_qp]*_velocity_coeff[_qp]*_u[_qp]*_potential_mult[_qp]*_grad_potential[_qp]*_grad_phi[_j][_qp]*std::exp(-_ion_activation_energy[_qp]/(_potential_mult[_qp]*_grad_potential[_qp].size()+1.0))*(_ion_activation_energy[_qp]/(_grad_potential[_qp]*_grad_potential[_qp]*std::pow(_potential_mult[_qp],2)+1.0)-1.0/(_potential_mult[_qp]*_grad_potential[_qp].size()+1.0));
  }
  
  return 0.0;
} */
