//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

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
  int _component;
  Real _r_units;

  virtual Real computeValue();
};

#endif // POSITION_H
