#include "ArpKernel.h"

template<>
InputParameters validParams<ArpKernel>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredCoupledVar("potential", "The electric potential");
  params.addRequiredCoupledVar("em", "The electron density");
  params.addRequiredCoupledVar("Te", "The electront temperature");
  return params;
}

ArpKernel::ArpKernel(const std::string & name, InputParameters parameters) :
  Kernel(name, parameters),

  _tc(getMaterialProperty<Real>("tc")),
  _rc(getMaterialProperty<Real>("rc")),
  _Vc(getMaterialProperty<Real>("Vc")),
  _Tec(getMaterialProperty<Real>("Tec")),
  _muArp(getMaterialProperty<Real>("muArp")),
  _k4_const(getMaterialProperty<Real>("k4_const")),
  _Ar(getMaterialProperty<Real>("Ar")),
  _k_boltz(getMaterialProperty<Real>("k_boltz")),
  _e(getMaterialProperty<Real>("e")),
  _T_gas(getMaterialProperty<Real>("T_gas")),

  _em(coupledValue("em")),
  _grad_potential(coupledGradient("potential")),
  _Te(coupledValue("Te"))
{}

ArpKernel::~ArpKernel()
{}

Real
ArpKernel::computeQpResidual()
{
  return -_grad_test[_i][_qp]*(-_tc[_qp]*_Vc[_qp]*_muArp[_qp]/std::pow(_rc[_qp],2)*std::max(_u[_qp],0.0)*_grad_potential[_qp]-_muArp[_qp]*_k_boltz[_qp]*_T_gas[_qp]/_e[_qp]*_tc[_qp]/std::pow(_rc[_qp],2)*_grad_u[_qp])-_test[_i][_qp]*_tc[_qp]*_k4_const[_qp]*_Ar[_qp]*std::max(_em[_qp],0.0)*std::exp(-15.76/(_Tec[_qp]*std::max(_Te[_qp],1e-16)))+_tc[_qp]*_grad_test[_i][_qp]/_rc[_qp]*_current_elem->hmax()*_rc[_qp]*_muArp[_qp]*_grad_potential[_qp].size()*_Vc[_qp]/_rc[_qp]*_grad_u[_qp]/_rc[_qp];
}
