#ifndef ELECTRONENERGYKERNEL_H
#define ELECTRONENERGYKERNEL_H

#include "Kernel.h"

class ElectronEnergyKernel;

template<>
InputParameters validParams<ElectronEnergyKernel>();

class ElectronEnergyKernel : public Kernel
{
 public:
  ElectronEnergyKernel(const InputParameters & parameters);
  virtual ~ElectronEnergyKernel();

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
  const MaterialProperty<Real> & _Eiz_en;
  const MaterialProperty<Real> & _rate_coeff_ion_en;
  const MaterialProperty<Real> & _rate_coeff_elastic;
  const MaterialProperty<Real> & _N_A;

  // kernel members

  /* Real _alpha; */
  /* Real _Pe; */
  /* Real _vd_mag; */
  /* Real _delta; */
};

#endif /* ELECTRONENERGYKERNEL_H */
