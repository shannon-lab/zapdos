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
 * Boundary condition of a Neumann style whose value is computed by a user-defined function
 */
class NeumannCircuitVoltageNew : public NonlocalIntegratedBC
{
public:
  static InputParameters validParams();

  NeumannCircuitVoltageNew(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;
  virtual Real computeQpNonlocalJacobian(dof_id_type dof_index) override;
  virtual Real computeQpNonlocalOffDiagJacobian(unsigned int jvar, dof_id_type dof_index) override;

  // Current and current density
  const CurrentDensityShapeSideUserObject & _current_uo;
  const Real & _current;
  const std::vector<Real> & _current_jac;
  const std::string _surface;
  Real _current_sign;

  // Data
  const ProvideMobility & _data;

  // Coupled variables
  const std::vector<dof_id_type> & _var_dofs;

  unsigned int _em_id;
  const std::vector<dof_id_type> & _em_dofs;

  unsigned int _ip_id;
  const std::vector<dof_id_type> & _ip_dofs;

  unsigned int _mean_en_id;
  const std::vector<dof_id_type> & _mean_en_dofs;

  // System properties
  const Function & _V_source;
  const Real _resistance;
  Real _area;
  bool _use_area;

  // Units
  std::string _potential_units;
  const Real _r_units;
  Real _voltage_scaling;
};

