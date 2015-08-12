#include "ArpKernel.h"

template<>
InputParameters validParams<ArpKernel>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredCoupledVar("potential", "The electric potential");
  params.addRequiredCoupledVar("em", "The electron density");
  // params.addRequiredCoupledVar("mean_en", "The electront temperature");
  return params;
}

ArpKernel::ArpKernel(const InputParameters & parameters) :
  Kernel(parameters),

  _em(coupledValue("em")),
  _grad_em(coupledGradient("em")),
  _grad_potential(coupledGradient("potential")),
  _potential_id(coupled("potential")),
  // _mean_en(coupledValue("mean_en")),

  _muem(380.0/1e4),
  _diff(1800.0/1e4),
  _muArp(3.42/1e2), // Morrow
  _DArp(0.046/1e4), // Morrow
  _alpha(0.0),
  _Pe(0.0),
  _vd_mag(0.0),
  _delta(0.0)
  // _a0(2.36e11), // Parameters for computing Townsend coeff
  // _b0(-3.11), // Parameters for computing Townsend coeff
  // _c0(6.63e1) // Parameters for computing Townsend coeff
  // _k4_const(5e-14),
  // _Ar(1.01e5/(300*1.38e-23)),
  // _Eiz(12.78),
{}

ArpKernel::~ArpKernel()
{}

Real
ArpKernel::computeQpResidual()
{
  _vd_mag = std::abs(_muArp*_grad_potential[_qp].size());
  _Pe = _vd_mag*_current_elem->hmax()/_DArp;
  _alpha = std::min(1.0,_Pe/6.0);
  _delta = _alpha*_vd_mag*_current_elem->hmax()/2.0;
 
  return -_grad_test[_i][_qp]*std::exp(_u[_qp])*(_muArp*-_grad_potential[_qp]-_DArp*_grad_u[_qp])
    // -_test[_i][_qp]*_k4_const*_Ar*std::exp(_em[_qp])*std::exp(-_Eiz/(2.0/3*std::exp(_mean_en[_qp]-_em[_qp]))); // Reaction coefficient formulation
    -_test[_i][_qp]*0.35*std::exp(-1.65e7/_grad_potential[_qp].size())*(-_muem*-_grad_potential[_qp]*std::exp(_em[_qp])-_diff*std::exp(_em[_qp])*_grad_em[_qp]).size() // Reaction. Townsend coefficient formulation
    -_grad_test[_i][_qp]*(-_delta*std::exp(_u[_qp])*_grad_u[_qp]); // Diffusion stabilization
}

Real
ArpKernel::computeQpJacobian()
{
  return -_grad_test[_i][_qp]*(_muArp*-_grad_potential[_qp]*std::exp(_u[_qp])*_phi[_j][_qp]-_DArp*(std::exp(_u[_qp])*_grad_phi[_j][_qp]+std::exp(_u[_qp])*_phi[_j][_qp]*_grad_u[_qp]))
    -_grad_test[_i][_qp]*(-_delta*(std::exp(_u[_qp])*_grad_phi[_j][_qp]+std::exp(_u[_qp])*_phi[_j][_qp]*_grad_u[_qp])); // Diffusion stabilization
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

