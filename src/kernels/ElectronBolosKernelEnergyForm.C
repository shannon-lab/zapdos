#include "ElectronBolosKernelEnergyForm.h"

template<>
InputParameters validParams<ElectronBolosKernelEnergyForm>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredCoupledVar("mean_en", "The electron temperature");
  params.addRequiredCoupledVar("potential","The electric potential");
  return params;
}

ElectronBolosKernelEnergyForm::ElectronBolosKernelEnergyForm(const InputParameters & parameters) :
  Kernel(parameters),

  _mean_en(coupledValue("mean_en")),
  _mean_en_id(coupled("mean_en")),
  _grad_potential(coupledGradient("potential")),
  _potential_id(coupled("potential")),

  // Material Properties

  _muem(getMaterialProperty<Real>("muem")),
  _diffem(getMaterialProperty<Real>("diffem")),
  _Ar(getMaterialProperty<Real>("Ar")),
  _iz_coeff_energy_a(getMaterialProperty<Real>("iz_coeff_energy_a")),
  _iz_coeff_energy_b(getMaterialProperty<Real>("iz_coeff_energy_b")),
  _iz_coeff_energy_c(getMaterialProperty<Real>("iz_coeff_energy_c")),
  _N_A(getMaterialProperty<Real>("N_A")),
  _alpha_iz(getMaterialProperty<Real>("alpha_iz")),
  _d_iz_d_actual_mean_en(getMaterialProperty<Real>("d_iz_d_actual_mean_en")),
  _d_muem_d_actual_mean_en(getMaterialProperty<Real>("d_muem_d_actual_mean_en")),
  _d_diffem_d_actual_mean_en(getMaterialProperty<Real>("d_diffem_d_actual_mean_en"))
{
}

ElectronBolosKernelEnergyForm::~ElectronBolosKernelEnergyForm()
{}

Real
ElectronBolosKernelEnergyForm::computeQpResidual()
{
  Real _electron_flux_mag = (-_muem[_qp]*-_grad_potential[_qp]*std::exp(_u[_qp])-_diffem[_qp]*std::exp(_u[_qp])*_grad_u[_qp]).size();
  Real _iz_term = _alpha_iz[_qp] * _electron_flux_mag;

  return -_grad_test[_i][_qp]*std::exp(_u[_qp])*(-_muem[_qp]*-_grad_potential[_qp]-_diffem[_qp]*_grad_u[_qp])
    -_test[_i][_qp]*_iz_term 
    -_test[_i][_qp]*_N_A[_qp]*std::exp(-_u[_qp]); 
	 // -_grad_test[_i][_qp]*(-_delta*std::exp(_u[_qp])*_grad_u[_qp]); // Diffusion stabilization
}

Real
ElectronBolosKernelEnergyForm::computeQpJacobian()
{
  Real _actual_mean_en = std::exp(_mean_en[_qp]-_u[_qp]);
  Real _d_actual_mean_en_d_em = -std::exp(_mean_en[_qp]-_u[_qp])*_phi[_j][_qp];
  Real _d_iz_d_em = _d_iz_d_actual_mean_en[_qp] * _d_actual_mean_en_d_em;
  Real _d_muem_d_em = _d_muem_d_actual_mean_en[_qp] * _d_actual_mean_en_d_em;
  Real _d_diffem_d_em = _d_diffem_d_actual_mean_en[_qp] * _d_actual_mean_en_d_em;

  RealVectorValue _electron_flux = -_muem[_qp]*-_grad_potential[_qp]*std::exp(_u[_qp])-_diffem[_qp]*std::exp(_u[_qp])*_grad_u[_qp];
  RealVectorValue _d_electron_flux_d_em = -_d_muem_d_em*-_grad_potential[_qp]*std::exp(_u[_qp])-_muem[_qp]*-_grad_potential[_qp]*std::exp(_u[_qp])*_phi[_j][_qp]-_d_diffem_d_em*std::exp(_u[_qp])*_grad_u[_qp]-_diffem[_qp]*std::exp(_u[_qp])*_phi[_j][_qp]*_grad_u[_qp]-_diffem[_qp]*std::exp(_u[_qp])*_grad_phi[_j][_qp];
  Real _electron_flux_mag = _electron_flux.size();
  Real _d_electron_flux_mag_d_em = _electron_flux*_d_electron_flux_d_em/(_electron_flux_mag+std::numeric_limits<double>::epsilon());

  Real _d_iz_term_d_em = (_electron_flux_mag * _d_iz_d_em + _alpha_iz[_qp] * _d_electron_flux_mag_d_em);

  return -_grad_test[_i][_qp]*_d_electron_flux_d_em
    -_test[_i][_qp] * _d_iz_term_d_em
    -_test[_i][_qp]*_N_A[_qp]*std::exp(-_u[_qp])*-1.0*_phi[_j][_qp];
	 // -_grad_test[_i][_qp]*(-_delta*(std::exp(_u[_qp])*_grad_phi[_j][_qp]+std::exp(_u[_qp])*_phi[_j][_qp]*_grad_u[_qp])); // Diffusion stabilization
}

Real
ElectronBolosKernelEnergyForm::computeQpOffDiagJacobian(unsigned int jvar)
{
  Real _actual_mean_en = std::exp(_mean_en[_qp]-_u[_qp]);
  Real _d_actual_mean_en_d_mean_en = std::exp(_mean_en[_qp]-_u[_qp])*_phi[_j][_qp];
  Real _d_iz_d_mean_en = _d_iz_d_actual_mean_en[_qp] * _d_actual_mean_en_d_mean_en;
  Real _d_muem_d_mean_en = _d_muem_d_actual_mean_en[_qp] * _d_actual_mean_en_d_mean_en;
  Real _d_diffem_d_mean_en = _d_diffem_d_actual_mean_en[_qp] * _d_actual_mean_en_d_mean_en;

  RealVectorValue _electron_flux = -_muem[_qp]*-_grad_potential[_qp]*std::exp(_u[_qp])-_diffem[_qp]*std::exp(_u[_qp])*_grad_u[_qp];
  RealVectorValue _d_electron_flux_d_potential = -_muem[_qp]*-_grad_phi[_j][_qp]*std::exp(_u[_qp]);
  RealVectorValue _d_electron_flux_d_mean_en = -_d_muem_d_mean_en*-_grad_potential[_qp]*std::exp(_u[_qp])-_d_diffem_d_mean_en*std::exp(_u[_qp])*_grad_u[_qp];
  Real _electron_flux_mag = _electron_flux.size();
  Real _d_electron_flux_mag_d_potential = _electron_flux*_d_electron_flux_d_potential/(_electron_flux_mag+std::numeric_limits<double>::epsilon());
  Real _d_electron_flux_mag_d_mean_en = _electron_flux*_d_electron_flux_d_mean_en/(_electron_flux_mag+std::numeric_limits<double>::epsilon());

  Real _d_iz_term_d_potential = (_alpha_iz[_qp] * _d_electron_flux_mag_d_potential);
  Real _d_iz_term_d_mean_en = (_electron_flux_mag * _d_iz_d_mean_en + _alpha_iz[_qp] * _d_electron_flux_mag_d_mean_en);

  if (jvar == _potential_id)
    return -_grad_test[_i][_qp]*_d_electron_flux_d_potential
      -_test[_i][_qp]*_d_iz_term_d_potential;

  else if (jvar == _mean_en_id)
    return -_grad_test[_i][_qp]*_d_electron_flux_d_mean_en
      -_test[_i][_qp]*_d_iz_term_d_mean_en; // Ionization term
  
  else
    return 0.0;
}
