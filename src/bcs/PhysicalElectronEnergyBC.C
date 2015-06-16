#include "PhysicalElectronEnergyBC.h"

template<>
InputParameters validParams<PhysicalElectronEnergyBC>()
{
    InputParameters params = validParams<IntegratedBC>();
    params.addRequiredCoupledVar("potential", "The gradient of the potential will be used to compute the advection velocity.");
    return params;
}

PhysicalElectronEnergyBC::PhysicalElectronEnergyBC(const std::string & name, InputParameters parameters) :
  IntegratedBC(name, parameters),

  // Parameters

  // Variables unique to class

  _a(0.0),
  _advection_velocity(0.0,0.0,0.0),

  // Material Properties

  _v_thermal_em(getMaterialProperty<Real>("v_thermal_em")),
  _advection_coeff(getMaterialProperty<Real>("EFieldAdvectionCoeff_em")),
  
// Coupled Variables

  _potential_id(coupled("potential")),
  _grad_potential(coupledGradient("potential"))

{}

Real
PhysicalElectronEnergyBC::computeQpResidual()
{
  _advection_velocity = _advection_coeff[_qp]*-_grad_potential[_qp];

  if ( _normals[_qp]*_advection_velocity > 0.0) {
    _a = 1.0;
  }
  else {
    _a = 0.0;
  }

  return _test[_i][_qp]*(_a*_advection_velocity*_normals[_qp]*_u[_qp]+5.0/6.0*_v_thermal_em[_qp]*_u[_qp]);
}

Real
PhysicalElectronEnergyBC::computeQpJacobian()
{
  _advection_velocity = _advection_coeff[_qp]*-_grad_potential[_qp];

  if ( _normals[_qp]*_advection_velocity > 0.0) {
    _a = 1.0;
  }
  else {
    _a = 0.0;
  }

  return _test[_i][_qp]*(_a*_advection_velocity*_normals[_qp]*_phi[_j][_qp]+5.0/6.0*_v_thermal_em[_qp]*_phi[_j][_qp]);
} 

Real
PhysicalElectronEnergyBC::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id)
  {
    if ( _normals[_qp]*_advection_velocity > 0.0) {
      _a = 1.0;
    }
    else {
      _a = 0.0;
    }
    return _test[_i][_qp]*(_a*_advection_coeff[_qp]*-_grad_phi[_j][_qp]*_normals[_qp]*_u[_qp]);
  }
  else
    {
      return 0.0;
    }
}

