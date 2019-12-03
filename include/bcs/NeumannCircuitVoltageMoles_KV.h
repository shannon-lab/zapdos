//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "IntegratedBC.h"
#include "ProvideMobility.h"

// Forward Declarations
class NeumannCircuitVoltageMoles_KV;
class Function;

template <>
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
  const Function & _V_bat;
  const ProvideMobility & _data;

  std::vector<const VariableValue *> _ip;
  std::vector<const VariableGradient *> _grad_ip;
  std::vector<unsigned int> _ip_id;
  const VariableValue & _mean_en;
  unsigned int _mean_en_id;
  const VariableValue & _em;
  unsigned int _em_id;

  const MaterialProperty<Real> & _se_coeff;
  std::vector<const MaterialProperty<Real> *> _muip;
  const MaterialProperty<Real> & _eps;
  const MaterialProperty<Real> & _N_A;
  std::vector<const MaterialProperty<Real> *> _sgnip;
  std::vector<const MaterialProperty<Real> *> _Dip;
  const MaterialProperty<Real> & _muem;
  const MaterialProperty<Real> & _d_muem_d_actual_mean_en;
  const MaterialProperty<Real> & _e;
  const MaterialProperty<Real> & _massem;
  std::vector<const MaterialProperty<Real> *> _T_heavy;
  const MaterialProperty<Real> & _kb;
  std::vector<const MaterialProperty<Real> *> _mass;

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
  RealVectorValue _d_ion_flux_d_u;
  RealVectorValue _d_ion_flux_d_ip;
  Real _d_n_gamma_d_u;
  Real _d_n_gamma_d_ip;
  Real _d_n_gamma_d_em;
  Real _d_n_gamma_d_mean_en;
  Real _numerator;
  Real _denominator;
  Real _d_numerator_d_u;
  Real _d_denominator_d_u;
  Real _d_numerator_d_ip;
  Real _d_denominator_d_ip;
  Real _d_numerator_d_em;
  Real _d_denominator_d_em;
  Real _d_numerator_d_mean_en;
  Real _d_denominator_d_mean_en;

  Real _voltage_scaling;

  Real _ion_drift;
  Real _secondary_ion;
  unsigned int _num_ions;
  std::vector<unsigned int> _ion_id;
  std::vector<MooseVariable *> _ip_var;
  unsigned int _ip_index;
  std::vector<unsigned int>::iterator _iter;
};
