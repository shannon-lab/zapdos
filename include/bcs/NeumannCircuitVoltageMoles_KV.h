/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef NEUMANNCIRCUITVOLTAGEMOLES_KV_H
#define NEUMANNCIRCUITVOLTAGEMOLES_KV_H

#include "IntegratedBC.h"
#include "ProvideMobility.h"

//Forward Declarations
class NeumannCircuitVoltageMoles_KV;
class Function;

template<>
InputParameters validParams<NeumannCircuitVoltageMoles_KV>();

/**
 * Boundary condition of a Neumann style whose value is computed by a user-defined function
 */
class NeumannCircuitVoltageMoles_KV : public IntegratedBC
{
public:
  NeumannCircuitVoltageMoles_KV(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  /// The function being used for setting the value
  Real _r_units;
  Function & _V_bat;
  const ProvideMobility & _data;

  MooseVariable & _ip_var;
  const VariableValue & _ip;
  const VariableGradient & _grad_ip;
  unsigned int _ip_id;
  const VariableValue & _mean_en;
  unsigned int _mean_en_id;
  const VariableValue & _em;
  unsigned int _em_id;

  const MaterialProperty<Real> & _se_coeff;
  const MaterialProperty<Real> & _muip;
  const MaterialProperty<Real> & _eps;
  const MaterialProperty<Real> & _N_A;
  const MaterialProperty<Real> & _sgnip;
  const MaterialProperty<Real> & _Dip;
  const MaterialProperty<Real> & _muem;
  const MaterialProperty<Real> & _d_muem_d_actual_mean_en;
  const MaterialProperty<Real> & _e;
  const MaterialProperty<Real> & _massem;
  const MaterialProperty<Real> & _T_heavy;
  const MaterialProperty<Real> & _kb;
  const MaterialProperty<Real> & _mass;

  std::string _potential_units;
  Real _r;

  RealVectorValue _ion_flux;
  Real _n_gamma;
  Real _actual_mean_en;
  Real _v_e_th;
  Real _d_v_e_th_d_em;
  Real _d_v_e_th_d_mean_en;
  Real _v_i_th;
  Real _a;
  Real _b;
  RealVectorValue  _d_ion_flux_d_u;
  RealVectorValue  _d_ion_flux_d_ip;
  Real  _d_n_gamma_d_u;
  Real  _d_n_gamma_d_ip;
  Real  _d_n_gamma_d_em;
  Real  _d_n_gamma_d_mean_en;
  Real  _numerator;
  Real  _denominator;
  Real  _d_numerator_d_u;
  Real  _d_denominator_d_u;
  Real  _d_numerator_d_ip;
  Real  _d_denominator_d_ip;
  Real  _d_numerator_d_em;
  Real  _d_denominator_d_em;
  Real  _d_numerator_d_mean_en;
  Real  _d_denominator_d_mean_en;

  Real _voltage_scaling;
};

#endif // NEUMANNCIRCUITVOLTAGEMOLES_KV_H
