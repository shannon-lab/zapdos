#include "ElectronEnergyBolosKernel.h"

template<>
InputParameters validParams<ElectronEnergyBolosKernel>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredCoupledVar("em", "The electron density");
  params.addRequiredCoupledVar("potential","The electric potential");
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
  _Eex(getMaterialProperty<Real>("Eex")),
  _el_coeff_energy_a(getMaterialProperty<Real>("el_coeff_energy_a")),
  _el_coeff_energy_b(getMaterialProperty<Real>("el_coeff_energy_b")),
  _el_coeff_energy_c(getMaterialProperty<Real>("el_coeff_energy_c")),
  _alpha_iz(getMaterialProperty<Real>("alpha_iz")),
  _d_iz_d_actual_mean_en(getMaterialProperty<Real>("d_iz_d_actual_mean_en")),
  _alpha_ex(getMaterialProperty<Real>("alpha_ex")),
  _d_ex_d_actual_mean_en(getMaterialProperty<Real>("d_ex_d_actual_mean_en")),
  _d_el_d_actual_mean_en(getMaterialProperty<Real>("d_el_d_actual_mean_en")),
  _d_muem_d_actual_mean_en(getMaterialProperty<Real>("d_muem_d_actual_mean_en")),
  _d_diffem_d_actual_mean_en(getMaterialProperty<Real>("d_diffem_d_actual_mean_en")),
  _d_muel_d_actual_mean_en(getMaterialProperty<Real>("d_muel_d_actual_mean_en")),
  _d_diffel_d_actual_mean_en(getMaterialProperty<Real>("d_diffel_d_actual_mean_en")),
  _alpha_el(getMaterialProperty<Real>("alpha_el"))
{
}

ElectronEnergyBolosKernel::~ElectronEnergyBolosKernel()
{}

Real
ElectronEnergyBolosKernel::computeQpResidual()
{
  Real _electron_flux_mag = (-_muem[_qp]*-_grad_potential[_qp]*std::exp(_em[_qp])-_diffem[_qp]*std::exp(_em[_qp])*_grad_em[_qp]).norm();
  Real _iz_term = _alpha_iz[_qp] * _electron_flux_mag * -_Eiz[_qp];
  Real _ex_term = _alpha_ex[_qp] * _electron_flux_mag * -_Eex[_qp];
  Real _Eel = 3.0*_mem[_qp]/_mip[_qp]*2.0/3*std::exp(_u[_qp]-_em[_qp]);
  Real _el_term = _alpha_el[_qp] * _electron_flux_mag * -_Eel;

  return -_grad_test[_i][_qp]*std::exp(_u[_qp])*(-_muel[_qp]*-_grad_potential[_qp]
  						 -_diffel[_qp]*_grad_u[_qp])
    +_test[_i][_qp]*-_grad_potential[_qp]*(-_muem[_qp]*std::exp(_em[_qp])*-_grad_potential[_qp]
					   -_diffem[_qp]*std::exp(_em[_qp])*_grad_em[_qp])
    -_test[_i][_qp]*_iz_term
    // -_test[_i][_qp]*_ex_term
    -_test[_i][_qp]*_el_term
    -_test[_i][_qp]*_N_A[_qp]*std::exp(-_u[_qp]);
  // -_grad_test[_i][_qp]*(-_delta*std::exp(_u[_qp])*_grad_u[_qp]);
}

