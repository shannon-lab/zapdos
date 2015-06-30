#include "PoissonKernel.h"

template<>
InputParameters validParams<PoissonKernel>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredCoupledVar("em", "The electron density");
  params.addRequiredCoupledVar("Arp", "The argon ion density");

  return params;
}

PoissonKernel::PoissonKernel(const std::string & name, InputParameters parameters) :
  Kernel(name, parameters),

  _e(getMaterialProperty<Real>("e")),
  _permittivity(getMaterialProperty<Real>("permittivity")),
  _rc(getMaterialProperty<Real>("rc")),
  _Vc(getMaterialProperty<Real>("Vc")),
  _emc(getMaterialProperty<Real>("emc")),

  _em(coupledValue("em")),
  _Arp(coupledValue("Arp"))
{}

PoissonKernel::~PoissonKernel()
{}

Real
PoissonKernel::computeQpResidual()
{
  return -_grad_test[_i][_qp]*(-_grad_u[_qp])-_test[_i][_qp]*_e[_qp]/_permittivity[_qp]*_emc[_qp]*std::pow(_rc[_qp],2)/_Vc[_qp]*(std::max(_Arp[_qp],0.0)-std::max(_em[_qp],0.0));
}
