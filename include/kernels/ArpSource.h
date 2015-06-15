#ifndef ARPSOURCE_H
#define ARPSOURCE_H

#include "Kernel.h"

class ArpSource;

template<>
InputParameters validParams<ArpSource>();

class ArpSource : public Kernel
{
 public:
  ArpSource(const std::string & name, InputParameters parameters);
  virtual ~ArpSource();

 protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // Material properties

  const MaterialProperty<Real> & _Ar;

  // Coupled Variables

  VariableValue & _em;
  unsigned int _em_id;
  VariableValue & _Ars;
  unsigned int _Ars_id;
  VariableValue & _mean_electron_energy;
  unsigned int _mean_electron_energy_id;

  // Unique to kernel

  Real _T_e;
  Real _k_4;
  Real _k_5;
  Real _dk4_dTe;
  Real _dk5_dTe;
  Real _dTe_d_em;
  Real _dTe_d_mean_el_energy;
};

#endif /* ARPSOURCE_H */