Real
ElectronEnergyBolosKernel::computeQpJacobian()
{
  Real _actual_mean_en = std::exp(_u[_qp]-_em[_qp]);
  Real _d_actual_mean_en_d_mean_en = std::exp(_u[_qp]-_em[_qp])*_phi[_j][_qp];
  Real _d_iz_d_mean_en = _d_iz_d_actual_mean_en[_qp] * _d_actual_mean_en_d_mean_en;
  Real _d_ex_d_mean_en = _d_ex_d_actual_mean_en[_qp] * _d_actual_mean_en_d_mean_en;
  Real _d_el_d_mean_en = _d_el_d_actual_mean_en[_qp] * _d_actual_mean_en_d_mean_en;
  Real _d_muem_d_mean_en = _d_muem_d_actual_mean_en[_qp] * _d_actual_mean_en_d_mean_en;
  Real _d_diffem_d_mean_en = _d_diffem_d_actual_mean_en[_qp] * _d_actual_mean_en_d_mean_en;
  Real _d_muel_d_mean_en = _d_muel_d_actual_mean_en[_qp] * _d_actual_mean_en_d_mean_en;
  Real _d_diffel_d_mean_en = _d_diffel_d_actual_mean_en[_qp] * _d_actual_mean_en_d_mean_en;

  RealVectorValue _electron_flux = -_muem[_qp]*-_grad_potential[_qp]*std::exp(_em[_qp])-_diffem[_qp]*std::exp(_em[_qp])*_grad_em[_qp];
  RealVectorValue _d_electron_flux_d_mean_en = -_d_muem_d_mean_en*-_grad_potential[_qp]*std::exp(_em[_qp])-_d_diffem_d_mean_en*std::exp(_em[_qp])*_grad_em[_qp];
  Real _electron_flux_mag = _electron_flux.norm();
  Real _d_electron_flux_mag_d_mean_en = _electron_flux*_d_electron_flux_d_mean_en/(_electron_flux_mag+std::numeric_limits<double>::epsilon());

  Real _d_Joule_d_mean_en = -_grad_potential[_qp] * _d_electron_flux_d_mean_en;

  Real _elastic_loss = -3.0*_mem[_qp]/_mip[_qp]*2.0/3*std::exp(_u[_qp]-_em[_qp]);
  Real _d_elastic_loss_d_mean_en = -3.0*_mem[_qp]/_mip[_qp]*2.0/3*std::exp(_u[_qp]-_em[_qp])*_phi[_j][_qp];

  Real _d_iz_term_d_mean_en = -_Eiz[_qp]*(_electron_flux_mag * _d_iz_d_mean_en + _alpha_iz[_qp] * _d_electron_flux_mag_d_mean_en);
  Real _d_ex_term_d_mean_en = -_Eex[_qp]*(_electron_flux_mag * _d_ex_d_mean_en + _alpha_ex[_qp] * _d_electron_flux_mag_d_mean_en);
  Real _d_el_term_d_mean_en = (_electron_flux_mag * _d_el_d_mean_en + _alpha_el[_qp] * _d_electron_flux_mag_d_mean_en)*_elastic_loss + _electron_flux_mag*_alpha_el[_qp]*_d_elastic_loss_d_mean_en;
  RealVectorValue _d_en_adflux_d_mean_en = _grad_potential[_qp]*(_d_muel_d_mean_en*std::exp(_u[_qp]) + _muel[_qp]*std::exp(_u[_qp])*_phi[_j][_qp]);
  RealVectorValue _d_en_difflux_d_mean_en = -(_d_diffel_d_mean_en*std::exp(_u[_qp])*_grad_u[_qp] + _diffel[_qp]*(std::exp(_u[_qp])*_grad_phi[_j][_qp] + _grad_u[_qp]*std::exp(_u[_qp])*_phi[_j][_qp]));

  return  -_grad_test[_i][_qp]*(_d_en_adflux_d_mean_en + _d_en_difflux_d_mean_en)
    +_test[_i][_qp] * _d_Joule_d_mean_en
    -_test[_i][_qp] * _d_iz_term_d_mean_en
    // -_test[_i][_qp] * _d_ex_term_d_mean_en
    -_test[_i][_qp] * _d_el_term_d_mean_en
    -_test[_i][_qp]*_N_A[_qp]*std::exp(-_u[_qp])*-1.0*_phi[_j][_qp]; 
  	 // -_grad_test[_i][_qp]*(-_delta*(std::exp(_u[_qp])*_grad_phi[_j][_qp]+std::exp(_u[_qp])*_phi[_j][_qp]*_grad_u[_qp])); // Diffusion stabilization
}

