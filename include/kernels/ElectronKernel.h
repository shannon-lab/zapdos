#ifndef ELECTRONKERNEL_H
#define ELECTRONKERNEL_H

#include "Kernel.h"

class ElectronKernel;

template<>
InputParameters validParams<ElectronKernel>();

class ElectronKernel : public Kernel
{
 public:
  ElectronKernel(const InputParameters & parameters);
  virtual ~ElectronKernel();

 protected:
  
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // coupled vars

  /* VariableValue & _mean_en; */
  VariableGradient & _grad_potential;
  unsigned int _potential_id;

  // Kernel members

  Real _muem;
  Real _diff;
  Real _Eiz;
  Real _alpha;
  Real _Pe;
  Real _vd_mag;
  Real _delta;
  RealVectorValue _flux;
  RealVectorValue _d_flux_d_u;
  /* Real _a0; */
  /* Real _b0; */
  /* Real _c0; */
  /* Real _k4_const; */
  /* Real _Ar; */
};

#endif /* ELECTRONKERNEL_H */
