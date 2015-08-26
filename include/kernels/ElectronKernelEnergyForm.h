#ifndef ELECTRONKERNELENERGYFORM_H
#define ELECTRONKERNELENERGYFORM_H

#include "Kernel.h"

class ElectronKernelEnergyForm;

template<>
InputParameters validParams<ElectronKernelEnergyForm>();

class ElectronKernelEnergyForm : public Kernel
{
 public:
  ElectronKernelEnergyForm(const InputParameters & parameters);
  virtual ~ElectronKernelEnergyForm();

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

  const MaterialProperty<Real> & _muem;
  const MaterialProperty<Real> & _diffem;
  const MaterialProperty<Real> & _Ar;
  const MaterialProperty<Real> & _Eiz_en;
  const MaterialProperty<Real> & _rate_coeff_ion_en;
  const MaterialProperty<Real> & _N_A;
};

#endif /* ELECTRONKERNELENERGYFORM_H */
