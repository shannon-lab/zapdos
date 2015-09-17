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
  // _mean_en_id(coupled("mean_en")),
  _grad_potential(coupledGradient("potential")),
  _potential_id(coupled("potential")),

  // Kernel members

  _alpha(0.0),
  _Pe(0.0),
  _vd_mag(0.0),
  _delta(0.0),
  _flux(0.0,0.0,0.0),
  _d_flux_d_u(0.0,0.0,0.0),
  _d_flux_d_potential(0.0,0.0,0.0),

  // Material Properties

  _muem(getMaterialProperty<Real>("muem")),
  _diffem(getMaterialProperty<Real>("diffem")),
  _Ar(getMaterialProperty<Real>("Ar")),
  _Eiz(getMaterialProperty<Real>("Eiz")),
  _rate_coeff_ion(getMaterialProperty<Real>("rate_coeff_ion"))
{}

ElectronKernel::~ElectronKernel()
{}

Real
ElectronKernel::computeQpResidual()
{
  // _vd_mag = std::abs(_muem[_qp]*_grad_potential[_qp].size());
  // _Pe = _vd_mag*_current_elem->hmax()/_diffem[_qp];
  // _alpha = std::min(1.0,_Pe/6.0);
  // _delta = _alpha*_vd_mag*_current_elem->hmax()/2.0;

  return -_grad_test[_i][_qp]*std::exp(_u[_qp])*(-_muem[_qp]*-_grad_potential[_qp]-_diffem[_qp]*_grad_u[_qp]) // Transport
    -_test[_i][_qp]*_rate_coeff_ion[_qp]*std::exp(-_Eiz[_qp]/(1e-15+_grad_potential[_qp].size()))*(-_muem[_qp]*-_grad_potential[_qp]*std::exp(_u[_qp])-_diffem[_qp]*std::exp(_u[_qp])*_grad_u[_qp]).size(); // Reaction. Townsend coefficient formulation
	 // -_grad_test[_i][_qp]*(-_delta*std::exp(_u[_qp])*_grad_u[_qp]); // Diffusion stabilization
}

Real
ElectronKernel::computeQpJacobian()
{
  // _vd_mag = std::abs(_muem[_qp]*_grad_potential[_qp].size());
  // _Pe = _vd_mag*_current_elem->hmax()/_diffem[_qp];
  // _alpha = std::min(1.0,_Pe/6.0);
  // _delta = _alpha*_vd_mag*_current_elem->hmax()/2.0;
  _flux = -_muem[_qp]*-_grad_potential[_qp]*std::exp(_u[_qp])-_diffem[_qp]*std::exp(_u[_qp])*_grad_u[_qp];
  _d_flux_d_u = -_muem[_qp]*-_grad_potential[_qp]*std::exp(_u[_qp])*_phi[_j][_qp]-_diffem[_qp]*(std::exp(_u[_qp])*_grad_phi[_j][_qp]+std::exp(_u[_qp])*_phi[_j][_qp]*_grad_u[_qp]);
  
  return -_grad_test[_i][_qp]*std::exp(_u[_qp])*(-_muem[_qp]*-_grad_potential[_qp]*_phi[_j][_qp] - _diffem[_qp]*(_phi[_j][_qp]*_grad_u[_qp]+_grad_phi[_j][_qp])) // Transport
    -_test[_i][_qp]*_rate_coeff_ion[_qp]*std::exp(-_Eiz[_qp]/(1e-15+_grad_potential[_qp].size()))*_flux*_d_flux_d_u/(_flux.size()+1e-15); // Reaction. Townsend coefficient formulation
	 // -_grad_test[_i][_qp]*(-_delta*(std::exp(_u[_qp])*_grad_phi[_j][_qp]+std::exp(_u[_qp])*_phi[_j][_qp]*_grad_u[_qp])); // Diffusion stabilization
}

Real
ElectronKernel::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id) { 
    _flux = -_muem[_qp]*-_grad_potential[_qp]*std::exp(_u[_qp])-_diffem[_qp]*std::exp(_u[_qp])*_grad_u[_qp];
    _d_flux_d_potential = -_muem[_qp]*-_grad_phi[_j][_qp]*std::exp(_u[_qp]);

    return -_grad_test[_i][_qp]*std::exp(_u[_qp])*(-_muem[_qp]*-_grad_phi[_j][_qp])
      -_test[_i][_qp]*_rate_coeff_ion[_qp]*(std::exp(-_Eiz[_qp]/(1e-15+_grad_potential[_qp].size()))*_Eiz[_qp]*_grad_potential[_qp]*_grad_phi[_j][_qp]/(1e-15+std::pow(_grad_potential[_qp].size(),3))*(-_muem[_qp]*-_grad_potential[_qp]*std::exp(_u[_qp])-_diffem[_qp]*std::exp(_u[_qp])*_grad_u[_qp]).size() + std::exp(-_Eiz[_qp]/(1e-15+_grad_potential[_qp].size()))*_flux*_d_flux_d_potential/(_flux.size()+1e-15)); // Reaction. Townsend coefficient formulation
  }

  else {
    return 0.0;
  }
}
