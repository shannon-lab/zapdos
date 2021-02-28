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

#include "GeneralUserObject.h"

// Forward Declarations
class ProvideMobility;

template <>
InputParameters validParams<ProvideMobility>();

class ProvideMobility : public GeneralUserObject
{
public:
  ProvideMobility(const InputParameters & parameters);

  Real electrode_area() const;
  Real ballast_resist() const;
  Real coulomb_charge() const;

  virtual void initialize();

  virtual void execute();

  virtual void finalize();

protected:
  Real _electrode_area;
  Real _ballast_resist;
  Real _e;
};
