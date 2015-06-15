#ifndef ELECTRONSOURCE_H
#define ELECTRONSOURCE_H

#include "Kernel.h"

class ElectronSource;

template<>
InputParameters validParams<ElectronSource>();

class ElectronSource : public Kernel
{
 public:
  ElectronSource(const std::string & name, InputParameters parameters);
  virtual ~ElectronSource();

 protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // Material properties

  const MaterialProperty<Real> & _Ar;
  const MaterialProperty<Real> & _N_A;

  // Coupled Variables

  VariableValue & _Ars;
  unsigned int _Ars_id;
  VariableValue & _mean_electron_energy;
  unsigned int _mean_electron_energy_id;

  // Unique to kernel

  Real _k_4;
  Real _k_5;
  Real _T_e;
  Real _dk4_dTe;
  Real _dk5_dTe;
  Real _dTe_d_mean_el_energy;
};

#endif /* ELECTRONSOURCE_H */
