#include "ElectronEnergyBolosKernel.h"

template<>
InputParameters validParams<ElectronEnergyBolosKernel>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredCoupledVar("em", "The electron density");
  params.addRequiredCoupledVar("potential","The electric potential");
  params.addParam<bool>("townsend",false,"Whether to use the townsend formulation for the ionization term.");

  return params;
}

ElectronEnergyBolosKernel::ElectronEnergyBolosKernel(const InputParameters & parameters) :
  Kernel(parameters),

  _em(coupledValue("em")),
  _grad_em(coupledGradient("em")),
  _em_id(coupled("em")),
  _grad_potential(coupledGradient("potential")),
  _potential_id(coupled("em")),

  // Material properties

  _muel(getMaterialProperty<Real>("muel")),
  _muem(getMaterialProperty<Real>("muem")),
  _diffem(getMaterialProperty<Real>("diffem")),
  _diffel(getMaterialProperty<Real>("diffel")),
  _Ar(getMaterialProperty<Real>("Ar")),
  _mem(getMaterialProperty<Real>("mem")),
  _mip(getMaterialProperty<Real>("mip")),
  _iz_coeff_energy_a(getMaterialProperty<Real>("iz_coeff_energy_a")),
  _iz_coeff_energy_b(getMaterialProperty<Real>("iz_coeff_energy_b")),
  _iz_coeff_energy_c(getMaterialProperty<Real>("iz_coeff_energy_c")),
  _rate_coeff_elastic(getMaterialProperty<Real>("rate_coeff_elastic")),
  _N_A(getMaterialProperty<Real>("N_A")),
  _Eiz(getMaterialProperty<Real>("Eiz")),

// Kernel members

  // _alpha(0.0),
  // _Pe(0.0),
  // _vd_mag(0.0),
  // _delta(0.0)
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

ElectronEnergyBolosKernel::~ElectronEnergyBolosKernel()
{}

Real
ElectronEnergyBolosKernel::computeQpResidual()
{
  // _vd_mag = std::abs(_muel[_qp]*_grad_potential[_qp].size());
  // _Pe = _vd_mag*_current_elem->hmax()/_diffel[_qp];
  // _alpha = std::min(1.0,_Pe/6.0);
  // _delta = _alpha*_vd_mag*_current_elem->hmax()/2.0;
  _actual_mean_en = std::exp(_u[_qp]-_em[_qp]);
  _iz = _iz_coeff_energy_a[_qp]*std::pow(_actual_mean_en,_iz_coeff_energy_b[_qp])*std::exp(-_iz_coeff_energy_c[_qp]/_actual_mean_en);

  if ( _townsend ) {
    _electron_flux_mag = (-_muem[_qp]*-_grad_potential[_qp]*std::exp(_em[_qp])-_diffem[_qp]*std::exp(_em[_qp])*_grad_em[_qp]).size();
    _source_term = _iz * _electron_flux_mag;
  }
  else
    _source_term = _iz * _Ar[_qp] * std::exp(_em[_qp]);
 
  return -_grad_test[_i][_qp]*std::exp(_u[_qp])*(-_muel[_qp]*-_grad_potential[_qp] // Advective motion
  						 -_diffel[_qp]*_grad_u[_qp]) // Diffusive motion
    +_test[_i][_qp]*-_grad_potential[_qp]*(-_muem[_qp]*std::exp(_em[_qp])*-_grad_potential[_qp] // Joule Heating
  						-_diffem[_qp]*std::exp(_em[_qp])*_grad_em[_qp]) // Joule Heating
         -_test[_i][_qp]*_source_term*-_Eiz[_qp] // Ionization term
         -_test[_i][_qp]*-_rate_coeff_elastic[_qp]*_Ar[_qp]*3.0*_mem[_qp]/_mip[_qp]*2.0/3*std::exp(_u[_qp]) // Energy loss from elastic collisions
    -_test[_i][_qp]*_N_A[_qp]*std::exp(-_u[_qp]); // Source stabilization
  	 // -_grad_test[_i][_qp]*(-_delta*std::exp(_u[_qp])*_grad_u[_qp]); // Diffusion stabilization
}

