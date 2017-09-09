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

#ifndef POSITION_H
#define POSITION_H

#include "AuxKernel.h"

// Forward Declarations
class Position;

template <>
InputParameters validParams<Position>();

/**
 * Function auxiliary value
 */
class Position : public AuxKernel
{
public:
  /**
   * Factory constructor, takes parameters so that all derived classes can be built using the same
   * constructor.
   */
  Position(const InputParameters & parameters);

  virtual ~Position() {}

protected:
  Real _r_units;

  virtual Real computeValue();
};

#endif // POSITION_H
