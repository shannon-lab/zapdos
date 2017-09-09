#ifndef HAGELAARIONDIFFUSIONBC_H
#define HAGELAARIONDIFFUSIONBC_H

#include "IntegratedBC.h"

class HagelaarIonDiffusionBC;

template <>
InputParameters validParams<HagelaarIonDiffusionBC>();

class HagelaarIonDiffusionBC : public IntegratedBC
{
public:
  HagelaarIonDiffusionBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  Real _r_units;
  Real _r;

  const MaterialProperty<Real> & _kb;
  const MaterialProperty<Real> & _T;
  const MaterialProperty<Real> & _mass;

  Real _v_thermal;
  Real _user_velocity;
};

#endif // HAGELAARIONDIFFUSIONBC_H
