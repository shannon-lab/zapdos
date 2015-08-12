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

  // coupled vars

  VariableValue & _em;
  VariableGradient & _grad_em;
  VariableGradient & _grad_potential;

  // kernel members

  Real _muel;
  Real _muem;
  Real _diff;
  Real _diffel;
  Real _Ar;
  Real _mem;
  Real _mAr;
  Real _k4_const;
  Real _k1_const;
  Real _Eiz;
  Real _alpha;
  Real _Pe;
  Real _vd_mag;
  Real _delta;
  Real _a0;
  Real _b0;
  Real _c0;
};

#endif /* ELECTRONENERGYKERNEL_H */
