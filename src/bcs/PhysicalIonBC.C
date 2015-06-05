#include "PhysicalIonBC.h"

template<>
InputParameters validParams<PhysicalIonBC>()
{
    InputParameters params = validParams<IntegratedBC>();
    params.addParam<Real>("reflection_coeff",0.0,"The reflection coefficient for ions at the walls.");
    return params;
}

PhysicalIonBC::PhysicalIonBC(const std::string & name, InputParameters parameters) :
  IntegratedBC(name, parameters),

  // Paramters

  _reflection_coeff(getParam<Real>("reflection_coeff")),

  // Variables unique to class

  _a(0.0),

  // Material Properties

  _advection_velocity_ip(getMaterialProperty<RealVectorValue>("advection_velocity_ip")),
  _muip(getMaterialProperty<Real>("muip")),
  _v_thermal_ip(getMaterialProperty<Real>("v_thermal_ip"))
{}

Real
PhysicalIonBC::computeQpResidual()
{
  if ( _normals[_qp]*_advection_velocity_ip[_qp] > 0.0) {
    _a = 1.0;
  }
  else {
    _a = 0.0;
  }
  //  return _test[_i][_qp]*(1.0-_reflection_coeff)/(1.0+_reflection_coeff)*((2.0*_a-1.0)*_advection_velocity_ip[_qp]*_normals[_qp]*_u[_qp]+0.5*_v_thermal_ip[_qp]*_u[_qp]);

  return _test[_i][_qp]*(_a*_advection_velocity_ip[_qp]*_normals[_qp]*std::max(0.0,_u[_qp])+0.25*_v_thermal_ip[_qp]*std::max(0.0,_u[_qp]));
}

Real
PhysicalIonBC::computeQpJacobian()
{
  if ( _normals[_qp]*_advection_velocity_ip[_qp] > 0.0) {
    _a = 1.0;
  }
  else {
    _a = 0.0;
  }
  //  return _test[_i][_qp]*(1.0-_reflection_coeff)/(1.0+_reflection_coeff)*((2.0*_a-1.0)*_advection_velocity_ip[_qp]*_normals[_qp]*_phi[_j][_qp]+0.5*_v_thermal_ip[_qp]*_phi[_j][_qp]);

  return _test[_i][_qp]*(_a*_advection_velocity_ip[_qp]*_normals[_qp]*_phi[_j][_qp]+0.25*_v_thermal_ip[_qp]*_phi[_j][_qp]);
}
  
