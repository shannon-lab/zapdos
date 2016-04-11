#ifndef ELECTRONENERGYRATEELASTIC_H
#define ELECTRONENERGYRATEELASTIC_H

#include "Kernel.h"

class ElectronEnergyRateElastic;

template<>
InputParameters validParams<ElectronEnergyRateElastic>();

class ElectronEnergyRateElastic : public Kernel
{
public:
  ElectronEnergyRateElastic(const InputParameters & parameters);
  virtual ~ElectronEnergyRateElastic();

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  const MaterialProperty<Real> & _kel;
  const MaterialProperty<Real> & _d_kel_d_actual_mean_en;
  const MaterialProperty<Real> & _massem;
  const MaterialProperty<Real> & _massGas;
  const MaterialProperty<Real> & _n_gas;

  Real _actual_mean_en;
  Real _d_kel_d_mean_en;
  Real _d_kel_d_em;

  const VariableValue & _em;
  unsigned int _em_id;
};


#endif /* ELECTRONENERGYRATEELASTIC_H */
