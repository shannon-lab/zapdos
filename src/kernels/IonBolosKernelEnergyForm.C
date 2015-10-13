#include "IonBolosKernelEnergyForm.h"

template<>
InputParameters validParams<IonBolosKernelEnergyForm>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredCoupledVar("potential", "The electric potential");
  params.addRequiredCoupledVar("em", "The electron density");
  params.addRequiredCoupledVar("mean_en", "The electront temperature");
  params.addParam<bool>("townsend",false,"Whether to use the townsend formulation for the ionization term.");
  return params;
}

IonBolosKernelEnergyForm::IonBolosKernelEnergyForm(const InputParameters & parameters) :
  Kernel(parameters),

  _em(coupledValue("em")),
  _grad_em(coupledGradient("em")),
  _em_id(coupled("em")),
  _grad_potential(coupledGradient("potential")),
  _potential_id(coupled("potential")),
  _mean_en(coupledValue("mean_en")),
  _mean_en_id(coupled("mean_en")),

  // Material Properties

  _muem(getMaterialProperty<Real>("muem")),
  _diffem(getMaterialProperty<Real>("diffem")),
  _muip(getMaterialProperty<Real>("muip")),
  _diffip(getMaterialProperty<Real>("diffip")),
  _Ar(getMaterialProperty<Real>("Ar")),
  _iz_coeff_energy_a(getMaterialProperty<Real>("iz_coeff_energy_a")),
  _iz_coeff_energy_b(getMaterialProperty<Real>("iz_coeff_energy_b")),
  _iz_coeff_energy_c(getMaterialProperty<Real>("iz_coeff_energy_c")),
  _N_A(getMaterialProperty<Real>("N_A")),

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
  _d_source_term_d_potential(0.0)
{}

IonBolosKernelEnergyForm::~IonBolosKernelEnergyForm()
{}

Real
IonBolosKernelEnergyForm::computeQpResidual()
{
  // _vd_mag = std::abs(_muip[_qp]*_grad_potential[_qp].size());
  // _Pe = _vd_mag*_current_elem->hmax()/_diffip[_qp];
  // _alpha = std::min(1.0,_Pe/6.0);
  // _delta = _alpha*_vd_mag*_current_elem->hmax()/2.0;
  _actual_mean_en = std::exp(_mean_en[_qp]-_em[_qp]);
  _iz = _iz_coeff_energy_a[_qp]*std::pow(_actual_mean_en,_iz_coeff_energy_b[_qp])*std::exp(-_iz_coeff_energy_c[_qp]/_actual_mean_en);

  if ( _townsend ) {
    _electron_flux_mag = (-_muem[_qp]*-_grad_potential[_qp]*std::exp(_em[_qp])-_diffem[_qp]*std::exp(_em[_qp])*_grad_em[_qp]).size();
    _source_term = _iz * _electron_flux_mag;
  }
  else
    _source_term = _iz * _Ar[_qp] * std::exp(_em[_qp]);
 
  return -_grad_test[_i][_qp]*std::exp(_u[_qp])*(_muip[_qp]*-_grad_potential[_qp]-_diffip[_qp]*_grad_u[_qp])
    -_test[_i][_qp]*_source_term // Ionization term
    -_test[_i][_qp]*_N_A[_qp]*std::exp(-_u[_qp]); // Source stabilization
    // -_grad_test[_i][_qp]*(-_delta*std::exp(_u[_qp])*_grad_u[_qp]); // Diffusion stabilization
}

Real
IonBolosKernelEnergyForm::computeQpJacobian()
{
  // _vd_mag = std::abs(_muip[_qp]*_grad_potential[_qp].size());
  // _Pe = _vd_mag*_current_elem->hmax()/_diffip[_qp];
  // _alpha = std::min(1.0,_Pe/6.0);
  // _delta = _alpha*_vd_mag*_current_elem->hmax()/2.0;

  return -_grad_test[_i][_qp]*(_muip[_qp]*-_grad_potential[_qp]*std::exp(_u[_qp])*_phi[_j][_qp]-_diffip[_qp]*(std::exp(_u[_qp])*_grad_phi[_j][_qp]+std::exp(_u[_qp])*_phi[_j][_qp]*_grad_u[_qp]))
    -_test[_i][_qp]*_N_A[_qp]*std::exp(-_u[_qp])*-1.0*_phi[_j][_qp]; // Source stabilization
    // -_grad_test[_i][_qp]*(-_delta*(std::exp(_u[_qp])*_grad_phi[_j][_qp]+std::exp(_u[_qp])*_phi[_j][_qp]*_grad_u[_qp])); // Diffusion stabilization
}

