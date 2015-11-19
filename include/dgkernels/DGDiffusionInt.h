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

#ifndef DGDIFFUSIONINT_H
#define DGDIFFUSIONINT_H

#include "DGInterface.h"

//Forward Declarations
class DGDiffusionInt;

template<>
InputParameters validParams<DGDiffusionInt>();

/**
 * DG kernel for interfacing diffusion between two variables on adjacent blocks
 */
class DGDiffusionInt : public DGInterface
{
public:
  DGDiffusionInt(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual(Moose::DGResidualType type);
  virtual Real computeQpJacobian(Moose::DGJacobianType type);

};

#endif
