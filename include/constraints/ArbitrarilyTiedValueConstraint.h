//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef ARBITRARILYTIEDVALUECONSTRAINT_H
#define ARBITRARILYTIEDVALUECONSTRAINT_H

// MOOSE includes
#include "NodeFaceConstraint.h"

// Forward Declarations
class ArbitrarilyTiedValueConstraint;

template <>
InputParameters validParams<ArbitrarilyTiedValueConstraint>();

/**
 * A ArbitrarilyTiedValueConstraint forces the value of a variable to be the same on both sides of
 * an interface.
 */
class ArbitrarilyTiedValueConstraint : public NodeFaceConstraint
{
public:
  ArbitrarilyTiedValueConstraint(const InputParameters & parameters);
  virtual ~ArbitrarilyTiedValueConstraint() {}

  virtual Real computeQpSecondaryValue();

  virtual Real computeQpResidual(Moose::ConstraintType type);

  virtual Real computeQpJacobian(Moose::ConstraintJacobianType type);

protected:
  const Real _scaling;
  const Real _H;
  NumericVector<Number> & _residual_copy;
};

#endif
