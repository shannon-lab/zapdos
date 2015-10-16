#ifndef ELECTRONBOLOSKERNELENERGYFORM_H
#define ELECTRONBOLOSKERNELENERGYFORM_H

#include "Kernel.h"

class ElectronBolosKernelEnergyForm;

template<>
InputParameters validParams<ElectronBolosKernelEnergyForm>();

class ElectronBolosKernelEnergyForm : public Kernel
{
 public:
  ElectronBolosKernelEnergyForm(const InputParameters & parameters);
  virtual ~ElectronBolosKernelEnergyForm();

 protected:
  
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // coupled vars

  VariableValue & _mean_en;
  unsigned int _mean_en_id;
  VariableGradient & _grad_potential;
  unsigned int _potential_id;

  // Kernel members

  /* Real _alpha; */
  /* Real _Pe; */
  /* Real _vd_mag; */
  /* Real _delta; */
  bool _townsend;
  bool _use_interp_for_townsend;
  /* bool _estim_jac_with_function; */
  Real  _actual_mean_en;
  Real  _iz;
  Real  _d_iz_d_actual_mean_en_member;
  Real  _d_actual_mean_en_d_em;
  Real  _d_actual_mean_en_d_mean_en;
  Real  _d_iz_d_em;
  Real  _d_iz_d_mean_en;
  RealVectorValue  _electron_flux;
  RealVectorValue  _d_electron_flux_d_potential;
  RealVectorValue  _d_electron_flux_d_em;
  Real  _electron_flux_mag;
  Real  _d_electron_flux_mag_d_potential;
  Real  _d_electron_flux_mag_d_em;
  Real  _source_term;
  Real  _d_source_term_d_em;
  Real  _d_source_term_d_mean_en;
  Real  _d_source_term_d_potential;

  const MaterialProperty<Real> & _muem;
  const MaterialProperty<Real> & _diffem;
  const MaterialProperty<Real> & _Ar;
  const MaterialProperty<Real> & _iz_coeff_energy_a;
  const MaterialProperty<Real> & _iz_coeff_energy_b;
  const MaterialProperty<Real> & _iz_coeff_energy_c;
  const MaterialProperty<Real> & _N_A;
  const MaterialProperty<Real> & _alpha_iz;
  const MaterialProperty<Real> & _d_iz_d_actual_mean_en;
};

#endif /* ELECTRONBOLOSKERNELENERGYFORM_H */
