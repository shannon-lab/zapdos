#ifndef ARSSOURCE_H
#define ARSSOURCE_H

#include "Kernel.h"

class ArsSource;

template<>
InputParameters validParams<ArsSource>();

class ArsSource : public Kernel
{
 public:
  ArsSource(const InputParameters & parameters);
  virtual ~ArsSource();

 protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // Material properties

  const MaterialProperty<Real> & _k6;
  const MaterialProperty<Real> & _k7;
  const MaterialProperty<Real> & _Ar;

  // Coupled Variables

  VariableValue & _em;
  unsigned int _em_id;
  VariableValue & _Te;
  unsigned int _Te_id;

  // Unique to kernel

  Real _k2;
  Real _k3;
  Real _k5;
  Real _dk2_dTe;
  Real _dk3_dTe;
  Real _dk5_dTe;
};

#endif /* ARSSOURCE_H */
