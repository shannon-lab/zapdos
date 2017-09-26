#ifndef DRIFTDIFFUSIONELECTRONS_H
#define DRIFTDIFFUSIONELECTRONS_H

#include "Kernel.h"

class DriftDiffusionElectrons;

template <>
InputParameters validParams<DriftDiffusionElectrons>();

// This diffusion kernel should only be used with species whose values are in the logarithmic form.

class DriftDiffusionElectrons : public Kernel
{
public:
  DriftDiffusionElectrons(const InputParameters & parameters);
  virtual ~DriftDiffusionElectrons();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  Real _r_units;

  const MaterialProperty<Real> & _muem;
  const MaterialProperty<Real> & _d_muem_d_actual_mean_en;
  const MaterialProperty<Real> & _sign;
  const MaterialProperty<Real> & _diffem;
  const MaterialProperty<Real> & _d_diffem_d_actual_mean_en;

  // Coupled variables
  unsigned int _potential_id;
  const VariableGradient & _grad_potential;
  const VariableValue & _mean_en;
  unsigned int _mean_en_id;

  Real _d_actual_mean_en_d_mean_en;
  Real _d_muem_d_mean_en;
  Real _d_actual_mean_en_d_u;
  Real _d_muem_d_u;
  Real _d_diffem_d_u;
  Real _d_diffem_d_mean_en;
};

#endif /* DRIFTDIFFUSIONELECTRONS_H */
