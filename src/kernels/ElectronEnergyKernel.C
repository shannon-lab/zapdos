#include "ElectronEnergyKernel.h"

template<>
InputParameters validParams<ElectronEnergyKernel>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredCoupledVar("em", "The electron density");
  params.addRequiredCoupledVar("potential","The electric potential");

  return params;
}

ElectronEnergyKernel::ElectronEnergyKernel(const std::string & name, InputParameters parameters) :
  Kernel(name, parameters),

  _tc(getMaterialProperty<Real>("tc")),
  _rc(getMaterialProperty<Real>("rc")),
  _Tec(getMaterialProperty<Real>("Tec")),
  _Vc(getMaterialProperty<Real>("Vc")),
  _muel(getMaterialProperty<Real>("muel")),
  _k4_const(getMaterialProperty<Real>("k4_const")),
  _k1_const(getMaterialProperty<Real>("k1_const")),
  _Ar(getMaterialProperty<Real>("Ar")),
  _mem(getMaterialProperty<Real>("mem")),
  _mAr(getMaterialProperty<Real>("mAr")),
  _muem(getMaterialProperty<Real>("muem")),

  _em(coupledValue("em")),
  _grad_em(coupledGradient("em")),
  _grad_potential(coupledGradient("potential"))
{}

ElectronEnergyKernel::~ElectronEnergyKernel()
{}

Real
ElectronEnergyKernel::computeQpResidual()
{
  return -_grad_test[_i][_qp]*(1.5*_muel[_qp]*_tc[_qp]*_Vc[_qp]/std::pow(_rc[_qp],2)*std::max(_em[_qp],0.0)*std::max(_u[_qp],0.0)*_grad_potential[_qp]-1.5*_muel[_qp]*_tc[_qp]*_Tec[_qp]/std::pow(_rc[_qp],2)*std::max(_u[_qp],0.0)*(std::max(_em[_qp],0.0)*_grad_u[_qp]+std::max(_u[_qp],0.0)*_grad_em[_qp]))+_test[_i][_qp]*-_grad_potential[_qp]*(_muem[_qp]*_tc[_qp]*std::pow(_Vc[_qp],2)/(_Tec[_qp]*std::pow(_rc[_qp],2))*std::max(_em[_qp],0.0)*_grad_potential[_qp]-_muem[_qp]*_tc[_qp]*_Vc[_qp]/std::pow(_rc[_qp],2)*std::max(_u[_qp],0.0)*_grad_em[_qp])-_test[_i][_qp]*(_k4_const[_qp]*std::exp(-15.76/(_Tec[_qp]*std::max(_u[_qp],1e-16)))*_Ar[_qp]*-15.76*_tc[_qp]/_Tec[_qp]*std::max(_em[_qp],0.0)-_k1_const[_qp]*_Ar[_qp]*3.0*_mem[_qp]/_mAr[_qp]*_tc[_qp]*std::max(_em[_qp],0.0)*std::max(_u[_qp],0.0))+_tc[_qp]*_grad_test[_i][_qp]/_rc[_qp]*_current_elem->hmax()*_rc[_qp]*_muel[_qp]*_grad_potential[_qp].size()*_Vc[_qp]/_rc[_qp]*(std::max(_em[_qp],0.0)*_grad_u[_qp]+std::max(_u[_qp],0.0)*_grad_em[_qp])/_rc[_qp];
}
