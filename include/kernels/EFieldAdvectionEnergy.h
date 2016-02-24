#ifndef EFIELDADVECTIONENERGY_H
#define EFIELDADVECTIONENERGY_H

#include "Kernel.h"

class EFieldAdvectionEnergy;

template<>
InputParameters validParams<EFieldAdvectionEnergy>();

class EFieldAdvectionEnergy : public Kernel
{
 public:

  EFieldAdvectionEnergy(const InputParameters & parameters);

 protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // Material properties

  Real _r_units;

  const MaterialProperty<Real> & _muel;
  const MaterialProperty<Real> & _d_muel_d_actual_mean_en;
  const MaterialProperty<Real> & _sign;

 private:

  // Coupled variables
  unsigned int _potential_id;
  const VariableGradient & _grad_potential;
  const VariableValue & _em;
  unsigned int _em_id;

  Real _d_actual_mean_en_d_em;
  Real _d_muel_d_em;
  Real _d_actual_mean_en_d_u;
  Real _d_muel_d_u;
};

#endif //EFIELDADVECTIONENERGY_H
