#ifndef ELECTRONENERGYBOLOSKERNEL_H
#define ELECTRONENERGYBOLOSKERNEL_H

#include "Kernel.h"

class ElectronEnergyBolosKernel;

template<>
InputParameters validParams<ElectronEnergyBolosKernel>();

class ElectronEnergyBolosKernel : public Kernel
{
 public:
  ElectronEnergyBolosKernel(const InputParameters & parameters);
  virtual ~ElectronEnergyBolosKernel();

 protected:
  
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // coupled vars

  VariableValue & _em;
  VariableGradient & _grad_em;
  unsigned int _em_id;
  VariableGradient & _grad_potential;
  unsigned int _potential_id;

  // Material properties

  const MaterialProperty<Real> & _muel;
  const MaterialProperty<Real> & _muem;
  const MaterialProperty<Real> & _diffem;
  const MaterialProperty<Real> & _diffel;
  const MaterialProperty<Real> & _Ar;
  const MaterialProperty<Real> & _mem;
  const MaterialProperty<Real> & _mip;
  const MaterialProperty<Real> & _iz_coeff_energy_a;
  const MaterialProperty<Real> & _iz_coeff_energy_b;
  const MaterialProperty<Real> & _iz_coeff_energy_c;
  const MaterialProperty<Real> & _rate_coeff_elastic;
  const MaterialProperty<Real> & _N_A;
  const MaterialProperty<Real> & _Eiz;

  // kernel members

  /* Real _alpha; */
  /* Real _Pe; */
  /* Real _vd_mag; */
  /* Real _delta; */
  bool _townsend;
  Real  _actual_mean_en;
  Real  _iz;
  Real  _d_iz_d_actual_mean_en;
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
};

#endif /* ELECTRONENERGYBOLOSKERNEL_H */
