#include "PhysicalElectronEnergyBC.h"

template<>
InputParameters validParams<PhysicalElectronEnergyBC>()
{
    InputParameters params = validParams<IntegratedBC>();
    params.addRequiredCoupledVar("potential", "The gradient of the potential will be used to compute the advection velocity.");
    params.addRequiredCoupledVar("em","The electron density");    
    params.addRequiredCoupledVar("Arp","The ion density");
    //    params.addRequiredParam<std::string>("coupled_ion_name","Though redundant, this parameter determines correct mobility and diffusivity for the ions.");
    params.addParam<Real>("se_energy",4.0,"The energy of electrons emitted from the walls by ion bombardment.");
    params.addParam<Real>("se_coeff",0.1,"The fraction of incident ions that produce secondary electrons.");
    return params;
}

PhysicalElectronEnergyBC::PhysicalElectronEnergyBC(const std::string & name, InputParameters parameters) :
  IntegratedBC(name, parameters),

  // Parameters

  _se_energy(getParam<Real>("se_energy")),
  _se_coeff(getParam<Real>("se_coeff")),

  // Variables unique to class

  _a(0.0),
  //  _advection_velocity(0.0,0.0,0.0),
  //  _v_thermal_em(0.0),
  //  _d_v_thermal_em_d_Te(0.0),

  // Material Properties

  _e(getMaterialProperty<Real>("e")),
  _mem(getMaterialProperty<Real>("m_em")),
  _muArp(getMaterialProperty<Real>("muArp")),
  _muem(getMaterialProperty<Real>("muem")),
  _muel(getMaterialProperty<Real>("muel")),
  _tc(getMaterialProperty<Real>("tc")),
  _Vc(getMaterialProperty<Real>("Vc")),
  _rc(getMaterialProperty<Real>("rc")),
  _Tec(getMaterialProperty<Real>("Tec")),
  _k_boltz(getMaterialProperty<Real>("k_boltz")),
  _T_gas(getMaterialProperty<Real>("T_gas")),
  //  _muArp(getMaterialProperty<Real>("mu"+getParam<std::string>("coupled_ion_name"))),
  //  _D_Arp(getMaterialProperty<Real>("D_"+getParam<std::string>("coupled_ion_name"))),
  
// Coupled Variables

  _Arp(coupledValue("Arp")),
  _grad_Arp(coupledGradient("Arp")),
  _grad_potential(coupledGradient("potential")),
  _em(coupledValue("em"))
  /*  _Arp_id(coupled("Arp")),
  _potential_id(coupled("potential")),
  _em_id(coupled("em")),*/
{}

Real
PhysicalElectronEnergyBC::computeQpResidual()
{

  if ( _normals[_qp]*-_muem[_qp]*-_grad_potential[_qp] > 0.0) {
    _a = 1.0;
  }
  else {
    _a = 0.0;
  }

  return _tc[_qp]*_test[_i][_qp]*1.5*std::max(_u[_qp],0.0)*(_a*-_muel[_qp]*-_grad_potential[_qp]*_Vc[_qp]/_rc[_qp]*_normals[_qp]*std::max(_em[_qp],0.0))+_tc[_qp]*_test[_i][_qp]*-_se_coeff*_se_energy/_Tec[_qp]*(_muArp[_qp]*-_grad_potential[_qp]*_Vc[_qp]/_rc[_qp]*std::max(_Arp[_qp],0.0)-_muArp[_qp]*_k_boltz[_qp]*_T_gas[_qp]/_e[_qp]*_grad_Arp[_qp]/_rc[_qp])*_normals[_qp];

  //return _test[_i][_qp]*2.5*_u[_qp]*(0.25*_v_thermal_em*_em[_qp])+_test[_i][_qp]*-_se_coeff*_se_energy*(_muArp[_qp]*-_grad_potential[_qp]*_Arp[_qp]-_D_Arp[_qp]*_grad_Arp[_qp])*_normals[_qp];
}

