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

  // Material Properties

  const MaterialProperty<Real> & _tc;
  const MaterialProperty<Real> & _rc;
  const MaterialProperty<Real> & _Vc;
  const MaterialProperty<Real> & _Tec;
  const MaterialProperty<Real> & _muArp;
  const MaterialProperty<Real> & _k4_const;
  const MaterialProperty<Real> & _Ar;
  const MaterialProperty<Real> & _k_boltz;
  const MaterialProperty<Real> & _e;
  const MaterialProperty<Real> & _T_gas;

  // coupled vars

  VariableValue & _em;
  VariableGradient & _grad_potential;
  VariableValue & _Te;
};

#endif /* ARPKERNEL_H */
