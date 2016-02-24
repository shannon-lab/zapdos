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

  const VariableValue & _em;
  const VariableGradient & _grad_em;
  unsigned int _em_id;
  const VariableGradient & _grad_potential;
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
  const MaterialProperty<Real> & _Eex;
  const MaterialProperty<Real> & _el_coeff_energy_a;
  const MaterialProperty<Real> & _el_coeff_energy_b;
  const MaterialProperty<Real> & _el_coeff_energy_c;
  const MaterialProperty<Real> & _alpha_iz;
  const MaterialProperty<Real> & _d_iz_d_actual_mean_en;
  const MaterialProperty<Real> & _alpha_ex;
  const MaterialProperty<Real> & _d_ex_d_actual_mean_en;
  const MaterialProperty<Real> & _d_el_d_actual_mean_en;
  const MaterialProperty<Real> & _d_muem_d_actual_mean_en;
  const MaterialProperty<Real> & _d_diffem_d_actual_mean_en;
  const MaterialProperty<Real> & _d_muel_d_actual_mean_en;
  const MaterialProperty<Real> & _d_diffel_d_actual_mean_en;
  const MaterialProperty<Real> & _alpha_el;
};

#endif /* ELECTRONENERGYBOLOSKERNEL_H */
