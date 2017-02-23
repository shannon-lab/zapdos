#ifndef POTENTIALDRIFTOUTFLOWBC_H
#define POTENTIALDRIFTOUTFLOWBC_H

#include "IntegratedBC.h"

class PotentialDriftOutflowBC;

template<>
InputParameters validParams<PotentialDriftOutflowBC>();

// This diffusion kernel should only be used with species whose values are in the logarithmic form.

class PotentialDriftOutflowBC : public IntegratedBC
{
public:
  PotentialDriftOutflowBC(const InputParameters & parameters);
  virtual ~PotentialDriftOutflowBC();

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  Real _r_units;

  const MaterialProperty<Real> & _mu;
  const MaterialProperty<Real> & _sign;
  MaterialProperty<Real> _user_mu;
  MaterialProperty<Real> _user_sign;

  const MaterialProperty<Real> & _diffusivity;
  MaterialProperty<Real> _user_diff;

  unsigned int _potential_id;
  const VariableGradient & _grad_potential;
  VariableGradient _minus_e_field;

  Real _d_diffusivity_d_u;
};


#endif /* POTENTIALDRIFTOUTFLOWBC_H */
