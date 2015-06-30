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

  // Material Properties

  const MaterialProperty<Real> & _tc;
  const MaterialProperty<Real> & _rc;
  const MaterialProperty<Real> & _Tec;
  const MaterialProperty<Real> & _Vc;
  const MaterialProperty<Real> & _muel;
  const MaterialProperty<Real> & _k4_const;
  const MaterialProperty<Real> & _k1_const;
  const MaterialProperty<Real> & _Ar;
  const MaterialProperty<Real> & _mem;
  const MaterialProperty<Real> & _mAr;
  const MaterialProperty<Real> & _muem;

  // coupled vars

  VariableValue & _em;
  VariableGradient & _grad_em;
  VariableGradient & _grad_potential;
};

#endif /* ELECTRONENERGYKERNEL_H */
