#ifndef ELECTRONENERGYKERNEL_H
#define ELECTRONENERGYKERNEL_H

#include "Kernel.h"

class ElectronEnergyKernel;

template<>
InputParameters validParams<ElectronEnergyKernel>();

class ElectronEnergyKernel : public Kernel
{
 public:
  ElectronEnergyKernel(const std::string & name, InputParameters parameters);
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
  Real _Ar;
  Real _mem;
  Real _mAr;
  Real _k4_const;
  Real _k1_const;
};

#endif /* ELECTRONENERGYKERNEL_H */
