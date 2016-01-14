#ifndef HAGELAARELECTRONBC_H
#define HAGELAARELECTRONBC_H

#include "IntegratedBC.h"

class HagelaarElectronBC;

template<>
InputParameters validParams<HagelaarElectronBC>();

class HagelaarElectronBC : public IntegratedBC
{
public:

  HagelaarElectronBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  Real _r;

  // Coupled variables

  VariableGradient & _grad_potential;
  unsigned int _potential_id;
  VariableValue & _mean_en;
  unsigned int _mean_en_id;
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

  Real  _a;
  Real  _v_thermal;
  RealVectorValue  _ion_flux;
  Real  _n_gamma;
  Real  _d_v_thermal_d_u;
  Real  _d_v_thermal_d_mean_en;
  RealVectorValue  _d_ion_flux_d_potential;
  RealVectorValue  _d_ion_flux_d_ip;
  Real  _d_n_gamma_d_potential;
  Real  _d_n_gamma_d_ip;

};

#endif //HAGELAARELECTRONBC_H
