#ifndef ELECTRONKERNELINTTD_H
#define ELECTRONKERNELINTTD_H

#include "Kernel.h"

class ElectronKernelIntTD;

template<>
InputParameters validParams<ElectronKernelIntTD>();

class ElectronKernelIntTD : public Kernel
{
 public:
  ElectronKernelIntTD(const InputParameters & parameters);
  virtual ~ElectronKernelIntTD();

 protected:
  
  virtual Real computeQpResidual();
  /* virtual Real computeQpJacobian(); */
  /* virtual Real computeQpOffDiagJacobian(unsigned int jvar); */

  // coupled vars

  /* const VariableValue & _mean_en; */
  /* unsigned int _mean_en_id; */
  const VariableGradient & _grad_potential;
  unsigned int _potential_id;

  // Kernel members

  Real _alpha;
  Real _Pe;
  Real _vd_mag;
  Real _delta;
  /* RealVectorValue _flux; */
  /* RealVectorValue _d_flux_d_u; */

  const MaterialProperty<Real> & _muem;
  const MaterialProperty<Real> & _diffem;
  const MaterialProperty<Real> & _Ar;
  const MaterialProperty<Real> & _rate_coeff_ion;
};

#endif /* ELECTRONKERNELINTTD_H */
