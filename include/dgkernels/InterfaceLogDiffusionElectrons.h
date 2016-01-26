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

#ifndef INTERFACELOGDIFFUSIONELECTRONS_H
#define INTERFACELOGDIFFUSIONELECTRONS_H

#include "InterfaceKernel.h"

//Forward Declarations
class InterfaceLogDiffusionElectrons;

template<>
InputParameters validParams<InterfaceLogDiffusionElectrons>();

/**
 * DG kernel for interfacing diffusion between two variables on adjacent blocks
 */
class InterfaceLogDiffusionElectrons : public InterfaceKernel
{
public:
  InterfaceLogDiffusionElectrons(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual(Moose::DGResidualType type);
  virtual Real computeQpJacobian(Moose::DGJacobianType type);
  virtual Real computeQpOffDiagJacobian(Moose::DGJacobianType type, unsigned int jvar);

  const MaterialProperty<Real> & _diffem;
  const MaterialProperty<Real> & _d_diffem_d_actual_mean_en;

  MooseVariable & _mean_en_neighbor_var;
  VariableValue & _mean_en_neighbor;
  unsigned int _mean_en_neighbor_id;

  Real _actual_mean_en;

};

#endif
