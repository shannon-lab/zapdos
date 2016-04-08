#ifndef IONRATEIONIZATION_H
#define IONRATEIONIZATION_H

#include "Kernel.h"

class IonRateIonization;

template<>
InputParameters validParams<IonRateIonization>();

class IonRateIonization : public Kernel
{
public:
  IonRateIonization(const InputParameters & parameters);
  virtual ~IonRateIonization();

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  const MaterialProperty<Real> & _kiz;
  const MaterialProperty<Real> & _d_kiz_d_actual_mean_en;

  const VariableValue & _mean_en;
  unsigned int _mean_en_id;
  const VariableValue & em;
  unsigned int _em_id;
};


#endif /* IONRATEIONIZATION_H */
