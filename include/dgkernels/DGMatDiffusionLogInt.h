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

#ifndef DGMATDIFFUSIONLOGINT_H
#define DGMATDIFFUSIONLOGINT_H

#include "InterfaceKernel.h"

//Forward Declarations
class DGMatDiffusionLogInt;

template<>
InputParameters validParams<DGMatDiffusionLogInt>();

/**
 * DG kernel for interfacing diffusion between two variables on adjacent blocks
 */
class DGMatDiffusionLogInt : public InterfaceKernel
{
public:
  DGMatDiffusionLogInt(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual(Moose::DGResidualType type);
  virtual Real computeQpJacobian(Moose::DGJacobianType type);
  virtual Real computeQpOffDiagJacobian(Moose::DGJacobianType type, unsigned int jvar);

  const MaterialProperty<Real> & _D;
  const MaterialProperty<Real> & _D_neighbor;
};

#endif
