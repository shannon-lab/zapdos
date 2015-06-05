#include "PhysicalElectronBC.h"

template<>
InputParameters validParams<PhysicalElectronBC>()
{
    InputParameters params = validParams<IntegratedBC>();
    params.addParam<Real>("reflection_coeff",0.0,"The reflection coefficient for electrons at the walls.");
    params.addParam<Real>("se_coeff",0.1,"The secondary electron emission coefficient for the walls.");
    params.addRequiredCoupledVar("ip","The ion density");
    return params;
}

PhysicalElectronBC::PhysicalElectronBC(const std::string & name, InputParameters parameters) :
  IntegratedBC(name, parameters),

  // Parameters

  _reflection_coeff(getParam<Real>("reflection_coeff")),
  _se_coeff(getParam<Real>("se_coeff")),

  // Variables unique to class

  _a(0.0),
  _a_p(0.0),
  _n_gamma(0.0),

  // Material Properties

  _advection_velocity_em(getMaterialProperty<RealVectorValue>("advection_velocity_em")),
  _muem(getMaterialProperty<Real>("muem")),
  _v_thermal_em(getMaterialProperty<Real>("v_thermal_em")),
  _gamma_ip(getMaterialProperty<RealVectorValue>("gamma_ip")),
  _advection_velocity_ip(getMaterialProperty<RealVectorValue>("advection_velocity_ip")),
  _muip(getMaterialProperty<Real>("muip")),

// Coupled Variables

  _ip(coupledValue("ip"))
{}

Real
PhysicalElectronBC::computeQpResidual()
{
  if ( _normals[_qp]*_advection_velocity_em[_qp] > 0.0) {
    _a = 1.0;
  }
  else {
    _a = 0.0;
  }
//  if ( _normals[_qp]*_advection_velocity_ip[_qp] > 0.0) {
//    _a_p = 1.0;
//  }
//  else {
//    _a_p = 0.0;
//  }
//  _n_gamma = (_a-1.0)*_se_coeff*_gamma_ip[_qp]*_normals[_qp]/(_advection_velocity_em[_qp]*_normals[_qp]);
//  _n_gamma = std::max(0.0,(1.0-_a)/std::abs(_muem[_qp])*_se_coeff*((2.0*_a_p-1.0)+0.5*std::sqrt(2.0/3.14))*_muip[_qp]*std::max(0.0,_ip[_qp]));
//  return _test[_i][_qp]*(1.0-_reflection_coeff)/(1.0+_reflection_coeff)*((2.0*_a-1.0)*_advection_velocity_em[_qp]*_normals[_qp]*_u[_qp]+0.5*_v_thermal_em[_qp]*_u[_qp]-0.5*_v_thermal_em[_qp]*_n_gamma)+_test[_i][_qp]*-2.0/(1.0+_reflection_coeff)*(1.0-_a)*_se_coeff*_gamma_ip[_qp]*_normals[_qp];

  return _test[_i][_qp]*(_a*_advection_velocity_em[_qp]*_normals[_qp]*std::max(0.0,_u[_qp])+0.25*_v_thermal_em[_qp]*std::max(0.0,_u[_qp]));
}

Real
PhysicalElectronBC::computeQpJacobian()
{
  if ( _normals[_qp]*_advection_velocity_em[_qp] > 0.0) {
    _a = 1.0;
  }
  else {
    _a = 0.0;
  }
  //  return _test[_i][_qp]*(1.0-_reflection_coeff)/(1.0+_reflection_coeff)*((2.0*_a-1.0)*_advection_velocity_em[_qp]*_normals[_qp]*_phi[_j][_qp]+0.5*_v_thermal_em[_qp]*_phi[_j][_qp]);

  return _test[_i][_qp]*(_a*_advection_velocity_em[_qp]*_normals[_qp]*_phi[_j][_qp]+0.25*_v_thermal_em[_qp]*_phi[_j][_qp]);
} 
