#include "ElectronKernelIntTD.h"

template<>
InputParameters validParams<ElectronKernelIntTD>()
{
  InputParameters params = validParams<Kernel>();

  // params.addRequiredCoupledVar("mean_en", "The electron temperature");
  params.addRequiredCoupledVar("potential","The electric potential");

  return params;
}

ElectronKernelIntTD::ElectronKernelIntTD(const InputParameters & parameters) :
  Kernel(parameters),

  // _mean_en(coupledValue("mean_en")),
  // _mean_en_id(coupled("mean_en")),
  _grad_potential(coupledGradient("potential")),
  _potential_id(coupled("potential")),

  // Kernel members

  _alpha(0.0),
  _Pe(0.0),
  _vd_mag(0.0),
  _delta(0.0),
  // _flux(0.0,0.0,0.0),
  // _d_flux_d_u(0.0,0.0,0.0),

  // Material Properties

  _muem(getMaterialProperty<Real>("muem")),
  _diffem(getMaterialProperty<Real>("diffem")),
  _Ar(getMaterialProperty<Real>("Ar")),
  _rate_coeff_ion(getMaterialProperty<Real>("rate_coeff_ion"))
{}

ElectronKernelIntTD::~ElectronKernelIntTD()
{}

Real
ElectronKernelIntTD::computeQpResidual()
{
  _vd_mag = std::abs(_muem[_qp]*_grad_potential[_qp].size());
  _Pe = _vd_mag*_current_elem->hmax()/_diffem[_qp];
  _alpha = std::min(1.0,_Pe/6.0);
  _delta = _alpha*_vd_mag*_current_elem->hmax()/2.0;
  
  // Trying a logarithmic formulation
  return -_grad_test[_i][_qp]*std::exp(_u[_qp])*(-_muem[_qp]*-_grad_potential[_qp]-_diffem[_qp]*_grad_u[_qp]) // Transport
    -_test[_i][_qp]*_rate_coeff_ion[_qp]*(-_muem[_qp]*-_grad_potential[_qp]*std::exp(_u[_qp])-_diffem[_qp]*std::exp(_u[_qp])*_grad_u[_qp]).size(); // Reaction. Townsend coefficient formulation
	 // -_grad_test[_i][_qp]*(-_delta*std::exp(_u[_qp])*_grad_u[_qp]); // Diffusion stabilization
}

// Real
// ElectronKernelIntTD::computeQpJacobian()
// {
//   _vd_mag = std::abs(_muem[_qp]*_grad_potential[_qp].size());
//   _Pe = _vd_mag*_current_elem->hmax()/_diffem[_qp];
//   _alpha = std::min(1.0,_Pe/6.0);
//   _delta = _alpha*_vd_mag*_current_elem->hmax()/2.0;
//   // _flux = -_muem[_qp]*-_grad_potential[_qp]*std::exp(_u[_qp])-_diffem[_qp]*std::exp(_u[_qp])*_grad_u[_qp];
//   // _d_flux_d_u = -_muem[_qp]*-_grad_potential[_qp]*std::exp(_u[_qp])*_phi[_j][_qp]-_diffem[_qp]*(std::exp(_u[_qp])*_grad_phi[_j][_qp]+std::exp(_u[_qp])*_phi[_j][_qp]*_grad_u[_qp]);
  
//   return -_grad_test[_i][_qp]*std::exp(_u[_qp])*(-_muem[_qp]*-_grad_potential[_qp]*_phi[_j][_qp] - _diffem[_qp]*(_phi[_j][_qp]*_grad_u[_qp]+_grad_phi[_j][_qp])) // Transport
// 	 -_test[_i][_qp]*_rate_coeff_ion[_qp]*_Ar[_qp]*(-3.0/2*_Eiz[_qp]*std::exp(-_Eiz[_qp]/(2.0/3*std::exp(_mean_en[_qp]-_u[_qp])))*std::exp(_u[_qp]-_mean_en[_qp])*_phi[_j][_qp]*std::exp(_u[_qp]) 
//                                         + std::exp(-_Eiz[_qp]/(2.0/3*std::exp(_mean_en[_qp]-_u[_qp])))*std::exp(_u[_qp])*_phi[_j][_qp]) // Reaction. Rate Coefficient Formulation
// 	 -_grad_test[_i][_qp]*(-_delta*(std::exp(_u[_qp])*_grad_phi[_j][_qp]+std::exp(_u[_qp])*_phi[_j][_qp]*_grad_u[_qp])); // Diffusion stabilization
// }

// Real
// ElectronKernelIntTD::computeQpOffDiagJacobian(unsigned int jvar)
// {
//   if (jvar == _potential_id) { 
//     return -_grad_test[_i][_qp]*std::exp(_u[_qp])*(-_muem[_qp]*-_grad_phi[_j][_qp]);
//   }

//   else if (jvar == _mean_en_id) {
//     return -_test[_i][_qp]*_rate_coeff_ion[_qp]*_Ar[_qp]*std::exp(-_Eiz[_qp]/(2.0/3*std::exp(_mean_en[_qp]-_u[_qp])))*std::exp(_u[_qp])*3.0/2*_Eiz[_qp]*std::exp(_u[_qp]-_mean_en[_qp])*_phi[_j][_qp]; // Reaction. Rate coefficient formulation
//   }

//   else {
//     return 0.0;
//   }
// }
