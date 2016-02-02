#ifndef COEFFDIFFUSIONELECTRONS_H
#define COEFFDIFFUSIONELECTRONS_H

#include "Kernel.h"

class CoeffDiffusionElectrons;

template<>
InputParameters validParams<CoeffDiffusionElectrons>();

// This diffusion kernel should only be used with species whose values are in the logarithmic form.

class CoeffDiffusionElectrons : public Kernel
{
public:
  CoeffDiffusionElectrons(const InputParameters & parameters);
  virtual ~CoeffDiffusionElectrons();

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  Real _r_units;

  const MaterialProperty<Real> & _diffem;
  const MaterialProperty<Real> & _d_diffem_d_actual_mean_en;

  VariableValue & _mean_en;
  unsigned int _mean_en_id;

  Real _d_diffem_d_u;
  Real _d_diffem_d_mean_en;
};


#endif /* COEFFDIFFUSIONELECTRONS_H */
