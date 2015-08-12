#include "RFElectronBC.h"

template<>
InputParameters validParams<RFElectronBC>()
{
    InputParameters params = validParams<IntegratedBC>();
    params.addRequiredCoupledVar("Arp","The ion density");
    params.addRequiredCoupledVar("potential","The electric potential");
    return params;
}

RFElectronBC::RFElectronBC(const std::string & name, InputParameters parameters) :
  IntegratedBC(name, parameters),

  _muem(getMaterialProperty<Real>("muem")),
  _mem(getMaterialProperty<Real>("mem")),
  _se_coeff(getMaterialProperty<Real>("se_coeff")),
  _muip(getMaterialProperty<Real>("muip")),
  _vthermal_em(getMaterialProperty<Real>("vthermal_em")),
  _a(0.0),
  _b(0.0),

// Coupled Variables

  _Arp(coupledValue("Arp")),
  _Arp_id(coupled("Arp")),
  _grad_Arp(coupledGradient("Arp")),
  _grad_potential(coupledGradient("potential")),
  _potential_id(coupled("potential"))
{}

Real
RFElectronBC::computeQpResidual()
{
  if ( _normals[_qp]*-1.0*-_grad_potential[_qp] > 0.0) {
    _a = 1.0;
    _b = 0.0;
  }
  else {
    _a = 0.0;
    _b = 1.0;
  }
  return _test[_i][_qp]*(_a*-_muem[_qp]*-_grad_potential[_qp]*std::exp(_u[_qp])*_normals[_qp]
			 -_b*_se_coeff[_qp]*_muip[_qp]*-_grad_potential[_qp]*std::exp(_Arp[_qp])*_normals[_qp] + 0.5*_vthermal_em[_qp]*std::exp(_u[_qp]));
}

Real
RFElectronBC::computeQpJacobian()
{
  if ( _normals[_qp]*-1.0*-_grad_potential[_qp] > 0.0) {
    _a = 1.0;
  }
  else {
    _a = 0.0;
  }
  return _test[_i][_qp]*(_a*-_muem[_qp]*-_grad_potential[_qp]*std::exp(_u[_qp])*_phi[_j][_qp]*_normals[_qp] + 0.5*_vthermal_em[_qp]*std::exp(_u[_qp])*_phi[_j][_qp]);
}

Real
RFElectronBC::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id) {
    if ( _normals[_qp]*-1.0*-_grad_potential[_qp] > 0.0) {
      _a = 1.0;
      _b = 0.0;
    }
    else {
      _a = 0.0;
      _b = 1.0;
    }
    return _test[_i][_qp]*(_a*-_muem[_qp]*-_grad_phi[_j][_qp]*std::exp(_u[_qp])*_normals[_qp]
			  -_b*_se_coeff[_qp]*_muip[_qp]*-_grad_phi[_j][_qp]*std::exp(_Arp[_qp])*_normals[_qp]);
  }

  else if (jvar == _Arp_id) {
    if ( _normals[_qp]*-1.0*-_grad_potential[_qp] > 0.0) {
      _b = 0.0;
    }
    else {
      _b = 1.0;
    }
    return _test[_i][_qp]*(-_b*_se_coeff[_qp]*_muip[_qp]*-_grad_potential[_qp]*std::exp(_Arp[_qp])*_phi[_j][_qp]*_normals[_qp]);
  }

  else {
    return 0.0;
  }
}