Real
IonBolosKernelEnergyForm::computeQpOffDiagJacobian(unsigned int jvar)
{
  _actual_mean_en = std::exp(_mean_en[_qp]-_em[_qp]);
  _iz = _iz_coeff_energy_a[_qp]*std::pow(_actual_mean_en,_iz_coeff_energy_b[_qp])*std::exp(-_iz_coeff_energy_c[_qp]/_actual_mean_en);
  _d_iz_d_actual_mean_en = std::pow(_actual_mean_en,_iz_coeff_energy_b[_qp]-2.0)*_iz_coeff_energy_a[_qp]*(_actual_mean_en*_iz_coeff_energy_b[_qp] + _iz_coeff_energy_c[_qp])*std::exp(-_iz_coeff_energy_c[_qp]/_actual_mean_en);
  _d_actual_mean_en_d_em = -std::exp(_mean_en[_qp]-_em[_qp])*_phi[_j][_qp];
  _d_actual_mean_en_d_mean_en = std::exp(_mean_en[_qp]-_em[_qp])*_phi[_j][_qp];
  _d_iz_d_em = _d_iz_d_actual_mean_en * _d_actual_mean_en_d_em;
  _d_iz_d_mean_en = _d_iz_d_actual_mean_en * _d_actual_mean_en_d_mean_en;

  if ( _townsend ) {
    _electron_flux = -_muem[_qp]*-_grad_potential[_qp]*std::exp(_em[_qp])-_diffem[_qp]*std::exp(_em[_qp])*_grad_em[_qp];
    _d_electron_flux_d_potential = -_muem[_qp]*-_grad_phi[_j][_qp]*std::exp(_em[_qp]);
    _d_electron_flux_d_em = -_muem[_qp]*-_grad_potential[_qp]*std::exp(_em[_qp])*_phi[_j][_qp]-_diffem[_qp]*(std::exp(_em[_qp])*_phi[_j][_qp]*_grad_em[_qp]+std::exp(_em[_qp])*_grad_phi[_j][_qp]);
    _electron_flux_mag = _electron_flux.size();
    _d_electron_flux_mag_d_potential = _electron_flux*_d_electron_flux_d_potential/(_electron_flux_mag+std::numeric_limits<double>::epsilon());
    _d_electron_flux_mag_d_em = _electron_flux*_d_electron_flux_d_em/(_electron_flux_mag+std::numeric_limits<double>::epsilon());

    _d_source_term_d_em = _iz * _d_electron_flux_mag_d_em + _electron_flux_mag * _d_iz_d_em;
    _d_source_term_d_mean_en = _electron_flux_mag * _d_iz_d_mean_en;
    _d_source_term_d_potential = _iz * _d_electron_flux_mag_d_potential;
  }

  else {
    _d_source_term_d_em = std::exp(_em[_qp]) * _Ar[_qp] * _d_iz_d_em + _iz * _Ar[_qp] * std::exp(_em[_qp]) * _phi[_j][_qp];
    _d_source_term_d_mean_en = std::exp(_em[_qp]) * _Ar[_qp] * _d_iz_d_mean_en;
    _d_source_term_d_potential = 0.0;
  }
 
  if (jvar == _potential_id)
    return -_grad_test[_i][_qp]*(_muip[_qp]*-_grad_phi[_j][_qp]*std::exp(_u[_qp])) - _test[_i][_qp] * _d_source_term_d_potential;

  else if (jvar == _em_id)
    return -_test[_i][_qp] * _d_source_term_d_em; // Ionization term

  else if (jvar == _mean_en_id)
    return -_test[_i][_qp] * _d_source_term_d_mean_en; // Ionization term

  else
    return 0.0;
}