/*Real
PhysicalElectronEnergyBC::computeQpJacobian()
{
  _advection_velocity = _advection_coeff[_qp]*-_grad_potential[_qp];
  _v_thermal_em = 1.6*std::sqrt(_e[_qp]*std::max(_u[_qp],0.0)/_m_em[_qp]);
  _d_v_thermal_em_d_Te = 0.8*std::sqrt(_e[_qp]*std::max(_u[_qp],0.0)/_m_em[_qp])/std::max(_u[_qp],1e-16);

  if ( _normals[_qp]*_advection_velocity > 0.0) {
    _a = 1.0;
  }
  else {
    _a = 0.0;
  }

  //  return _test[_i][_qp]*2.5*_phi[_j][_qp]*(_a*_advection_velocity*_normals[_qp]*_em[_qp]+0.25*_v_thermal_em*_em[_qp])+_test[_i][_qp]*2.5*_u[_qp]*(0.25*_d_v_thermal_em_d_Te*_phi[_j][_qp]*_em[_qp]);
    return _test[_i][_qp]*2.5*_phi[_j][_qp]*(_a*_advection_velocity*_normals[_qp]*_em[_qp]);
  //  return _test[_i][_qp]*2.5*_phi[_j][_qp]*(0.25*_v_thermal_em*_em[_qp])+_test[_i][_qp]*2.5*_u[_qp]*(0.25*_d_v_thermal_em_d_Te*_phi[_j][_qp]*_em[_qp]);
} 

Real
PhysicalElectronEnergyBC::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id)
    {
      _advection_velocity = _advection_coeff[_qp]*-_grad_potential[_qp];
      _v_thermal_em = 1.6*std::sqrt(_e[_qp]*std::max(_u[_qp],0.0)/_m_em[_qp]);

      if ( _normals[_qp]*_advection_velocity > 0.0) {
	_a = 1.0;
      }
      else {
	_a = 0.0;
      }
      //      return _test[_i][_qp]*2.5*_u[_qp]*(_a*_advection_coeff[_qp]*-_grad_phi[_j][_qp]*_normals[_qp]*_em[_qp]);
      return 0.0;
    }
  else if (jvar == _em_id)
    {
      _advection_velocity = _advection_coeff[_qp]*-_grad_potential[_qp];
      _v_thermal_em = 1.6*std::sqrt(_e[_qp]*std::max(_u[_qp],0.0)/_m_em[_qp]);
      if ( _normals[_qp]*_advection_velocity > 0.0) {
	_a = 1.0;
      }
      else {
	_a = 0.0;
      }
      //      return _test[_i][_qp]*2.5*_u[_qp]*(_a*_advection_velocity*_normals[_qp]*_phi[_j][_qp]+0.25*_v_thermal_em*_phi[_j][_qp]);
	    //return _test[_i][_qp]*2.5*_u[_qp]*(_a*_advection_velocity*_normals[_qp]*_phi[_j][_qp]);
      return _test[_i][_qp]*2.5*_u[_qp]*(0.25*_v_thermal_em*_phi[_j][_qp]);
    }
  else if (jvar == _Arp_id)
    {
      _advection_velocity = _advection_coeff[_qp]*-_grad_potential[_qp];
      _v_thermal_em = 1.6*std::sqrt(_e[_qp]*std::max(_u[_qp],0.0)/_m_em[_qp]);
      if ( _normals[_qp]*_advection_velocity > 0.0) {
	_a = 1.0;
      }
      else {
	_a = 0.0;
      }
      //      return _test[_i][_qp]*2.5*_u[_qp]*(_a*_advection_velocity*_normals[_qp]*_phi[_j][_qp]+0.25*_v_thermal_em*_phi[_j][_qp]);
	    //return _test[_i][_qp]*2.5*_u[_qp]*(_a*_advection_velocity*_normals[_qp]*_phi[_j][_qp]);
      return _test[_i][_qp]*-_se_coeff*_se_energy*(_muArp[_qp]*-_grad_potential[_qp]*_phi[_j][_qp]-_D_Arp[_qp]*_grad_phi[_j][_qp])*_normals[_qp];
    }

  else
    {
      return 0.0;
    }
}*/
