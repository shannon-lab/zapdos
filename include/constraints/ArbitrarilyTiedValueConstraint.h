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

// MOOSE includes
#include "NodeFaceConstraint.h"

/**
 * The ArbitrarilyTiedValueConstraint object forces the value of a variable on one side of an
 * interface to be scaled by a ratio to the same variable on the other side of the interface.
 */
class ArbitrarilyTiedValueConstraint : public NodeFaceConstraint
{
public:
  ArbitrarilyTiedValueConstraint(const InputParameters & parameters);

  static InputParameters validParams();

  virtual ~ArbitrarilyTiedValueConstraint() {}

  virtual Real computeQpSecondaryValue();

  virtual Real computeQpResidual(Moose::ConstraintType type);

  virtual Real computeQpJacobian(Moose::ConstraintJacobianType type);

protected:
  /// Scaling factor
  const Real _scaling;
  /// User defined ratio of secondary to primary variable
  const Real _H;
  /// Copy of residual
  NumericVector<Number> & _residual_copy;
};
