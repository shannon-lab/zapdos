#include "ArpKernel.h"

template<>
InputParameters validParams<ArpKernel>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredCoupledVar("potential", "The electric potential");
  params.addRequiredCoupledVar("em", "The electron density");
  params.addRequiredCoupledVar("mean_en", "The electront temperature");
  return params;
}

ArpKernel::ArpKernel(const std::string & name, InputParameters parameters) :
  Kernel(name, parameters),

  _em(coupledValue("em")),
  _grad_em(coupledGradient("em")),
  _grad_potential(coupledGradient("potential")),
  _potential_id(coupled("potential")),
  _mean_en(coupledValue("mean_en")),

  _muem(0.16),
  _diff(.05),
  _k4_const(5e-14),
  _Ar(1.01e5/(300*1.38e-23)),
  _Eiz(12.78),
  _muArp(1.54/1e4),
  _DArp(1.54/1e4*1.38e-23*300/1.6e-19),
  _a0(2.36e11), // Parameters for computing Townsend coeff
  _b0(-3.11), // Parameters for computing Townsend coeff
  _c0(6.63e1) // Parameters for computing Townsend coeff
{}

ArpKernel::~ArpKernel()
{}

Real
ArpKernel::computeQpResidual()
{
  return -_grad_test[_i][_qp]*(_muArp*-_grad_potential[_qp]*std::exp(_u[_qp])-_DArp*exp(_u[_qp])*_grad_u[_qp])
    // -_test[_i][_qp]*_k4_const*_Ar*std::exp(_em[_qp])*std::exp(-_Eiz/(2.0/3*std::exp(_mean_en[_qp]-_em[_qp]))); // Reaction coefficient formulation
    -_test[_i][_qp]*_a0*std::pow(std::exp(_mean_en[_qp]-_em[_qp]),_b0)*std::exp(-_c0/std::exp(_mean_en[_qp]-_em[_qp]))*(-_muem*-_grad_potential[_qp]*std::exp(_em[_qp])-_diff*std::exp(_em[_qp])*_grad_em[_qp]).size(); // Reaction. Townsend coefficient formulation
}

Real
ArpKernel::computeQpJacobian()
{
  return -_grad_test[_i][_qp]*(_muArp*-_grad_potential[_qp]*std::exp(_u[_qp])*_phi[_j][_qp]-_DArp*(std::exp(_u[_qp])*_phi[_j][_qp]*_grad_u[_qp]+std::exp(_u[_qp])*_grad_phi[_j][_qp]));
}

Real
ArpKernel::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id) {
    return -_grad_test[_i][_qp]*(_muArp*-_grad_phi[_j][_qp]*std::exp(_u[_qp]));
  }

  else {
    return 0.0;
  }
}

