#include "PhysicalElectronBC.h"

template<>
InputParameters validParams<PhysicalElectronBC>()
{
    InputParameters params = validParams<IntegratedBC>();
    params.addParam<Real>("reflection_coeff",0.0,"The reflection coefficient for electrons at the walls.");
    params.addParam<Real>("se_coeff",0.1,"The secondary electron emission coefficient for the walls.");
    params.addRequiredCoupledVar("Arp","The ion density");
    //    params.addRequiredParam<std::string>("coupled_ion_name","Though redundant, this parameter determines correct mobility and diffusivity for the ions.");
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
  //  _d_vthermal_em_d_Te(0.0),

  // Material Properties

  _muem(getMaterialProperty<Real>("muem")),
  _muArp(getMaterialProperty<Real>("muArp")),
  _e(getMaterialProperty<Real>("e")),
  _mem(getMaterialProperty<Real>("m_em")),
  _tc(getMaterialProperty<Real>("tc")),
  _Vc(getMaterialProperty<Real>("Vc")),
  _rc(getMaterialProperty<Real>("rc")),
  //  _muArp(getMaterialProperty<Real>("mu"+getParam<std::string>("coupled_ion_name"))),
  //  _D_Arp(getMaterialProperty<Real>("D_"+getParam<std::string>("coupled_ion_name"))),

// Coupled Variables

  _Arp(coupledValue("Arp")),
  _grad_Arp(coupledGradient("Arp")),
  _Te(coupledValue("Te")),
  _grad_potential(coupledGradient("potential"))
  //  _Arp_id(coupled("Arp")),
  //  _Te_id(coupled("Te")),
  //  _potential_id(coupled("potential"))
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
  return _test[_i][_qp]*(_tc[_qp]*_a*-_muem[_qp]*-_grad_potential[_qp]*_Vc[_qp]/_rc[_qp]*_normals[_qp]*std::max(_u[_qp],0.0)-_se_coeff*(_tc[_qp]*_muArp[_qp]*-_grad_potential[_qp]*_Vc[_qp]/_rc[_qp]*std::max(_Arp[_qp],0.0))*_normals[_qp]);

  //  return _test[_i][_qp]*(_a*-_muem[_qp]*-_grad_potential[_qp]*_normals[_qp]*std::max(0.0,_u[_qp])+0.25*1.6*std::sqrt(_e[_qp]*std::max(_Te[_qp],0.0)/_m_em[_qp])*std::max(0.0,_u[_qp])-_se_coeff*(_muArp[_qp]*-_grad_potential[_qp]*_Arp[_qp]-_D_Arp[_qp]*_grad_Arp[_qp])*_normals[_qp]);
  //return _test[_i][_qp]*(0.25*1.6*std::sqrt(_e[_qp]*std::max(_Te[_qp],0.0)/_m_em[_qp])*std::max(0.0,_u[_qp])-_se_coeff*(_muArp[_qp]*-_grad_potential[_qp]*_Arp[_qp]-_D_Arp[_qp]*_grad_Arp[_qp])*_normals[_qp]);
}

/*Real
PhysicalElectronBC::computeQpJacobian()
{
  if ( _normals[_qp]*-1.0*-_grad_potential[_qp] > 0.0) {
    _a = 1.0;
  }
  else {
    _a = 0.0;
  }

  //  return _test[_i][_qp]*(_a*-_muem[_qp]*-_grad_potential[_qp]*_normals[_qp]*_phi[_j][_qp]+0.25*1.6*std::sqrt(_e[_qp]*std::max(_Te[_qp],0.0)/_m_em[_qp])*_phi[_j][_qp]);
  return _test[_i][_qp]*(_a*-_muem[_qp]*-_grad_potential[_qp]*_normals[_qp]*_phi[_j][_qp]);
    //  return _test[_i][_qp]*(0.25*1.6*std::sqrt(_e[_qp]*std::max(_Te[_qp],0.0)/_m_em[_qp])*_phi[_j][_qp]);
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
    return _test[_i][_qp]*(_a*-_muem[_qp]*-_grad_phi[_j][_qp]*_normals[_qp]*std::max(0.0,_u[_qp])-_se_coeff*(_muArp[_qp]*-_grad_phi[_j][_qp]*_Arp[_qp])*_normals[_qp]);
    //return _test[_i][_qp]*(-_se_coeff*(_muArp[_qp]*-_grad_phi[_j][_qp]*_Arp[_qp])*_normals[_qp]);
  }
  else if (jvar == _Arp_id) {
    if ( _normals[_qp]*-1.0*-_grad_potential[_qp] > 0.0) {
      _a = 1.0;
    }
    else {
      _a = 0.0;
    }
    return _test[_i][_qp]*(-_se_coeff*(_muArp[_qp]*-_grad_potential[_qp]*_phi[_j][_qp]-_D_Arp[_qp]*_grad_phi[_j][_qp])*_normals[_qp]);
	//return _test[_i][_qp]*(-_se_coeff*(_muArp[_qp]*-_grad_potential[_qp]*_phi[_j][_qp])*_normals[_qp]);
  }
  else if (jvar == _Te_id) {
    if ( _normals[_qp]*-1.0*-_grad_potential[_qp] > 0.0) {
      _a = 1.0;
    }
    else {
      _a = 0.0;
    }
    _d_vthermal_em_d_Te = 0.8*std::sqrt(_e[_qp]*std::max(_Te[_qp],0.0)/_m_em[_qp])/std::max(_Te[_qp],1e-16);
    //  return _test[_i][_qp]*(0.25*_d_vthermal_em_d_Te*_phi[_j][_qp]*std::max(0.0,_u[_qp]));
    return 0.0;
  }
  else {
    return 0.0;
  }
}
*/
