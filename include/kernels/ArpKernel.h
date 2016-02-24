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

  const VariableValue & _em;
  const VariableGradient & _grad_em;
  unsigned int _em_id;
  const VariableGradient & _grad_potential;
  unsigned int _potential_id;

  // Material Properties

  const MaterialProperty<Real> &  _muem;
  const MaterialProperty<Real> &  _diffem;
  const MaterialProperty<Real> &  _muip;
  const MaterialProperty<Real> &  _diffip;
  const MaterialProperty<Real> &  _Ar;
  const MaterialProperty<Real> &  _Eiz;
  const MaterialProperty<Real> &  _rate_coeff_ion;

  // Kernel members

  Real  _alpha;
  Real  _Pe;
  Real  _vd_mag;
  Real  _delta;
  RealVectorValue _em_flux;
  RealVectorValue _d_em_flux_d_em;
  RealVectorValue _d_em_flux_d_potential;
};

#endif /* ARPKERNEL_H */
