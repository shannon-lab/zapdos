#include "PhysicalIonBC.h"

template<>
InputParameters validParams<PhysicalIonBC>()
{
    InputParameters params = validParams<IntegratedBC>();
    params.addParam<Real>("reflection_coeff",0.0,"The reflection coefficient for ions at the walls.");
    params.addRequiredParam<std::string>("var_name","Though redundant, this parameter determines correct mobility and diffusivity for the ions.");
    params.addRequiredCoupledVar("potential","The electrical potential");
    return params;
}

PhysicalIonBC::PhysicalIonBC(const std::string & name, InputParameters parameters) :
  IntegratedBC(name, parameters),

  // Paramters

  _reflection_coeff(getParam<Real>("reflection_coeff")),

  // Variables unique to class

  _a(0.0),

  // Material Properties

  _muip(getMaterialProperty<Real>("mu"+getParam<std::string>("var_name"))),
  _k_boltz(getMaterialProperty<Real>("k_boltz")),
  _T_gas(getMaterialProperty<Real>("T_gas")),
  _m_ip(getMaterialProperty<Real>("m"+getParam<std::string>("var_name"))),

  // coupled variables

  _grad_potential(coupledGradient("potential")),
  _potential_id(coupled("potential"))
{}

Real
PhysicalIonBC::computeQpResidual()
{
  if ( _normals[_qp]*1.0*-_grad_potential[_qp] > 0.0) {
    _a = 1.0;
  }
  else {
    _a = 0.0;
  }

  //    return _test[_i][_qp]*(_a*_muip[_qp]*-_grad_potential[_qp]*_normals[_qp]*std::max(0.0,_u[_qp])+0.25*1.6*std::sqrt(_k_boltz[_qp]*_T_gas[_qp]/_m_ip[_qp])*std::max(0.0,_u[_qp]));
  return _test[_i][_qp]*(_a*_muip[_qp]*-_grad_potential[_qp]*_normals[_qp]*std::max(0.0,_u[_qp]));
}

Real
PhysicalIonBC::computeQpJacobian()
{
  if ( _normals[_qp]*1.0*-_grad_potential[_qp] > 0.0) {
    _a = 1.0;
  }
  else {
    _a = 0.0;
  }
  //    return _test[_i][_qp]*(_a*_muip[_qp]*-_grad_potential[_qp]*_normals[_qp]*_phi[_j][_qp]+0.25*1.6*std::sqrt(_k_boltz[_qp]*_T_gas[_qp]/_m_ip[_qp])*_phi[_j][_qp]);
  return _test[_i][_qp]*(_a*_muip[_qp]*-_grad_potential[_qp]*_normals[_qp]*_phi[_j][_qp]);
}

Real
PhysicalIonBC::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id) {
    if ( _normals[_qp]*1.0*-_grad_potential[_qp] > 0.0) {
      _a = 1.0;
    }
    else {
      _a = 0.0;
    }
    return _test[_i][_qp]*(_a*_muip[_qp]*-_grad_phi[_j][_qp]*_normals[_qp]*std::max(0.0,_u[_qp]));
  }
  else {
    return 0.0;
  }
}

  
