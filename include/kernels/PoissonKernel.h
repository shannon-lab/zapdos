#ifndef POISSONKERNEL_H
#define POISSONKERNEL_H

#include "Kernel.h"

class PoissonKernel;

template<>
InputParameters validParams<PoissonKernel>();

class PoissonKernel : public Kernel
{
 public:
  PoissonKernel(const std::string & name, InputParameters parameters);
  virtual ~PoissonKernel();

 protected:
  
  virtual Real computeQpResidual();

  // Material Properties

  const MaterialProperty<Real> & _e;
  const MaterialProperty<Real> & _permittivity;
  const MaterialProperty<Real> & _rc;
  const MaterialProperty<Real> & _Vc;
  const MaterialProperty<Real> & _emc;

  // coupled vars

  VariableValue & _em;
  VariableValue & _Arp;
};

#endif /* POISSONKERNEL_H */
