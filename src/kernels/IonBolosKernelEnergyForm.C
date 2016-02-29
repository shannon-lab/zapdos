#include "IonBolosKernelEnergyForm.h"

template<>
InputParameters validParams<IonBolosKernelEnergyForm>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredCoupledVar("potential", "The electric potential");
  params.addRequiredCoupledVar("em", "The electron density");
  params.addRequiredCoupledVar("mean_en", "The electront temperature");
  // params.addRequiredParam<bool>("townsend","Whether to use the townsend formulation for the ionization term.");
  // params.addRequiredParam<bool>("use_interp_for_townsend","Whether to use interpolated data as opposed to a model functional fit for the townsend coeffient.");
  // params.addRequiredParam<bool>("estim_jac_with_function","If using interpolation for townsend, whether to use inexact function to estimate Jacobian.");
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
  _alpha_iz(getMaterialProperty<Real>("alpha_iz")),
  _d_iz_d_actual_mean_en(getMaterialProperty<Real>("d_iz_d_actual_mean_en")),
  _d_muem_d_actual_mean_en(getMaterialProperty<Real>("d_muem_d_actual_mean_en")),
  _d_diffem_d_actual_mean_en(getMaterialProperty<Real>("d_diffem_d_actual_mean_en"))

  // Kernel members

  // _alpha(0.0),
  // _Pe(0.0),
  // _vd_mag(0.0),
  // _delta(0.0),
  // _townsend(getParam<bool>("townsend")),
  // _use_interp_for_townsend(getParam<bool>("use_interp_for_townsend")),
  // // _estim_jac_with_function(getParam<bool>("estim_jac_with_function")),
  // _actual_mean_en(0.0),
  // _iz(0.0),
  // _d_iz_d_actual_mean_en_member(0.0),
  // _d_actual_mean_en_d_em(0.0),
  // _d_actual_mean_en_d_mean_en(0.0),
  // _d_iz_d_em(0.0),
  // _d_iz_d_mean_en(0.0),
  // _electron_flux(0.0,0.0,0.0),
  // _d_electron_flux_d_potential(0.0,0.0,0.0),
  // _d_electron_flux_d_em(0.0,0.0,0.0),
  // _electron_flux_mag(0.0),
  // _d_electron_flux_mag_d_potential(0.0),
  // _d_electron_flux_mag_d_em(0.0),
  // _source_term(0.0),
  // _d_source_term_d_em(0.0),
  // _d_source_term_d_mean_en(0.0),
  // _d_source_term_d_potential(0.0)
{
  // if ( !_townsend && _use_interp_for_townsend )
  //   std::cerr << "Not a consistent specification of the ionization problem." << std::endl;
}

IonBolosKernelEnergyForm::~IonBolosKernelEnergyForm()
{}

Real
IonBolosKernelEnergyForm::computeQpResidual()
{
  Real  vd_mag = _muip[_qp]*_grad_potential[_qp].norm();
  Real  delta = vd_mag*_current_elem->hmax()/2.0;

  Real  _electron_flux_mag = (-_muem[_qp]*-_grad_potential[_qp]*std::exp(_em[_qp])-_diffem[_qp]*std::exp(_em[_qp])*_grad_em[_qp]).norm();
  Real _iz_term = _alpha_iz[_qp] * _electron_flux_mag;

  return -_grad_test[_i][_qp]*std::exp(_u[_qp])*(_muip[_qp]*-_grad_potential[_qp]-_diffip[_qp]*_grad_u[_qp])
    -_test[_i][_qp]*_iz_term // Ionization term
    -_test[_i][_qp]*_N_A[_qp]*std::exp(-_u[_qp]) // Source stabilization
    -_grad_test[_i][_qp]*(-delta*std::exp(_u[_qp])*_grad_u[_qp]); // Diffusion stabilization
}

Real
IonBolosKernelEnergyForm::computeQpJacobian()
{
  Real  vd_mag = _muip[_qp]*_grad_potential[_qp].norm();
  Real  delta = vd_mag*_current_elem->hmax()/2.0;

  return -_grad_test[_i][_qp]*(_muip[_qp]*-_grad_potential[_qp]*std::exp(_u[_qp])*_phi[_j][_qp]-_diffip[_qp]*(std::exp(_u[_qp])*_grad_phi[_j][_qp]+std::exp(_u[_qp])*_phi[_j][_qp]*_grad_u[_qp]))
    -_test[_i][_qp]*_N_A[_qp]*std::exp(-_u[_qp])*-1.0*_phi[_j][_qp] // Source stabilization
    -_grad_test[_i][_qp]*(-delta*std::exp(_u[_qp])*_grad_phi[_j][_qp]-delta*std::exp(_u[_qp])*_phi[_j][_qp]*_grad_u[_qp]); // Diffusion stabilization
}

