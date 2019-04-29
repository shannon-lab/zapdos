#ifndef LYMBEROPOULOSIONBC_H
#define LYMBEROPOULOSIONBC_H

#include "IntegratedBC.h"

class LymberopoulosIonBC;

template <>
InputParameters validParams<LymberopoulosIonBC>();

class LymberopoulosIonBC : public IntegratedBC
{
public:
  LymberopoulosIonBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  Real _r_units;

  // Coupled variables

  const VariableGradient & _grad_potential;
  unsigned int _potential_id;

  const MaterialProperty<Real> & _mu;
};

#endif // LymberopoulosIonBC_H
