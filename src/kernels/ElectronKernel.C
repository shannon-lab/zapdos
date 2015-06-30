#include "ElectronKernel.h"

template<>
InputParameters validParams<ElectronKernel>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredCoupledVar("Te", "The electron temperature");
  params.addRequiredCoupledVar("potential","The electric potential");

  return params;
}

ElectronKernel::ElectronKernel(const std::string & name, InputParameters parameters) :
  Kernel(name, parameters),

  _tc(getMaterialProperty<Real>("tc")),
  _rc(getMaterialProperty<Real>("rc")),
  _Tec(getMaterialProperty<Real>("Tec")),
  _Vc(getMaterialProperty<Real>("Vc")),
  _muem(getMaterialProperty<Real>("muem")),
  _k4_const(getMaterialProperty<Real>("k4_const")),
  _Ar(getMaterialProperty<Real>("Ar")),

  _Te(coupledValue("Te")),
  _grad_potential(coupledGradient("potential"))
{}

ElectronKernel::~ElectronKernel()
{}

Real
ElectronKernel::computeQpResidual()
{
  return -_grad_test[_i][_qp]*(_tc[_qp]*_Vc[_qp]*_muem[_qp]/std::pow(_rc[_qp],2)*std::max(_u[_qp],0.0)*_grad_potential[_qp]-_muem[_qp]*_Tec[_qp]*_tc[_qp]/std::pow(_rc[_qp],2)*std::max(_Te[_qp],0.0)*_grad_u[_qp])-_test[_i][_qp]*_tc[_qp]*_k4_const[_qp]*_Ar[_qp]*std::exp(-15.76/(_Tec[_qp]*std::max(_Te[_qp],1e-16)))*std::max(_u[_qp],0.0)+_tc[_qp]*_grad_test[_i][_qp]/_rc[_qp]*_current_elem->hmax()*_rc[_qp]*_muem[_qp]*_grad_potential[_qp].size()*_Vc[_qp]/_rc[_qp]*_grad_u[_qp]/_rc[_qp];
}
