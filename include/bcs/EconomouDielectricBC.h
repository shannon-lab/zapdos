//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef EconomouDielectricBC_H
#define EconomouDielectricBC_H

#include "IntegratedBC.h"

class EconomouDielectricBC;

template <>
InputParameters validParams<EconomouDielectricBC>();

/**
 * Implements a simple constant Neumann BC where grad(u)=value on the boundary.
 * Uses the term produced from integrating the diffusion operator by parts.
 */
class EconomouDielectricBC : public IntegratedBC
{
public:
  /**
   * Factory constructor, takes parameters so that all derived classes can be built using the same
   * constructor.
   */
  EconomouDielectricBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  /// Value of grad(u) on the boundary.

  const Real & _r_units;

  const VariableValue & _mean_en;
  unsigned int _mean_en_id;
  const VariableValue & _em;
  unsigned int _em_id;
  const VariableValue & _ip;
  MooseVariable & _ip_var;
  unsigned int _ip_id;
  const VariableValue & _potential_ion;
  unsigned int _potential_ion_id;
  const VariableGradient & _grad_potential_ion;
  const VariableGradient & _grad_u_dot;
  const VariableValue & _u_dot;
  const VariableValue & _du_dot_du;

  const MaterialProperty<Real> & _e;
  const MaterialProperty<Real> & _sgnip;
  const MaterialProperty<Real> & _muip;
  const MaterialProperty<Real> & _massem;
  Real _user_se_coeff;

  const Real & _epsilon_d;
  const Real & _thickness;
  Real _a;
  RealVectorValue _ion_flux;
  Real _v_thermal;
  RealVectorValue _em_flux;
  RealVectorValue _d_ion_flux_du;
  RealVectorValue _d_em_flux_du;
  Real _d_v_thermal_d_mean_en;
  RealVectorValue _d_em_flux_d_mean_en;
  Real _d_v_thermal_d_em;
  RealVectorValue _d_em_flux_d_em;
  RealVectorValue _d_ion_flux_d_ip;
  RealVectorValue _d_em_flux_d_ip;
  RealVectorValue _d_ion_flux_d_potential_ion;
  RealVectorValue _d_em_flux_d_potential_ion;
  std::string _potential_units;

  Real _voltage_scaling;

  //const VariableValue & _surface_charge;
};

#endif // LymberopoulosElectronBC_H
