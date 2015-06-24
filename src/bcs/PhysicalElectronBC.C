#include "PhysicalElectronBC.h"

template<>
InputParameters validParams<PhysicalElectronBC>()
{
    InputParameters params = validParams<IntegratedBC>();
    params.addParam<Real>("reflection_coeff",0.0,"The reflection coefficient for electrons at the walls.");
    params.addParam<Real>("se_coeff",0.1,"The secondary electron emission coefficient for the walls.");
    params.addRequiredCoupledVar("ip","The ion density");
    params.addRequiredParam<std::string>("coupled_ion_name","Though redundant, this parameter determines correct mobility and diffusivity for the ions.");
    params.addRequiredCoupledVar("Te","The electron temperature");
    params.addRequiredCoupledVar("potential","The electric potential");
    return params;
}

PhysicalElectronBC::PhysicalElectronBC(const std::string & name, InputParameters parameters) :
  IntegratedBC(name, parameters),

  // Parameters

  _reflection_coeff(getParam<Real>("reflection_coeff")),
  _se_coeff(getParam<Real>("se_coeff")),

  // Variables unique to class

  _a(0.0),
  _d_vthermal_em_d_Te(0.0),

  // Material Properties

  _muem(getMaterialProperty<Real>("muem")),
  _muip(getMaterialProperty<Real>("mu"+getParam<std::string>("coupled_ion_name"))),
  _D_ip(getMaterialProperty<Real>("D_"+getParam<std::string>("coupled_ion_name"))),
  _e(getMaterialProperty<Real>("e")),
  _m_em(getMaterialProperty<Real>("m_em")),
  _blahzie(getMaterialProperty<Real>("blahzie")),

// Coupled Variables

  _ip(coupledValue("ip")),
  _ip_id(coupled("ip")),
  _grad_ip(coupledGradient("ip")),
  _Te(coupledValue("Te")),
  _Te_id(coupled("Te")),
  _grad_potential(coupledGradient("potential")),
  _potential_id(coupled("potential"))
{}

Real
PhysicalElectronBC::computeQpResidual()
{
  if ( _normals[_qp]*-1.0*-_grad_potential[_qp] > 0.0) {
    _a = 1.0;
  }
  else {
    _a = 0.0;
  }
  //  return _test[_i][_qp]*(_a*-_muem[_qp]*-_grad_potential[_qp]*_normals[_qp]*std::max(0.0,_u[_qp])+0.25*1.6*std::sqrt(_e[_qp]*std::max(_Te[_qp],0.0)/_m_em[_qp])*std::max(0.0,_u[_qp])-_se_coeff*(_muip[_qp]*-_grad_potential[_qp]*_ip[_qp]-_D_ip[_qp]*_grad_ip[_qp])*_normals[_qp]);
    //return _test[_i][_qp]*(_a*-_muem[_qp]*-_grad_potential[_qp]*_normals[_qp]*std::max(0.0,_u[_qp])-_se_coeff*(_muip[_qp]*-_grad_potential[_qp]*_ip[_qp])*_normals[_qp]);
  return _test[_i][_qp]*(0.25*1.6*std::sqrt(_e[_qp]*std::max(_Te[_qp],0.0)/_m_em[_qp])*std::max(0.0,_u[_qp])-_se_coeff*(_muip[_qp]*-_grad_potential[_qp]*_ip[_qp]-_D_ip[_qp]*_grad_ip[_qp])*_normals[_qp]);
}

Real
PhysicalElectronBC::computeQpJacobian()
{
  if ( _normals[_qp]*-1.0*-_grad_potential[_qp] > 0.0) {
    _a = 1.0;
  }
  else {
    _a = 0.0;
  }

  //  return _test[_i][_qp]*(_a*-_muem[_qp]*-_grad_potential[_qp]*_normals[_qp]*_phi[_j][_qp]+0.25*1.6*std::sqrt(_e[_qp]*std::max(_Te[_qp],0.0)/_m_em[_qp])*_phi[_j][_qp]);
    //return _test[_i][_qp]*(_a*-_muem[_qp]*-_grad_potential[_qp]*_normals[_qp]*_phi[_j][_qp]);
  return _test[_i][_qp]*(0.25*1.6*std::sqrt(_e[_qp]*std::max(_Te[_qp],0.0)/_m_em[_qp])*_phi[_j][_qp]);
} 

Real
PhysicalElectronBC::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id) {
    if ( _normals[_qp]*-1.0*-_grad_potential[_qp] > 0.0) {
      _a = 1.0;
    }
    else {
      _a = 0.0;
    }
    //    return _test[_i][_qp]*(_a*-_muem[_qp]*-_grad_phi[_j][_qp]*_normals[_qp]*std::max(0.0,_u[_qp])-_se_coeff*(_muip[_qp]*-_grad_phi[_j][_qp]*_ip[_qp])*_normals[_qp]);
    return _test[_i][_qp]*(-_se_coeff*(_muip[_qp]*-_grad_phi[_j][_qp]*_ip[_qp])*_normals[_qp]);
  }
  else if (jvar == _ip_id) {
    if ( _normals[_qp]*-1.0*-_grad_potential[_qp] > 0.0) {
      _a = 1.0;
    }
    else {
      _a = 0.0;
    }
        return _test[_i][_qp]*(-_se_coeff*(_muip[_qp]*-_grad_potential[_qp]*_phi[_j][_qp]-_D_ip[_qp]*_grad_phi[_j][_qp])*_normals[_qp]);
	//return _test[_i][_qp]*(-_se_coeff*(_muip[_qp]*-_grad_potential[_qp]*_phi[_j][_qp])*_normals[_qp]);
  }
  else if (jvar == _Te_id) {
    if ( _normals[_qp]*-1.0*-_grad_potential[_qp] > 0.0) {
      _a = 1.0;
    }
    else {
      _a = 0.0;
    }
    _d_vthermal_em_d_Te = 0.8*std::sqrt(_e[_qp]*std::max(_Te[_qp],0.0)/_m_em[_qp])/std::max(_Te[_qp],1e-16);
        return _test[_i][_qp]*(0.25*_d_vthermal_em_d_Te*_phi[_j][_qp]*std::max(0.0,_u[_qp]));
	//return 0.0;
  }
  else {
    return 0.0;
  }
}
