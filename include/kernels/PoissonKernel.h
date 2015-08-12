#ifndef POISSONKERNEL_H
#define POISSONKERNEL_H

#include "Kernel.h"

class PoissonKernel;

template<>
InputParameters validParams<PoissonKernel>();

class PoissonKernel : public Kernel
{
 public:
  PoissonKernel(const InputParameters & parameters);
  virtual ~PoissonKernel();

 protected:
  
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // coupled vars

  VariableValue & _em;
  VariableValue & _Arp;
  unsigned int _em_id;
  unsigned int _Arp_id;

  // Kernel members

  Real _e;
  Real _eps;
};

#endif /* POISSONKERNEL_H */
