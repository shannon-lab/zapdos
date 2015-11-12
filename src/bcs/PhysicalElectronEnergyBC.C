#include "PhysicalElectronEnergyBC.h"

template<>
InputParameters validParams<PhysicalElectronEnergyBC>()
{
    InputParameters params = validParams<IntegratedBC>();
    params.addRequiredCoupledVar("potential", "The gradient of the potential will be used to compute the advection velocity.");
    params.addRequiredCoupledVar("em","The electron density");    
    // params.addRequiredCoupledVar("Arp","The ion density");
    //    params.addRequiredParam<std::string>("coupled_ion_name","Though redundant, this parameter determines correct mobility and diffusivity for the ions.");
    // params.addParam<Real>("se_energy",4.0,"The energy of electrons emitted from the walls by ion bombardment.");
    // params.addParam<Real>("se_coeff",0.1,"The fraction of incident ions that produce secondary electrons.");
    return params;
}

PhysicalElectronEnergyBC::PhysicalElectronEnergyBC(const InputParameters & parameters) :
  IntegratedBC(parameters),

  // Parameters

  // _se_energy(getParam<Real>("se_energy")),
  // _se_coeff(getParam<Real>("se_coeff")),

  _mumean_en(getMaterialProperty<Real>("mumean_en")),
  _d_mumean_en_d_actual_mean_en(getMaterialProperty<Real>("d_mumean_en_d_actual_mean_en")),
  _mem(getMaterialProperty<Real>("mem")),
  _a(0.0),
  _b(0.0),

// Coupled Variables

  // _Arp(coupledValue("Arp")),
  // _grad_Arp(coupledGradient("Arp")),
  _grad_potential(coupledGradient("potential")),
  _potential_id(coupled("potential")),
  _em(coupledValue("em")),
  _em_id(coupled("em"))
{}

Real
PhysicalElectronEnergyBC::computeQpResidual()
{

  if ( _normals[_qp]*-1.0*-_grad_potential[_qp] > 0.0) {
    _a = 1.0;
    // _b = 0.0;
  }
  else {
    _a = 0.0;
    // _b = 1.0;
  }

  return _test[_i][_qp]*_a*-_mumean_en[_qp]*-_grad_potential[_qp]*std::exp(_u[_qp])*_normals[_qp];
         // + _test[_i][_qp]*_b*5.0/6*1.6*std::sqrt(_e*2.0/3*std::exp(_u[_qp]-_em[_qp])/_m_el)*std::exp(_u[_qp]);
}

Real
PhysicalElectronEnergyBC::computeQpJacobian()
{
  if ( _normals[_qp]*-1.0*-_grad_potential[_qp] > 0.0) {
    _a = 1.0;
    // _b = 0.0;
  }
  else {
    _a = 0.0;
    // _b = 1.0;
  }
  
  Real _actual_mean_en = std::exp(_u[_qp]-_em[_qp]);
  Real _d_actual_mean_en_d_mean_en = _actual_mean_en*_phi[_j][_qp];
  Real _d_mumean_en_d_mean_en = _d_mumean_en_d_actual_mean_en[_qp] * _d_actual_mean_en_d_mean_en;

  return _test[_i][_qp]*_a*-_mumean_en[_qp]*-_grad_potential[_qp]*std::exp(_u[_qp])*_phi[_j][_qp]*_normals[_qp]
    + _test[_i][_qp]*_a*-_d_mumean_en_d_mean_en*-_grad_potential[_qp]*std::exp(_u[_qp])*_normals[_qp];
         // + _test[_i][_qp]*_b*5.0/6*1.6*(std::sqrt(_e*2.0/3*std::exp(_u[_qp]-_em[_qp])/_m_el)*std::exp(_u[_qp])*_phi[_j][_qp] + std::exp(_u[_qp])*0.408248*std::sqrt(_e*std::exp(_u[_qp]-_em[_qp])/_m_el)*_phi[_j][_qp]);
}

Real
PhysicalElectronEnergyBC::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id)
    {
      if ( _normals[_qp]*-1.0*-_grad_potential[_qp] > 0.0) {
      	_a = 1.0;
      	// _b = 0.0;
      }
      else {
      	_a = 0.0;
      	// _b = 1.0;
      }

      return _test[_i][_qp]*_a*-_mumean_en[_qp]*-_grad_phi[_j][_qp]*std::exp(_u[_qp])*_normals[_qp];
    }
  else if (jvar == _em_id) {
    Real _actual_mean_en = std::exp(_u[_qp]-_em[_qp]);
    Real _d_actual_mean_en_d_em = -_actual_mean_en*_phi[_j][_qp];
    Real _d_mumean_en_d_em = _d_mumean_en_d_actual_mean_en[_qp] * _d_actual_mean_en_d_em;
    if ( _normals[_qp]*-1.0*-_grad_potential[_qp] > 0.0) {
      _a = 1.0;
    }
    else {
      _a = 0.0;
    }

    return _test[_i][_qp]*_a*-_d_mumean_en_d_em*-_grad_potential[_qp]*std::exp(_u[_qp])*_normals[_qp];
  }

  else {
    return 0.0;
  }
}
