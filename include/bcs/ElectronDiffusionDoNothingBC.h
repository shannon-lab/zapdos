#ifndef ELECTRONDIFFUSIONDONOTHINGBC_H
#define ELECTRONDIFFUSIONDONOTHINGBC_H

#include "IntegratedBC.h"

class ElectronDiffusionDoNothingBC;

template <>
InputParameters validParams<ElectronDiffusionDoNothingBC>();

// This diffusion kernel should only be used with species whose values are in the logarithmic form.

class ElectronDiffusionDoNothingBC : public IntegratedBC
{
public:
  ElectronDiffusionDoNothingBC(const InputParameters & parameters);
  virtual ~ElectronDiffusionDoNothingBC();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  Real _r_units;

  const MaterialProperty<Real> & _diffem;
  const MaterialProperty<Real> & _d_diffem_d_actual_mean_en;

  const VariableValue & _mean_en;
  unsigned int _mean_en_id;

  Real _d_diffem_d_u;
  Real _d_diffem_d_mean_en;
};

#endif /* ELECTRONDIFFUSIONDONOTHINGBC_H */
