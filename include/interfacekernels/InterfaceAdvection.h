//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef INTERFACEADVECTION_H
#define INTERFACEADVECTION_H

#include "InterfaceKernel.h"

// Forward Declarations
class InterfaceAdvection;

template <>
InputParameters validParams<InterfaceAdvection>();

/**
 * DG kernel for interfacing advection on adjacent blocks
 */
class InterfaceAdvection : public InterfaceKernel
{
public:
  InterfaceAdvection(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual(Moose::DGResidualType type);
  virtual Real computeQpJacobian(Moose::DGJacobianType type);
  virtual Real computeQpOffDiagJacobian(Moose::DGJacobianType type, unsigned int jvar);

  Real _r_units;
  Real _r_neighbor_units;

  MooseVariable & _potential_neighbor_var;
  const VariableGradient & _grad_potential_neighbor;
  unsigned int _potential_neighbor_id;
  MooseVariable & _mean_en_neighbor_var;
  const VariableValue & _mean_en_neighbor;
  unsigned int _mean_en_neighbor_id;

  const MaterialProperty<Real> & _mu_neighbor;
  const MaterialProperty<Real> & _d_mu_neighbor_d_actual_mean_en;
  const MaterialProperty<Real> & _sgn_neighbor;

  Real _actual_mean_en;
};

#endif