Real
IonBolosKernelEnergyForm::computeQpOffDiagJacobian(unsigned int jvar)
{
  Real _actual_mean_en = std::exp(_mean_en[_qp]-_em[_qp]);
  Real _d_actual_mean_en_d_mean_en = std::exp(_mean_en[_qp]-_em[_qp])*_phi[_j][_qp];
  Real _d_iz_d_mean_en = _d_iz_d_actual_mean_en[_qp] * _d_actual_mean_en_d_mean_en;
  Real _d_muem_d_mean_en = _d_muem_d_actual_mean_en[_qp] * _d_actual_mean_en_d_mean_en;
  Real _d_diffem_d_mean_en = _d_diffem_d_actual_mean_en[_qp] * _d_actual_mean_en_d_mean_en;
  Real _d_actual_mean_en_d_em = -std::exp(_mean_en[_qp]-_em[_qp])*_phi[_j][_qp];
  Real _d_iz_d_em = _d_iz_d_actual_mean_en[_qp] * _d_actual_mean_en_d_em;
  Real _d_muem_d_em = _d_muem_d_actual_mean_en[_qp] * _d_actual_mean_en_d_em;
  Real _d_diffem_d_em = _d_diffem_d_actual_mean_en[_qp] * _d_actual_mean_en_d_em;

  RealVectorValue _electron_flux = -_muem[_qp]*-_grad_potential[_qp]*std::exp(_em[_qp])-_diffem[_qp]*std::exp(_em[_qp])*_grad_em[_qp];
  RealVectorValue _d_electron_flux_d_potential = -_muem[_qp]*-_grad_phi[_j][_qp]*std::exp(_em[_qp]);
  RealVectorValue _d_electron_flux_d_mean_en = -_d_muem_d_mean_en*-_grad_potential[_qp]*std::exp(_em[_qp])-_d_diffem_d_mean_en*std::exp(_em[_qp])*_grad_em[_qp];
  RealVectorValue _d_electron_flux_d_em = -_d_muem_d_em*-_grad_potential[_qp]*std::exp(_em[_qp])-_muem[_qp]*-_grad_potential[_qp]*std::exp(_em[_qp])*_phi[_j][_qp]-_d_diffem_d_em*std::exp(_em[_qp])*_grad_em[_qp]-_diffem[_qp]*std::exp(_em[_qp])*_phi[_j][_qp]*_grad_em[_qp]-_diffem[_qp]*std::exp(_em[_qp])*_grad_phi[_j][_qp];
  Real _electron_flux_mag = _electron_flux.norm();
  Real _d_electron_flux_mag_d_potential = _electron_flux*_d_electron_flux_d_potential/(_electron_flux_mag+std::numeric_limits<double>::epsilon());
  Real _d_electron_flux_mag_d_mean_en = _electron_flux*_d_electron_flux_d_mean_en/(_electron_flux_mag+std::numeric_limits<double>::epsilon());
  Real _d_electron_flux_mag_d_em = _electron_flux*_d_electron_flux_d_em/(_electron_flux_mag+std::numeric_limits<double>::epsilon());

  Real _d_iz_term_d_potential = (_alpha_iz[_qp] * _d_electron_flux_mag_d_potential);
  Real _d_iz_term_d_mean_en = (_electron_flux_mag * _d_iz_d_mean_en + _alpha_iz[_qp] * _d_electron_flux_mag_d_mean_en);
  Real _d_iz_term_d_em = (_electron_flux_mag * _d_iz_d_em + _alpha_iz[_qp] * _d_electron_flux_mag_d_em);

  Real  vd_mag = _muip[_qp]*_grad_potential[_qp].norm();
  Real  d_vd_mag_d_potential = _muip[_qp]*_grad_potential[_qp]*_grad_phi[_j][_qp]/(_grad_potential[_qp].norm()+std::numeric_limits<double>::epsilon());
  Real d_delta_d_potential = _current_elem->hmax()/2.0*d_vd_mag_d_potential;

  if (jvar == _potential_id)
    return -_grad_test[_i][_qp]*(_muip[_qp]*-_grad_phi[_j][_qp]*std::exp(_u[_qp])) 
      - _test[_i][_qp] * _d_iz_term_d_potential
      -_grad_test[_i][_qp] * -d_delta_d_potential * std::exp(_u[_qp]) * _grad_u[_qp];

  else if (jvar == _em_id)
    return -_test[_i][_qp] * _d_iz_term_d_em; // Ionization term

  else if (jvar == _mean_en_id)
    return -_test[_i][_qp] * _d_iz_term_d_mean_en; // Ionization term

  else
    return 0.0;
}

