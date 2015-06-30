#ifndef ELECTRONKERNEL_H
#define ELECTRONKERNEL_H

#include "Kernel.h"

class ElectronKernel;

template<>
InputParameters validParams<ElectronKernel>();

class ElectronKernel : public Kernel
{
 public:
  ElectronKernel(const std::string & name, InputParameters parameters);
  virtual ~ElectronKernel();

 protected:
  
  virtual Real computeQpResidual();

  // Material Properties

  const MaterialProperty<Real> & _tc;
  const MaterialProperty<Real> & _rc;
  const MaterialProperty<Real> & _Tec;
  const MaterialProperty<Real> & _Vc;
  const MaterialProperty<Real> & _muem;
  const MaterialProperty<Real> & _k4_const;
  const MaterialProperty<Real> & _Ar;

  // coupled vars

  VariableValue & _Te;
  VariableGradient & _grad_potential;
};

#endif /* ELECTRONKERNEL_H */