Real
ElectronEnergyBolosKernel::computeQpJacobian()
{
  // _vd_mag = std::abs(_muel[_qp]*_grad_potential[_qp].size());
  // _Pe = _vd_mag*_current_elem->hmax()/_diffel[_qp];
  // _alpha = std::min(1.0,_Pe/6.0);
  // _delta = _alpha*_vd_mag*_current_elem->hmax()/2.0;
  _actual_mean_en = std::exp(_u[_qp]-_em[_qp]);
  _iz = _iz_coeff_energy_a[_qp]*std::pow(_actual_mean_en,_iz_coeff_energy_b[_qp])*std::exp(-_iz_coeff_energy_c[_qp]/_actual_mean_en);
  _d_iz_d_actual_mean_en = std::pow(_actual_mean_en,_iz_coeff_energy_b[_qp]-2.0)*_iz_coeff_energy_a[_qp]*(_actual_mean_en*_iz_coeff_energy_b[_qp] + _iz_coeff_energy_c[_qp])*std::exp(-_iz_coeff_energy_c[_qp]/_actual_mean_en);
  _d_actual_mean_en_d_mean_en = std::exp(_u[_qp]-_em[_qp])*_phi[_j][_qp];
  _d_iz_d_mean_en = _d_iz_d_actual_mean_en * _d_actual_mean_en_d_mean_en;

  if ( _townsend ) {
    _electron_flux = -_muem[_qp]*-_grad_potential[_qp]*std::exp(_em[_qp])-_diffem[_qp]*std::exp(_em[_qp])*_grad_em[_qp];
    _electron_flux_mag = _electron_flux.size();

    _d_source_term_d_mean_en = _electron_flux_mag * _d_iz_d_mean_en;
  }

  else {
    _d_source_term_d_mean_en = std::exp(_em[_qp]) * _Ar[_qp] * _d_iz_d_mean_en;
  }

  return  -_grad_test[_i][_qp]*(-_muel[_qp]*-_grad_potential[_qp]*std::exp(_u[_qp])*_phi[_j][_qp] // Advective motion
  			       -_diffel[_qp]*_grad_phi[_j][_qp]*std::exp(_u[_qp])-_diffel[_qp]*_grad_u[_qp]*std::exp(_u[_qp])*_phi[_j][_qp]) // Diffusive motion
    -_test[_i][_qp] * _d_source_term_d_mean_en * -_Eiz[_qp]
    -_test[_i][_qp]*-_rate_coeff_elastic[_qp]*_Ar[_qp]*3.0*_mem[_qp]/_mip[_qp]*2.0/3*std::exp(_u[_qp])*_phi[_j][_qp] // Energy loss from elastic collisions
    -_test[_i][_qp]*_N_A[_qp]*std::exp(-_u[_qp])*-1.0*_phi[_j][_qp]; // Source stabilization
  	 // -_grad_test[_i][_qp]*(-_delta*(std::exp(_u[_qp])*_grad_phi[_j][_qp]+std::exp(_u[_qp])*_phi[_j][_qp]*_grad_u[_qp])); // Diffusion stabilization
}

Real
ElectronEnergyBolosKernel::computeQpOffDiagJacobian(unsigned int jvar)
{
  _actual_mean_en = std::exp(_u[_qp]-_em[_qp]);
  _iz = _iz_coeff_energy_a[_qp]*std::pow(_actual_mean_en,_iz_coeff_energy_b[_qp])*std::exp(-_iz_coeff_energy_c[_qp]/_actual_mean_en);
  _d_iz_d_actual_mean_en = std::pow(_actual_mean_en,_iz_coeff_energy_b[_qp]-2.0)*_iz_coeff_energy_a[_qp]*(_actual_mean_en*_iz_coeff_energy_b[_qp] + _iz_coeff_energy_c[_qp])*std::exp(-_iz_coeff_energy_c[_qp]/_actual_mean_en);
  _d_actual_mean_en_d_em = -std::exp(_u[_qp]-_em[_qp])*_phi[_j][_qp];
  _d_iz_d_em = _d_iz_d_actual_mean_en * _d_actual_mean_en_d_em;

  if ( _townsend ) {
    _electron_flux = -_muem[_qp]*-_grad_potential[_qp]*std::exp(_em[_qp])-_diffem[_qp]*std::exp(_em[_qp])*_grad_em[_qp];
    _d_electron_flux_d_potential = -_muem[_qp]*-_grad_phi[_j][_qp]*std::exp(_em[_qp]);
    _d_electron_flux_d_em = -_muem[_qp]*-_grad_potential[_qp]*std::exp(_em[_qp])*_phi[_j][_qp]-_diffem[_qp]*(std::exp(_em[_qp])*_phi[_j][_qp]*_grad_em[_qp]+std::exp(_em[_qp])*_grad_phi[_j][_qp]);
    _electron_flux_mag = _electron_flux.size();
    _d_electron_flux_mag_d_potential = _electron_flux*_d_electron_flux_d_potential/(_electron_flux_mag+std::numeric_limits<double>::epsilon());
    _d_electron_flux_mag_d_em = _electron_flux*_d_electron_flux_d_em/(_electron_flux_mag+std::numeric_limits<double>::epsilon());

    _d_source_term_d_em = _iz * _d_electron_flux_mag_d_em + _electron_flux_mag * _d_iz_d_em;
    _d_source_term_d_potential = _iz * _d_electron_flux_mag_d_potential;
  }

  else {
    _d_source_term_d_em = std::exp(_em[_qp]) * _Ar[_qp] * _d_iz_d_em + _iz * _Ar[_qp] * std::exp(_em[_qp]) * _phi[_j][_qp];
    _d_source_term_d_potential = 0.0;
  }

  if (jvar == _potential_id) {
    return -_grad_test[_i][_qp]*std::exp(_u[_qp])*(-_muel[_qp]*-_grad_phi[_j][_qp]) // Advective motion
           +_test[_i][_qp]*(-_grad_phi[_j][_qp]*(-_muem[_qp]*std::exp(_em[_qp])*-_grad_potential[_qp] // Joule Heating
    						 -_diffem[_qp]*std::exp(_em[_qp])*_grad_em[_qp]) // Joule Heating
    			    -_grad_potential[_qp]*(-_muem[_qp]*std::exp(_em[_qp])*-_grad_phi[_j][_qp])) // Joule Heating
	     -_test[_i][_qp] * _d_source_term_d_potential * -_Eiz[_qp];
  }

  else if (jvar == _em_id) {
    return +_test[_i][_qp]*-_grad_potential[_qp]*(-_muem[_qp]*std::exp(_em[_qp])*_phi[_j][_qp]*-_grad_potential[_qp] // Joule Heating
    						  -_diffem[_qp]*(std::exp(_em[_qp])*_grad_phi[_j][_qp]+std::exp(_em[_qp])*_phi[_j][_qp]*_grad_em[_qp])) // Joule Heating
      -_test[_i][_qp] * _d_source_term_d_em * -_Eiz[_qp];
  }

  else {
    return 0.0;
  }

}
