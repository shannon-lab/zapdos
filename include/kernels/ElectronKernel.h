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
  /* unsigned int _mean_en_id; */
  VariableGradient & _grad_potential;
  unsigned int _potential_id;

  // Kernel members

  Real _alpha;
  Real _Pe;
  Real _vd_mag;
  Real _delta;
  RealVectorValue _flux;
  RealVectorValue _d_flux_d_u;
  RealVectorValue _d_flux_d_potential;

  const MaterialProperty<Real> & _muem;
  const MaterialProperty<Real> & _diffem;
  const MaterialProperty<Real> & _Ar;
  const MaterialProperty<Real> & _Eiz;
  const MaterialProperty<Real> & _rate_coeff_ion;
};

#endif /* ELECTRONKERNEL_H */