Real
ElectronEnergyBolosKernel::computeQpOffDiagJacobian(unsigned int jvar)
{
  Real _actual_mean_en = std::exp(_u[_qp]-_em[_qp]);
  Real _d_actual_mean_en_d_em = -std::exp(_u[_qp]-_em[_qp])*_phi[_j][_qp];
  Real _d_iz_d_em = _d_iz_d_actual_mean_en[_qp] * _d_actual_mean_en_d_em;
  Real _d_ex_d_em = _d_ex_d_actual_mean_en[_qp] * _d_actual_mean_en_d_em;
  Real _d_el_d_em = _d_el_d_actual_mean_en[_qp] * _d_actual_mean_en_d_em;
  Real _d_muem_d_em = _d_muem_d_actual_mean_en[_qp] * _d_actual_mean_en_d_em;
  Real _d_diffem_d_em = _d_diffem_d_actual_mean_en[_qp] * _d_actual_mean_en_d_em;
  Real _d_muel_d_em = _d_muel_d_actual_mean_en[_qp] * _d_actual_mean_en_d_em;
  Real _d_diffel_d_em = _d_diffel_d_actual_mean_en[_qp] * _d_actual_mean_en_d_em;

  RealVectorValue _d_en_adflux_d_em = -_d_muel_d_em*-_grad_potential[_qp]*std::exp(_u[_qp]);
  RealVectorValue _d_en_adflux_d_potential = -_muel[_qp]*-_grad_phi[_j][_qp]*std::exp(_u[_qp]);

  RealVectorValue _d_en_difflux_d_em = -_d_diffel_d_em*std::exp(_u[_qp])*_grad_u[_qp];
  RealVectorValue _d_en_difflux_d_potential = 0.0;

  RealVectorValue _electron_flux = -_muem[_qp]*-_grad_potential[_qp]*std::exp(_em[_qp])-_diffem[_qp]*std::exp(_em[_qp])*_grad_em[_qp];
  RealVectorValue _d_electron_flux_d_em = -_d_muem_d_em*-_grad_potential[_qp]*std::exp(_em[_qp])-_muem[_qp]*-_grad_potential[_qp]*std::exp(_em[_qp])*_phi[_j][_qp]-_d_diffem_d_em*std::exp(_em[_qp])*_grad_em[_qp]-_diffem[_qp]*std::exp(_em[_qp])*_phi[_j][_qp]*_grad_em[_qp]-_diffem[_qp]*std::exp(_em[_qp])*_grad_phi[_j][_qp];
  RealVectorValue _d_electron_flux_d_potential = -_muem[_qp]*-_grad_phi[_j][_qp]*std::exp(_em[_qp]);
  Real _electron_flux_mag = _electron_flux.norm();
  Real _d_electron_flux_mag_d_em = _electron_flux*_d_electron_flux_d_em/(_electron_flux_mag+std::numeric_limits<double>::epsilon());
  Real _d_electron_flux_mag_d_potential = _electron_flux*_d_electron_flux_d_potential/(_electron_flux_mag+std::numeric_limits<double>::epsilon());

  Real _d_Joule_d_potential = -_grad_phi[_j][_qp]*_electron_flux - _grad_potential[_qp]*_d_electron_flux_d_potential;
  Real _d_Joule_d_em = -_grad_potential[_qp]*_d_electron_flux_d_em;

  Real _d_iz_term_d_em = -_Eiz[_qp]*(_electron_flux_mag * _d_iz_d_em + _alpha_iz[_qp] * _d_electron_flux_mag_d_em);
  Real _d_iz_term_d_potential = -_Eiz[_qp]*(_alpha_iz[_qp] * _d_electron_flux_mag_d_potential);

  Real _d_ex_term_d_em = -_Eex[_qp]*(_electron_flux_mag * _d_ex_d_em + _alpha_ex[_qp] * _d_electron_flux_mag_d_em);
  Real _d_ex_term_d_potential = -_Eex[_qp]*(_alpha_ex[_qp] * _d_electron_flux_mag_d_potential);

  Real _elastic_loss = -3.0*_mem[_qp]/_mip[_qp]*2.0/3*std::exp(_u[_qp]-_em[_qp]);
  Real _d_elastic_loss_d_em = -3.0*_mem[_qp]/_mip[_qp]*2.0/3*std::exp(_u[_qp]-_em[_qp])*-_phi[_j][_qp];
  Real _d_elastic_loss_d_potential = 0.0;

  Real _d_el_term_d_em = (_electron_flux_mag * _d_el_d_em + _alpha_el[_qp] * _d_electron_flux_mag_d_em)*_elastic_loss + _electron_flux_mag*_alpha_el[_qp]*_d_elastic_loss_d_em;
  Real _d_el_term_d_potential = (_alpha_el[_qp] * _d_electron_flux_mag_d_potential)*_elastic_loss + _electron_flux_mag*_alpha_el[_qp]*_d_elastic_loss_d_potential;

  if (jvar == _potential_id) {
    return -_grad_test[_i][_qp]*(_d_en_adflux_d_potential + _d_en_difflux_d_potential)
      +_test[_i][_qp]*_d_Joule_d_potential
      -_test[_i][_qp] * _d_iz_term_d_potential
      // -_test[_i][_qp] * _d_ex_term_d_potential
      -_test[_i][_qp] * _d_el_term_d_potential;
  }

  else if (jvar == _em_id) {
    return -_grad_test[_i][_qp]*(_d_en_adflux_d_em + _d_en_difflux_d_em)
      +_test[_i][_qp]*_d_Joule_d_em
      -_test[_i][_qp] * _d_iz_term_d_em
      // -_test[_i][_qp] * _d_ex_term_d_em
      -_test[_i][_qp] * _d_el_term_d_em;
  }

  else {
    return 0.0;
  }

}
