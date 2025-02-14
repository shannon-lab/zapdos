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

#include "NonlocalIntegratedBC.h"
#include "CurrentDensityShapeSideUserObject.h"
#include "ProvideMobility.h"

/**
 *  Circuit boundary condition for potential multiplied by a penalty term
 */
class PenaltyCircuitPotential : public NonlocalIntegratedBC
{
public:
  static InputParameters validParams();

  PenaltyCircuitPotential(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;
  virtual Real computeQpNonlocalJacobian(dof_id_type dof_index) override;
  virtual Real computeQpNonlocalOffDiagJacobian(unsigned int jvar, dof_id_type dof_index) override;

  /// UserObject that provides the current
  const CurrentDensityShapeSideUserObject & _current_uo;
  /// Current on the surface
  const Real & _current;
  /// Jacobian of the current from the UserObject
  const std::vector<Real> & _current_jac;
  /// Applied potential on the surface
  const Real _surface_potential;
  /// Is the surface a anode or cathode
  const std::string _surface;
  /// Sign based on anode or cathode surface
  Real _current_sign;
  /// Penalty value
  const Real _p;
  /// The ProvideMobility UserObject that provides the Coulomb charge, electrode area, and ballast resistance
  const ProvideMobility & _data;
  /// Degree of freedoms for the variable
  const std::vector<dof_id_type> & _var_dofs;
  /// Electron variable
  unsigned int _em_id;
  /// Degree of freedoms for electron variable
  const std::vector<dof_id_type> & _em_dofs;
  /// Electron mean energy density variable
  unsigned int _mean_en_id;
  /// Degree of freedoms for electron mean energy density variable
  const std::vector<dof_id_type> & _mean_en_dofs;
  /// Scaling units for the position
  const Real _r_units;
  /// Ballast resistance
  const Real _resistance;
  /// Number of ions defined
  const unsigned int _num_ions;
  /// Area of surface, for 1D simulations
  Real _area;
  /// True for 1D simulations
  bool _use_area;
  /// Scaling value for the potential
  Real _voltage_scaling;
  /// Term for current * resistance
  Real curr_times_resist;
  /// Term for derivative of (current * resistance) wrt potential
  Real d_curr_times_resist_d_potential;
  /// Term for derivative of (current * resistance) wrt electron density
  Real d_curr_times_resist_d_em;
  /// Term for derivative of (current * resistance) wrt ion density
  Real d_curr_times_resist_d_ip;
  /// Term for derivative of (current * resistance) wrt electron mean energy density
  Real d_curr_times_resist_d_mean_en;
  /// Term for derivative of (current * resistance) wrt a coupled variable
  Real d_curr_times_resist_d_coupled_var;
  /// Ion variable
  std::vector<unsigned int> _ip_ids;
  /// Degree of freedoms for ion variable
  std::vector<const std::vector<dof_id_type> *> _ip_dofs;
};
