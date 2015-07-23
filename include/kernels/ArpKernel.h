#ifndef ARPKERNEL_H
#define ARPKERNEL_H

#include "Kernel.h"

class ArpKernel;

template<>
InputParameters validParams<ArpKernel>();

class ArpKernel : public Kernel
{
 public:
  ArpKernel(const std::string & name, InputParameters parameters);
  virtual ~ArpKernel();

 protected:
  
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  // coupled vars

  VariableValue & _em;
  VariableGradient & _grad_potential;
  VariableValue & _mean_en;

  // Kernel members

  Real _k4_const;
  Real _Ar;
  Real _Eiz;
  Real _muArp;
  Real _DArp;
};

#endif /* ARPKERNEL_H */
