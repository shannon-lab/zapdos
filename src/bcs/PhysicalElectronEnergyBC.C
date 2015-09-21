#include "PhysicalElectronEnergyBC.h"

template<>
InputParameters validParams<PhysicalElectronEnergyBC>()
{
    InputParameters params = validParams<IntegratedBC>();
    params.addRequiredCoupledVar("potential", "The gradient of the potential will be used to compute the advection velocity.");
    // params.addRequiredCoupledVar("em","The electron density");    
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

  _muel(getMaterialProperty<Real>("muel")),
  _mem(getMaterialProperty<Real>("mem")),
  _a(0.0),
  _b(0.0),

// Coupled Variables

  // _Arp(coupledValue("Arp")),
  // _grad_Arp(coupledGradient("Arp")),
  _grad_potential(coupledGradient("potential")),
  _potential_id(coupled("potential"))
  // _em(coupledValue("em"))
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

  return _test[_i][_qp]*_a*-_muel[_qp]*-_grad_potential[_qp]*std::exp(_u[_qp])*_normals[_qp];
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

  return _test[_i][_qp]*_a*-_muel[_qp]*-_grad_potential[_qp]*std::exp(_u[_qp])*_phi[_j][_qp]*_normals[_qp];
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

      return _test[_i][_qp]*_a*-_muel[_qp]*-_grad_phi[_j][_qp]*std::exp(_u[_qp])*_normals[_qp];
    }
  else {
    return 0.0;
  }
}
