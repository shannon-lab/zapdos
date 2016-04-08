#ifndef HAGELAARELECTRONBC_H
#define HAGELAARELECTRONBC_H

#include "IntegratedBC.h"

class HagelaarElectronBC;

template<>
InputParameters validParams<HagelaarElectronBC>();

class HagelaarElectronBC : public IntegratedBC
{
public:

  HagelaarElectronBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  Real _r_units;
  Real _r;

  // Coupled variables

  const VariableGradient & _grad_potential;
  unsigned int _potential_id;
  const VariableValue & _mean_en;
  unsigned int _mean_en_id;

  const MaterialProperty<Real> & _muem;
  const MaterialProperty<Real> & _d_muem_d_actual_mean_en;
  const MaterialProperty<Real> & _massem;
  const MaterialProperty<Real> & _e;

  Real  _a;
  Real  _v_thermal;
  Real  _d_v_thermal_d_u;
  Real  _d_v_thermal_d_mean_en;
  Real _actual_mean_en;

};

#endif //HAGELAARELECTRONBC_H
