#ifndef CHARGESOURCEMOLES_KV_H
#define CHARGESOURCEMOLES_KV_H

#include "Kernel.h"

class ChargeSourceMoles_KV;

template <>
InputParameters validParams<ChargeSourceMoles_KV>();

class ChargeSourceMoles_KV : public Kernel
{
public:
  ChargeSourceMoles_KV(const InputParameters & parameters);
  virtual ~ChargeSourceMoles_KV();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // coupled vars

  MooseVariable & _charged_var;
  const VariableValue & _charged;
  unsigned int _charged_id;

  // Kernel members

  const MaterialProperty<Real> & _e;
  const MaterialProperty<Real> & _sgn;
  const MaterialProperty<Real> & _N_A;
  std::string _potential_units;

  Real _voltage_scaling;
};

#endif /* CHARGESOURCEMOLES_KV_H */
