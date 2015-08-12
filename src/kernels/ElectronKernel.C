#include "ElectronKernel.h"

template<>
InputParameters validParams<ElectronKernel>()
{
  InputParameters params = validParams<Kernel>();

  // params.addRequiredCoupledVar("mean_en", "The electron temperature");
  params.addRequiredCoupledVar("potential","The electric potential");

  return params;
}

ElectronKernel::ElectronKernel(const InputParameters & parameters) :
  Kernel(parameters),

  // _mean_en(coupledValue("mean_en")),
  _grad_potential(coupledGradient("potential")),
  _potential_id(coupled("potential")),

  _muem(380.0/1e4), // Morrow, Ebert
  _diff(1800.0/1e4), // Morrow, Ebert
  _alpha(0.0),
  _Pe(0.0),
  _vd_mag(0.0),
  _delta(0.0),
  _flux(0.0,0.0,0.0),
  _d_flux_d_u(0.0,0.0,0.0)
  // _a0(2.36e11), // Parameters for computing Townsend coeff
  // _b0(-3.11), // Parameters for computing Townsend coeff
  // _c0(6.63e1) // Parameters for computing Townsend coeff
  // _k4_const(5e-14),
  // _Eiz(12.78),
  // _muem(0.16), // Equates to comsols reduced mobility
  // _Ar(1.01e5/(300*1.38e-23)),
{}

ElectronKernel::~ElectronKernel()
{}

Real
ElectronKernel::computeQpResidual()
{
  _vd_mag = std::abs(_muem*_grad_potential[_qp].size());
  _Pe = _vd_mag*_current_elem->hmax()/_diff;
  _alpha = std::min(1.0,_Pe/6.0);
  _delta = _alpha*_vd_mag*_current_elem->hmax()/2.0;
  
  // Trying a logarithmic formulation
  return -_grad_test[_i][_qp]*std::exp(_u[_qp])*(-_muem*-_grad_potential[_qp]-_diff*_grad_u[_qp]) // Transport
         // -_test[_i][_qp]*_k4_const*_Ar*std::exp(-_Eiz/(2.0/3*std::exp(_mean_en[_qp]-_u[_qp])))*std::exp(_u[_qp]) // Reaction. Rate coefficient formulation
    -_test[_i][_qp]*0.35*std::exp(-1.65e7/_grad_potential[_qp].size())*(-_muem*-_grad_potential[_qp]*std::exp(_u[_qp])-_diff*std::exp(_u[_qp])*_grad_u[_qp]).size() // Reaction. Townsend coefficient formulation
	 -_grad_test[_i][_qp]*(-_delta*std::exp(_u[_qp])*_grad_u[_qp]); // Diffusion stabilization
}

Real
ElectronKernel::computeQpJacobian()
{
  _vd_mag = std::abs(_muem*_grad_potential[_qp].size());
  _Pe = _vd_mag*_current_elem->hmax()/_diff;
  _alpha = std::min(1.0,_Pe/6.0);
  _delta = _alpha*_vd_mag*_current_elem->hmax()/2.0;
  _flux = -_muem*-_grad_potential[_qp]*std::exp(_u[_qp])-_diff*std::exp(_u[_qp])*_grad_u[_qp];
  _d_flux_d_u = -_muem*-_grad_potential[_qp]*std::exp(_u[_qp])*_phi[_j][_qp]-_diff*(std::exp(_u[_qp])*_grad_phi[_j][_qp]+std::exp(_u[_qp])*_phi[_j][_qp]*_grad_u[_qp]);
  
  return -_grad_test[_i][_qp]*std::exp(_u[_qp])*(-_muem*-_grad_potential[_qp]*_phi[_j][_qp] - _diff*(_phi[_j][_qp]*_grad_u[_qp]+_grad_phi[_j][_qp]))
	 // -_test[_i][_qp]*_k4_const*_Ar*(-3.0/2*_Eiz*std::exp(-_Eiz/(2.0/3*std::exp(_mean_en[_qp]-_u[_qp])))*std::exp(_u[_qp]-_mean_en[_qp])*_phi[_j][_qp]*std::exp(_u[_qp]) 
                                        // + std::exp(-_Eiz/(2.0/3*std::exp(_mean_en[_qp]-_u[_qp])))*std::exp(_u[_qp])*_phi[_j][_qp]) // Reaction. Rate Coefficient Formulation
    -_test[_i][_qp]*0.35*std::exp(-1.65e7/_grad_potential[_qp].size())*_flux*_d_flux_d_u/std::sqrt(_flux*_flux) // Reaction. Townsend coefficient formulation
	 -_grad_test[_i][_qp]*(-_delta*(std::exp(_u[_qp])*_grad_phi[_j][_qp]+std::exp(_u[_qp])*_phi[_j][_qp]*_grad_u[_qp])); // Diffusion stabilization
}

Real
ElectronKernel::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id) { 
    return -_grad_test[_i][_qp]*std::exp(_u[_qp])*(-_muem*-_grad_phi[_j][_qp]);
  }

  else {
    return 0.0;
  }
}
