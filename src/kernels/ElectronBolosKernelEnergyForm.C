#include "ElectronBolosKernelEnergyForm.h"

template<>
InputParameters validParams<ElectronBolosKernelEnergyForm>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredCoupledVar("mean_en", "The electron temperature");
  params.addRequiredCoupledVar("potential","The electric potential");
  params.addParam<bool>("townsend",false,"Whether to use the townsend formulation for the ionization term.");

  return params;
}

ElectronBolosKernelEnergyForm::ElectronBolosKernelEnergyForm(const InputParameters & parameters) :
  Kernel(parameters),

  _mean_en(coupledValue("mean_en")),
  _mean_en_id(coupled("mean_en")),
  _grad_potential(coupledGradient("potential")),
  _potential_id(coupled("potential")),

  // Kernel members

  // _alpha(0.0),
  // _Pe(0.0),
  // _vd_mag(0.0),
  // _delta(0.0),
  _townsend(getParam<bool>("townsend")),
  _actual_mean_en(0.0),
  _iz(0.0),
  _d_iz_d_actual_mean_en(0.0),
  _d_actual_mean_en_d_em(0.0),
  _d_actual_mean_en_d_mean_en(0.0),
  _d_iz_d_em(0.0),
  _d_iz_d_mean_en(0.0),
  _electron_flux(0.0,0.0,0.0),
  _d_electron_flux_d_potential(0.0,0.0,0.0),
  _d_electron_flux_d_em(0.0,0.0,0.0),
  _electron_flux_mag(0.0),
  _d_electron_flux_mag_d_potential(0.0),
  _d_electron_flux_mag_d_em(0.0),
  _source_term(0.0),
  _d_source_term_d_em(0.0),
  _d_source_term_d_mean_en(0.0),
  _d_source_term_d_potential(0.0),

  // Material Properties

  _muem(getMaterialProperty<Real>("muem")),
  _diffem(getMaterialProperty<Real>("diffem")),
  _Ar(getMaterialProperty<Real>("Ar")),
  _iz_coeff_energy_a(getMaterialProperty<Real>("iz_coeff_energy_a")),
  _iz_coeff_energy_b(getMaterialProperty<Real>("iz_coeff_energy_b")),
  _iz_coeff_energy_c(getMaterialProperty<Real>("iz_coeff_energy_c")),
  _N_A(getMaterialProperty<Real>("N_A"))
{}

ElectronBolosKernelEnergyForm::~ElectronBolosKernelEnergyForm()
{}

Real
ElectronBolosKernelEnergyForm::computeQpResidual()
{
  // _vd_mag = std::abs(_muem[_qp]*_grad_potential[_qp].size());
  // _Pe = _vd_mag*_current_elem->hmax()/_diffem[_qp];
  // _alpha = std::min(1.0,_Pe/6.0);
  // _delta = _alpha*_vd_mag*_current_elem->hmax()/2.0;
  _actual_mean_en = std::exp(_mean_en[_qp]-_u[_qp]);
  _iz = _iz_coeff_energy_a[_qp]*std::pow(_actual_mean_en,_iz_coeff_energy_b[_qp])*std::exp(-_iz_coeff_energy_c[_qp]/_actual_mean_en);

  if ( _townsend ) {
    _electron_flux_mag = (-_muem[_qp]*-_grad_potential[_qp]*std::exp(_u[_qp])-_diffem[_qp]*std::exp(_u[_qp])*_grad_u[_qp]).size();
    _source_term = _iz * _electron_flux_mag;
  }
  else
    _source_term = _iz * _Ar[_qp] * std::exp(_u[_qp]);
 
  return -_grad_test[_i][_qp]*std::exp(_u[_qp])*(-_muem[_qp]*-_grad_potential[_qp]-_diffem[_qp]*_grad_u[_qp]) // Transport
    -_test[_i][_qp]*_source_term // Ionization term
    -_test[_i][_qp]*_N_A[_qp]*std::exp(-_u[_qp]); // Source stabilization
	 // -_grad_test[_i][_qp]*(-_delta*std::exp(_u[_qp])*_grad_u[_qp]); // Diffusion stabilization
}

