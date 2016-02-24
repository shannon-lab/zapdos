#ifndef IONBOLOSKERNEL_H
#define IONBOLOSKERNEL_H

#include "Kernel.h"

class IonBolosKernel;

template<>
InputParameters validParams<IonBolosKernel>();

class IonBolosKernel : public Kernel
{
 public:
  IonBolosKernel(const InputParameters & parameters);
  virtual ~IonBolosKernel();

 protected:
  
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // coupled vars

  const VariableValue & _em;
  const VariableGradient & _grad_em;
  unsigned int _em_id;
  const VariableGradient & _grad_potential;
  unsigned int _potential_id;

  // Material Properties

  const MaterialProperty<Real> &  _muem;
  const MaterialProperty<Real> &  _diffem;
  const MaterialProperty<Real> &  _muip;
  const MaterialProperty<Real> &  _diffip;
  const MaterialProperty<Real> &  _iz_coeff_efield_a;
  const MaterialProperty<Real> &  _iz_coeff_efield_b;
  const MaterialProperty<Real> &  _iz_coeff_efield_c;

  // Kernel members

  Real  _alpha;
  Real  _Pe;
  Real  _vd_mag;
  Real  _delta;
  RealVectorValue _em_flux;
  Real _em_flux_mag;
  RealVectorValue _d_em_flux_d_em;
  RealVectorValue _d_em_flux_d_potential;
  Real _d_em_flux_mag_d_potential;
  Real _iz;
  Real _d_iz_d_potential;
};

#endif /* IONBOLOSKERNEL_H */
