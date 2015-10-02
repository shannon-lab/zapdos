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

#ifndef EQUALGRADIENTCONSTRAINT_H
#define EQUALGRADIENTCONSTRAINT_H

#include "FaceFaceConstraint.h"

class EqualGradientConstraint;

template<>
InputParameters validParams<EqualGradientConstraint>();

/**
 *
 */
class EqualGradientConstraint : public FaceFaceConstraint
{
public:
  EqualGradientConstraint(const InputParameters & parameters);
  virtual ~EqualGradientConstraint();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpResidualSide(Moose::ConstraintType res_type);
  virtual Real computeQpJacobianSide(Moose::ConstraintJacobianType jac_type);
};


#endif /* EQUALGRADIENTCONSTRAINT_H */
