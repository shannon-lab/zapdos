#ifndef ELECTRONSOURCE_H
#define ELECTRONSOURCE_H

#include "Kernel.h"

class ElectronSource;

template<>
InputParameters validParams<ElectronSource>();

class ElectronSource : public Kernel
{
 public:
  ElectronSource(const InputParameters & parameters);
  virtual ~ElectronSource();

 protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // Material properties

  const MaterialProperty<Real> & _Ar;

  // Coupled Variables

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

#endif /* ELECTRONSOURCE_H */
