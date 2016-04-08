#ifndef ELECTRONRATEIONIZATION_H
#define ELECTRONRATEIONIZATION_H

#include "Kernel.h"

class ElectronRateIonization;

template<>
InputParameters validParams<ElectronRateIonization>();

class ElectronRateIonization : public Kernel
{
public:
  ElectronRateIonization(const InputParameters & parameters);
  virtual ~ElectronRateIonization();

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  const MaterialProperty<Real> & _kiz;
  const MaterialProperty<Real> & _d_kiz_d_actual_mean_en;

  const VariableValue & _mean_en;
  unsigned int _mean_en_id;
};


#endif /* ELECTRONRATEIONIZATION_H */
