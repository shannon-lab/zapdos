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

  const VariableValue & _mean_en;
  unsigned int _mean_en_id;
  const VariableGradient & _grad_potential;
  unsigned int _potential_id;

  const MaterialProperty<Real> & _muem;
  const MaterialProperty<Real> & _diffem;
  const MaterialProperty<Real> & _Ar;
  const MaterialProperty<Real> & _iz_coeff_energy_a;
  const MaterialProperty<Real> & _iz_coeff_energy_b;
  const MaterialProperty<Real> & _iz_coeff_energy_c;
  const MaterialProperty<Real> & _N_A;
  const MaterialProperty<Real> & _alpha_iz;
  const MaterialProperty<Real> & _d_iz_d_actual_mean_en;
  const MaterialProperty<Real> & _d_muem_d_actual_mean_en;
  const MaterialProperty<Real> & _d_diffem_d_actual_mean_en;
};

#endif /* ELECTRONBOLOSKERNELENERGYFORM_H */
