#ifndef HAGELAARIONBC_H
#define HAGELAARIONBC_H

#include "IntegratedBC.h"

class HagelaarIonBC;

template<>
InputParameters validParams<HagelaarIonBC>();

class HagelaarIonBC : public IntegratedBC
{
public:

  HagelaarIonBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  Real _r_units;
  Real _r;

  // Coupled variables

  const VariableGradient & _grad_potential;
  unsigned int _potential_id;

  const MaterialProperty<Real> & _mu;
  const MaterialProperty<Real> & _e;
  const MaterialProperty<Real> & _sgn;
  const MaterialProperty<Real> & _kb;
  const MaterialProperty<Real> & _T_heavy;
  const MaterialProperty<Real> & _mass;

  Real _a;
  Real _v_thermal;
};

#endif //HAGELAARIONBC_H
