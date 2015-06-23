#include "PhysicalElectronEnergyBC.h"

template<>
InputParameters validParams<PhysicalElectronEnergyBC>()
{
    InputParameters params = validParams<IntegratedBC>();
    params.addRequiredCoupledVar("potential", "The gradient of the potential will be used to compute the advection velocity.");
    params.addRequiredCoupledVar("em","The electron density");    
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
  _grad_potential(coupledGradient("potential")),
  _em_id(coupled("em")),
  _em(coupledValue("em"))
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

    return _test[_i][_qp]*2.5*_u[_qp]*(_a*_advection_velocity*_normals[_qp]*_em[_qp]+0.25*_v_thermal_em[_qp]*_em[_qp]);
    //return _test[_i][_qp]*2.5*_u[_qp]*(_a*_advection_velocity*_normals[_qp]*_em[_qp]);
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

    return _test[_i][_qp]*2.5*_phi[_j][_qp]*(_a*_advection_velocity*_normals[_qp]*_em[_qp]+0.25*_v_thermal_em[_qp]*_em[_qp]);
    //return _test[_i][_qp]*2.5*_phi[_j][_qp]*(_a*_advection_velocity*_normals[_qp]*_em[_qp]);
} 

Real
PhysicalElectronEnergyBC::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id)
    {
      _advection_velocity = _advection_coeff[_qp]*-_grad_potential[_qp];
      if ( _normals[_qp]*_advection_velocity > 0.0) {
	_a = 1.0;
      }
      else {
	_a = 0.0;
      }
      return _test[_i][_qp]*2.5*_u[_qp]*(_a*_advection_coeff[_qp]*-_grad_phi[_j][_qp]*_normals[_qp]*_em[_qp]);
    }
  else if (jvar == _em_id)
    {
      _advection_velocity = _advection_coeff[_qp]*-_grad_potential[_qp];
      if ( _normals[_qp]*_advection_velocity > 0.0) {
	_a = 1.0;
      }
      else {
	_a = 0.0;
      }
            return _test[_i][_qp]*2.5*_u[_qp]*(_a*_advection_velocity*_normals[_qp]*_phi[_j][_qp]+0.25*_v_thermal_em[_qp]*_phi[_j][_qp]);
	    //return _test[_i][_qp]*2.5*_u[_qp]*(_a*_advection_velocity*_normals[_qp]*_phi[_j][_qp]);
    }
  else
    {
      return 0.0;
    }
}

