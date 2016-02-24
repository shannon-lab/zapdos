#ifndef HAGELAARELECTRONLFA_BC_H
#define HAGELAARELECTRONLFA_BC_H

#include "IntegratedBC.h"

class HagelaarElectronLFA_BC;

template<>
InputParameters validParams<HagelaarElectronLFA_BC>();

class HagelaarElectronLFA_BC : public IntegratedBC
{
public:

  HagelaarElectronLFA_BC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  Real _r;

  // Coupled variables

  const VariableGradient & _grad_potential;
  unsigned int _potential_id;
  const VariableValue & _mean_en;
  unsigned int _mean_en_id;

  const MaterialProperty<Real> & _muem;
  const MaterialProperty<Real> & _d_muem_d_actual_mean_en;
  const MaterialProperty<Real> & _mem;
  const MaterialProperty<Real> & _e;

  Real _a;
  Real _v_thermal;
  Real _d_v_thermal_d_u;
  Real _d_v_thermal_d_mean_en;

};

#endif //HAGELAARELECTRONLFA_BC_H
