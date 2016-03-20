#ifndef VACUUMELECTRICBC_H
#define VACUUMELECTRICBC_H

#include "IntegratedBC.h"

class VacuumElectricBC;

template<>
InputParameters validParams<VacuumElectricBC>();

class VacuumElectricBC : public IntegratedBC
{
public:

  VacuumElectricBC(const InputParameters & parameters);

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
  const MaterialProperty<Real> & _diff;

  Real _a;
  Real _v_thermal;
};

#endif //VACUUMELECTRICBC_H
