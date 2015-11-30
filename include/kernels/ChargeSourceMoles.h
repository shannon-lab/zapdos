#ifndef CHARGESOURCEMOLES_H
#define CHARGESOURCEMOLES_H

#include "Kernel.h"

class ChargeSourceMoles;

template<>
InputParameters validParams<ChargeSourceMoles>();

class ChargeSourceMoles : public Kernel
{
 public:
  ChargeSourceMoles(const InputParameters & parameters);
  virtual ~ChargeSourceMoles();

 protected:
  
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // coupled vars

  MooseVariable & _charged_var;
  VariableValue & _charged;
  unsigned int _charged_id;

  // Kernel members

  const MaterialProperty<Real> &  _e;
  const MaterialProperty<Real> &  _sgn;
  const MaterialProperty<Real> &  _N_A;
};

#endif /* CHARGESOURCEMOLES_H */
