#ifndef IONKERNELINTTD_H
#define IONKERNELINTTD_H

#include "Kernel.h"

class IonKernelIntTD;

template<>
InputParameters validParams<IonKernelIntTD>();

class IonKernelIntTD : public Kernel
{
 public:
  IonKernelIntTD(const InputParameters & parameters);
  virtual ~IonKernelIntTD();

 protected:
  
  virtual Real computeQpResidual();
  /* virtual Real computeQpJacobian(); */
  /* virtual Real computeQpOffDiagJacobian(unsigned int jvar); */

  // coupled vars

  const VariableValue & _em;
  const VariableGradient & _grad_em;
  unsigned int _em_id;
  const VariableGradient & _grad_potential;
  unsigned int _potential_id;
  /* const VariableValue & _mean_en; */
  /* unsigned int _mean_en_id; */

  // Material Properties

  const MaterialProperty<Real> &  _muem;
  const MaterialProperty<Real> &  _diffem;
  const MaterialProperty<Real> &  _muip;
  const MaterialProperty<Real> &  _diffip;
  const MaterialProperty<Real> &  _Ar;
  const MaterialProperty<Real> &  _rate_coeff_ion;

  // Kernel members

  Real  _alpha;
  Real  _Pe;
  Real  _vd_mag;
  Real  _delta;
};

#endif /* IONKERNELINTTD_H */
