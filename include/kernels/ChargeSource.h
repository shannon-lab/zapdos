#ifndef CHARGESOURCE_H
#define CHARGESOURCE_H

#include "Kernel.h"

class ChargeSource;

template<>
InputParameters validParams<ChargeSource>();

class ChargeSource : public Kernel
{
 public:
  ChargeSource(const InputParameters & parameters);
  virtual ~ChargeSource();

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
};

#endif /* CHARGESOURCE_H */
