#ifndef HAGELAARENERGYBC_H
#define HAGELAARENERGYBC_H

#include "IntegratedBC.h"

class HagelaarEnergyBC;

template<>
InputParameters validParams<HagelaarEnergyBC>();

class HagelaarEnergyBC : public IntegratedBC
{
public:

  HagelaarEnergyBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  Real _r_units;
  Real _r;

  // Coupled variables

  VariableGradient & _grad_potential;
  unsigned int _potential_id;
  VariableValue & _em;
  unsigned int _em_id;
  MooseVariable & _ip_var;
  VariableValue & _ip;
  VariableGradient & _grad_ip;
  unsigned int _ip_id;

  const MaterialProperty<Real> & _muem;
  const MaterialProperty<Real> & _d_muem_d_actual_mean_en;
  const MaterialProperty<Real> & _mem;
  const MaterialProperty<Real> & _e;
  const MaterialProperty<Real> & _sgnip;
  const MaterialProperty<Real> & _muip;
  const MaterialProperty<Real> & _Dip;
  const MaterialProperty<Real> & _se_coeff;
  const MaterialProperty<Real> & _se_energy;
  const MaterialProperty<Real> & _mumean_en;
  const MaterialProperty<Real> & _d_mumean_en_d_actual_mean_en;

  Real  _a;
  Real  _v_thermal;
  RealVectorValue  _ion_flux;
  Real  _n_gamma;
  Real  _d_v_thermal_d_u;
  Real  _d_v_thermal_d_em;
  RealVectorValue  _d_ion_flux_d_potential;
  RealVectorValue  _d_ion_flux_d_ip;
  Real  _d_n_gamma_d_potential;
  Real  _d_n_gamma_d_ip;
  Real  _d_n_gamma_d_u;
  Real  _d_n_gamma_d_em;
  Real _actual_mean_en;

};

#endif //HAGELAARENERGYBC_H
