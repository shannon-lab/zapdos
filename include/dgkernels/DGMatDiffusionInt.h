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

#ifndef DGMATDIFFUSIONINT_H
#define DGMATDIFFUSIONINT_H

#include "DGInterface.h"

//Forward Declarations
class DGMatDiffusionInt;

template<>
InputParameters validParams<DGMatDiffusionInt>();

/**
 * DG kernel for interfacing diffusion between two variables on adjacent blocks
 */
class DGMatDiffusionInt : public DGInterface
{
public:
  DGMatDiffusionInt(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual(Moose::DGResidualType type);
  virtual Real computeQpJacobian(Moose::DGJacobianType type);

  const MaterialProperty<Real> & _D;
  const MaterialProperty<Real> & _D_neighbor;
};

#endif
