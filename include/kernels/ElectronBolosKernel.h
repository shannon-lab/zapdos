#ifndef ELECTRONBOLOSKERNEL_H
#define ELECTRONBOLOSKERNEL_H

#include "Kernel.h"

class ElectronBolosKernel;

template<>
InputParameters validParams<ElectronBolosKernel>();

class ElectronBolosKernel : public Kernel
{
 public:
  ElectronBolosKernel(const InputParameters & parameters);
  virtual ~ElectronBolosKernel();

 protected:
  
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // coupled vars

  /* VariableValue & _mean_en; */
  /* unsigned int _mean_en_id; */
  VariableGradient & _grad_potential;
  unsigned int _potential_id;

  // Kernel members

  Real _alpha;
  Real _Pe;
  Real _vd_mag;
  Real _delta;
  RealVectorValue _em_flux;
  Real _em_flux_mag;
  RealVectorValue _d_em_flux_d_em;
  RealVectorValue _d_em_flux_d_potential;
  Real _d_em_flux_mag_d_potential;
  Real _iz;
  Real _d_iz_d_potential;

  const MaterialProperty<Real> & _muem;
  const MaterialProperty<Real> & _diffem;
  const MaterialProperty<Real> &  _iz_coeff_efield_a;
  const MaterialProperty<Real> &  _iz_coeff_efield_b;
  const MaterialProperty<Real> &  _iz_coeff_efield_c;
};

#endif /* ELECTRONBOLOSKERNEL_H */