Real
ElectronBolosKernelEnergyForm::computeQpJacobian()
{
  // _vd_mag = std::abs(_muem[_qp]*_grad_potential[_qp].size());
  // _Pe = _vd_mag*_current_elem->hmax()/_diffem[_qp];
  // _alpha = std::min(1.0,_Pe/6.0);
  // _delta = _alpha*_vd_mag*_current_elem->hmax()/2.0;
  _actual_mean_en = std::exp(_mean_en[_qp]-_u[_qp]);
  _iz = _iz_coeff_energy_a[_qp]*std::pow(_actual_mean_en,_iz_coeff_energy_b[_qp])*std::exp(-_iz_coeff_energy_c[_qp]/_actual_mean_en);
  _d_iz_d_actual_mean_en = std::pow(_actual_mean_en,_iz_coeff_energy_b[_qp]-2.0)*_iz_coeff_energy_a[_qp]*(_actual_mean_en*_iz_coeff_energy_b[_qp] + _iz_coeff_energy_c[_qp])*std::exp(-_iz_coeff_energy_c[_qp]/_actual_mean_en);
  _d_actual_mean_en_d_em = -std::exp(_mean_en[_qp]-_u[_qp])*_phi[_j][_qp];
  _d_iz_d_em = _d_iz_d_actual_mean_en * _d_actual_mean_en_d_em;

  if ( _townsend ) {
    _electron_flux = -_muem[_qp]*-_grad_potential[_qp]*std::exp(_u[_qp])-_diffem[_qp]*std::exp(_u[_qp])*_grad_u[_qp];
    _d_electron_flux_d_em = -_muem[_qp]*-_grad_potential[_qp]*std::exp(_u[_qp])*_phi[_j][_qp]-_diffem[_qp]*(std::exp(_u[_qp])*_phi[_j][_qp]*_grad_u[_qp]+std::exp(_u[_qp])*_grad_phi[_j][_qp]);
    _electron_flux_mag = _electron_flux.size();
    _d_electron_flux_mag_d_em = _electron_flux*_d_electron_flux_d_em/(_electron_flux_mag+std::numeric_limits<double>::epsilon());

    _d_source_term_d_em = _iz * _d_electron_flux_mag_d_em + _electron_flux_mag * _d_iz_d_em;
  }

  else {
    _d_source_term_d_em = std::exp(_u[_qp]) * _Ar[_qp] * _d_iz_d_em + _iz * _Ar[_qp] * std::exp(_u[_qp]) * _phi[_j][_qp];
  }

  return -_grad_test[_i][_qp]*std::exp(_u[_qp])*(-_muem[_qp]*-_grad_potential[_qp]*_phi[_j][_qp] - _diffem[_qp]*(_phi[_j][_qp]*_grad_u[_qp]+_grad_phi[_j][_qp])) // Transport
    -_test[_i][_qp] * _d_source_term_d_em
    -_test[_i][_qp]*_N_A[_qp]*std::exp(-_u[_qp])*-1.0*_phi[_j][_qp]; // Source stabilization
	 // -_grad_test[_i][_qp]*(-_delta*(std::exp(_u[_qp])*_grad_phi[_j][_qp]+std::exp(_u[_qp])*_phi[_j][_qp]*_grad_u[_qp])); // Diffusion stabilization
}

Real
ElectronBolosKernelEnergyForm::computeQpOffDiagJacobian(unsigned int jvar)
{
  _actual_mean_en = std::exp(_mean_en[_qp]-_u[_qp]);
  _iz = _iz_coeff_energy_a[_qp]*std::pow(_actual_mean_en,_iz_coeff_energy_b[_qp])*std::exp(-_iz_coeff_energy_c[_qp]/_actual_mean_en);
  _d_iz_d_actual_mean_en = std::pow(_actual_mean_en,_iz_coeff_energy_b[_qp]-2.0)*_iz_coeff_energy_a[_qp]*(_actual_mean_en*_iz_coeff_energy_b[_qp] + _iz_coeff_energy_c[_qp])*std::exp(-_iz_coeff_energy_c[_qp]/_actual_mean_en);
  _d_actual_mean_en_d_mean_en = std::exp(_mean_en[_qp]-_u[_qp])*_phi[_j][_qp];
  _d_iz_d_mean_en = _d_iz_d_actual_mean_en * _d_actual_mean_en_d_mean_en;

  if ( _townsend ) {
    _electron_flux = -_muem[_qp]*-_grad_potential[_qp]*std::exp(_u[_qp])-_diffem[_qp]*std::exp(_u[_qp])*_grad_u[_qp];
    _d_electron_flux_d_potential = -_muem[_qp]*-_grad_phi[_j][_qp]*std::exp(_u[_qp]);
    _electron_flux_mag = _electron_flux.size();
    _d_electron_flux_mag_d_potential = _electron_flux*_d_electron_flux_d_potential/(_electron_flux_mag+std::numeric_limits<double>::epsilon());

    _d_source_term_d_mean_en = _electron_flux_mag * _d_iz_d_mean_en;
    _d_source_term_d_potential = _iz * _d_electron_flux_mag_d_potential;
  }

  else {
    _d_source_term_d_mean_en = std::exp(_u[_qp]) * _Ar[_qp] * _d_iz_d_mean_en;
    _d_source_term_d_potential = 0.0;
  }

  if (jvar == _potential_id)
    return -_grad_test[_i][_qp]*std::exp(_u[_qp])*(-_muem[_qp]*-_grad_phi[_j][_qp]) - _test[_i][_qp] * _d_source_term_d_potential;

  else if (jvar == _mean_en_id)
    return -_test[_i][_qp] * _d_source_term_d_mean_en; // Ionization term
  
  else
    return 0.0;
}
