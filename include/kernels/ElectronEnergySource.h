#ifndef ELECTRONENERGYSOURCE_H
#define ELECTRONENERGYSOURCE_H

#include "Kernel.h"

class ElectronEnergySource;

template<>
InputParameters validParams<ElectronEnergySource>();

class ElectronEnergySource : public Kernel
{
 public:
  ElectronEnergySource(const InputParameters & parameters);
  virtual ~ElectronEnergySource();

 protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // Material properties

  const MaterialProperty<Real> & _Ar;
  const MaterialProperty<Real> & _el_energy_gain_excitation;
  const MaterialProperty<Real> & _el_energy_gain_deexcitation;
  const MaterialProperty<Real> & _el_energy_gain_ionization;
  const MaterialProperty<Real> & _el_energy_gain_meta_ionization;
  const MaterialProperty<Real> & _m_em;
  const MaterialProperty<Real> & _mAr;

  // Coupled Variables

  VariableValue & _Ars;
  unsigned int _Ars_id;
  VariableValue & _em;
  unsigned int _em_id;

  // Unique to kernel

  Real _T_e;
  Real _k1;
  Real _k2;
  Real _k3;
  Real _k4;
  Real _k5;
  Real _dk1_dTe;
  Real _dk2_dTe;
  Real _dk3_dTe;
  Real _dk4_dTe;
  Real _dk5_dTe;

  bool ArsCoupling;
};

#endif /* ELECTRONENERGYSOURCE_H */
