#ifndef ELECTRONSOURCE_H
#define ELECTRONSOURCE_H

#include "Kernel.h"

class ElectronSource;

template<>
InputParameters validParams<ElectronSource>();

class ElectronSource : public Kernel
{
 public:
  ElectronSource(const std::string & name, InputParameters parameters);
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

  // Unique to kernel

  Real _k4;
  Real _k5;
};

#endif /* ELECTRONSOURCE_H */
