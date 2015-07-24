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
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // coupled vars

  VariableValue & _mean_en;
  VariableGradient & _grad_potential;
  unsigned int _potential_id;

  // Kernel members

  Real _muem;
  Real _k4_const;
  Real _diff;
  Real _Ar;
  Real _Eiz;
};

#endif /* ELECTRONKERNEL_H */
