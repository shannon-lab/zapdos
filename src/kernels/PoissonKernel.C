#include "PoissonKernel.h"

template<>
InputParameters validParams<PoissonKernel>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredCoupledVar("em", "The electron density");
  params.addRequiredCoupledVar("Arp", "The argon ion density");

  return params;
}

PoissonKernel::PoissonKernel(const InputParameters & parameters) :
  Kernel(parameters),

  _em(coupledValue("em")),
  _Arp(coupledValue("Arp")),
  _em_id(coupled("em")),
  _Arp_id(coupled("Arp")),

  _e(1.6e-19),
  _eps(8.85e-12)
{}

PoissonKernel::~PoissonKernel()
{}

Real
PoissonKernel::computeQpResidual()
{
  return -_grad_test[_i][_qp]*(-_grad_u[_qp])
         -_test[_i][_qp]*_e/_eps*(std::exp(_Arp[_qp])-std::exp(_em[_qp]));
}

Real
PoissonKernel::computeQpJacobian()
{
  return -_grad_test[_i][_qp]*(-_grad_phi[_j][_qp]);
}

Real
PoissonKernel::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _em_id) {
    return -_test[_i][_qp]*_e/_eps*-std::exp(_em[_qp])*_phi[_j][_qp];
  }

  else if (jvar == _Arp_id) {
    return -_test[_i][_qp]*_e/_eps*std::exp(_Arp[_qp])*_phi[_j][_qp];
  }

  else {
    return 0.0;
  }
}
