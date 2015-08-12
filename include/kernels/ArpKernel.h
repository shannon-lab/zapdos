#ifndef ARPKERNEL_H
#define ARPKERNEL_H

#include "Kernel.h"

class ArpKernel;

template<>
InputParameters validParams<ArpKernel>();

class ArpKernel : public Kernel
{
 public:
  ArpKernel(const InputParameters & parameters);
  virtual ~ArpKernel();

 protected:
  
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // coupled vars

  VariableValue & _em;
  VariableGradient & _grad_em;
  VariableGradient & _grad_potential;
  unsigned int _potential_id;
  /* VariableValue & _mean_en; */

  // Kernel members

  Real _muem;
  Real _diff;
  Real _muArp;
  Real _DArp;
  Real  _alpha;
  Real  _Pe;
  Real  _vd_mag;
  Real  _delta;
   /* Real _a0; */
  /* Real _b0; */
  /* Real _c0; */
  /* Real _k4_const; */
  /* Real _Ar; */
  /* Real _Eiz; */
};

#endif /* ARPKERNEL_H */
