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

#ifndef INTERFACEADVECTION_H
#define INTERFACEADVECTION_H

#include "InterfaceKernel.h"

//Forward Declarations
class InterfaceAdvection;

template<>
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
  VariableGradient & _grad_potential_neighbor;
  unsigned int _potential_neighbor_id;
  MooseVariable & _mean_en_neighbor_var;
  VariableValue & _mean_en_neighbor;
  unsigned int _mean_en_neighbor_id;

  const MaterialProperty<Real> & _mu_neighbor;
  const MaterialProperty<Real> & _d_mu_neighbor_d_actual_mean_en;
  const MaterialProperty<Real> & _sgn_neighbor;

  Real _actual_mean_en;
};

#endif
