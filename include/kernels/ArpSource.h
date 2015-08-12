#ifndef ARPSOURCE_H
#define ARPSOURCE_H

#include "Kernel.h"

class ArpSource;

template<>
InputParameters validParams<ArpSource>();

class ArpSource : public Kernel
{
 public:
  ArpSource(const InputParameters & parameters);
  virtual ~ArpSource();

 protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // Material properties

  const MaterialProperty<Real> & _Ar;

  // Coupled Variables

  VariableValue & _em;
  unsigned int _em_id;
  VariableValue & _Ars;
  unsigned int _Ars_id;
  VariableValue & _Te;
  unsigned int _Te_id;

  // Unique to kernel

  Real _k_4;
  Real _k_5;
  Real _dk4_dTe;
  Real _dk5_dTe;

  bool ArsCoupling;
};

#endif /* ARPSOURCE_H */
