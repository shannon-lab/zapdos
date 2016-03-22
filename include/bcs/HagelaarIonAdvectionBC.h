#ifndef HAGELAARIONADVECTIONBC_H
#define HAGELAARIONADVECTIONBC_H

#include "IntegratedBC.h"

class HagelaarIonAdvectionBC;

template<>
InputParameters validParams<HagelaarIonAdvectionBC>();

class HagelaarIonAdvectionBC : public IntegratedBC
{
public:

  HagelaarIonAdvectionBC(const InputParameters & parameters);

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

  Real _a;
};

#endif //HAGELAARIONADVECTIONBC_H
