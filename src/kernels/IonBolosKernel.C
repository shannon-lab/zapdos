#include "IonBolosKernel.h"

template<>
InputParameters validParams<IonBolosKernel>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredCoupledVar("potential", "The electric potential");
  params.addRequiredCoupledVar("em", "The electron density");
  // params.addRequiredCoupledVar("mean_en", "The electront temperature");
  return params;
}

IonBolosKernel::IonBolosKernel(const InputParameters & parameters) :
  Kernel(parameters),

  _em(coupledValue("em")),
  _grad_em(coupledGradient("em")),
  _em_id(coupled("em")),
  _grad_potential(coupledGradient("potential")),
  _potential_id(coupled("potential")),

  // Material Properties

  _muem(getMaterialProperty<Real>("muem")),
  _diffem(getMaterialProperty<Real>("diffem")),
  _muip(getMaterialProperty<Real>("muip")),
  _diffip(getMaterialProperty<Real>("diffip")),
  _iz_coeff_efield_a(getMaterialProperty<Real>("iz_coeff_efield_a")),
  _iz_coeff_efield_b(getMaterialProperty<Real>("iz_coeff_efield_b")),
  _iz_coeff_efield_c(getMaterialProperty<Real>("iz_coeff_efield_c")),

  // Kernel members

  _alpha(0.0),
  _Pe(0.0),
  _vd_mag(0.0),
  _delta(0.0),
  _em_flux(0.0,0.0,0.0),
  _em_flux_mag(0.0),
  _d_em_flux_d_em(0.0,0.0,0.0),
  _d_em_flux_d_potential(0.0,0.0,0.0),
  _d_em_flux_mag_d_potential(0.0),
  _iz(0.0),
  _d_iz_d_potential(0.0)
{}

IonBolosKernel::~IonBolosKernel()
{}

Real
IonBolosKernel::computeQpResidual()
{
  // _vd_mag = std::abs(_muip[_qp]*_grad_potential[_qp].size());
  // _Pe = _vd_mag*_current_elem->hmax()/_diffip[_qp];
  // _alpha = std::min(1.0,_Pe/6.0);
  // _delta = _alpha*_vd_mag*_current_elem->hmax()/2.0;
 
  return -_grad_test[_i][_qp]*std::exp(_u[_qp])*(_muip[_qp]*-_grad_potential[_qp]-_diffip[_qp]*_grad_u[_qp])
    -_test[_i][_qp]*_iz_coeff_efield_a[_qp]*std::pow(_grad_potential[_qp].size()+std::numeric_limits<double>::epsilon(),_iz_coeff_efield_b[_qp])*std::exp(-_iz_coeff_efield_c[_qp]/(_grad_potential[_qp].size()+std::numeric_limits<double>::epsilon()))*(-_muem[_qp]*-_grad_potential[_qp]*std::exp(_em[_qp])-_diffem[_qp]*std::exp(_em[_qp])*_grad_em[_qp]).size(); // Reaction. Townsend coefficient formulation
    // -_grad_test[_i][_qp]*(-_delta*std::exp(_u[_qp])*_grad_u[_qp]); // Diffusion stabilization
}

Real
IonBolosKernel::computeQpJacobian()
{
  // _vd_mag = std::abs(_muip[_qp]*_grad_potential[_qp].size());
  // _Pe = _vd_mag*_current_elem->hmax()/_diffip[_qp];
  // _alpha = std::min(1.0,_Pe/6.0);
  // _delta = _alpha*_vd_mag*_current_elem->hmax()/2.0;

  return -_grad_test[_i][_qp]*(_muip[_qp]*-_grad_potential[_qp]*std::exp(_u[_qp])*_phi[_j][_qp]-_diffip[_qp]*(std::exp(_u[_qp])*_grad_phi[_j][_qp]+std::exp(_u[_qp])*_phi[_j][_qp]*_grad_u[_qp]))
    -_grad_test[_i][_qp]*(-_delta*(std::exp(_u[_qp])*_grad_phi[_j][_qp]+std::exp(_u[_qp])*_phi[_j][_qp]*_grad_u[_qp])); // Diffusion stabilization
}

Real
IonBolosKernel::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id) {
    _em_flux = -_muem[_qp]*-_grad_potential[_qp]*std::exp(_em[_qp])-_diffem[_qp]*std::exp(_em[_qp])*_grad_em[_qp];
    _em_flux_mag = _em_flux.size();
    _d_em_flux_d_potential = -_muem[_qp]*-_grad_phi[_j][_qp]*std::exp(_em[_qp]);
    _d_em_flux_mag_d_potential = _em_flux*_d_em_flux_d_potential/(_em_flux_mag+std::numeric_limits<double>::epsilon());
    _iz = _iz_coeff_efield_a[_qp]*std::pow(_grad_potential[_qp].size()+std::numeric_limits<double>::epsilon(),_iz_coeff_efield_b[_qp])*std::exp(-_iz_coeff_efield_c[_qp]/(_grad_potential[_qp].size()+std::numeric_limits<double>::epsilon()));
    _d_iz_d_potential = std::pow(_grad_potential[_qp].size()+std::numeric_limits<double>::epsilon(),_iz_coeff_efield_b[_qp]-2.0)*_iz_coeff_efield_a[_qp]*(_grad_potential[_qp].size()*_iz_coeff_efield_b[_qp]+_iz_coeff_efield_c[_qp])*std::exp(-_iz_coeff_efield_c[_qp]/(_grad_potential[_qp].size()+std::numeric_limits<double>::epsilon()))*_grad_potential[_qp]*_grad_phi[_j][_qp]/(_grad_potential[_qp].size()+std::numeric_limits<double>::epsilon());

    return -_grad_test[_i][_qp]*(_muip[_qp]*-_grad_phi[_j][_qp]*std::exp(_u[_qp]))
      -_test[_i][_qp]*(_iz*_d_em_flux_mag_d_potential + _d_iz_d_potential*_em_flux_mag); // Reaction. Townsend coefficient formulation
  }

  else if (jvar == _em_id) {
    _em_flux = -_muem[_qp]*-_grad_potential[_qp]*std::exp(_em[_qp])-_diffem[_qp]*std::exp(_em[_qp])*_grad_em[_qp];
    _d_em_flux_d_em = -_muem[_qp]*-_grad_potential[_qp]*std::exp(_em[_qp])*_phi[_j][_qp]-_diffem[_qp]*(std::exp(_em[_qp])*_grad_phi[_j][_qp]+std::exp(_em[_qp])*_phi[_j][_qp]*_grad_em[_qp]);
    _iz = _iz_coeff_efield_a[_qp]*std::pow(_grad_potential[_qp].size()+std::numeric_limits<double>::epsilon(),_iz_coeff_efield_b[_qp])*std::exp(-_iz_coeff_efield_c[_qp]/(_grad_potential[_qp].size()+std::numeric_limits<double>::epsilon()));

    return -_test[_i][_qp]*_iz*_em_flux*_d_em_flux_d_em/(_em_flux.size()+std::numeric_limits<double>::epsilon()); // Reaction. Townsend coefficient formulation

  }

  else {
    return 0.0;
  }
}

