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
  virtual Real computeQpJacobian();

  // coupled vars

  /* VariableValue & _em; */
  /* VariableValue & _Arp; */

  // Kernel members

  Real _e;
  Real _eps;
};

#endif /* POISSONKERNEL_H */
