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

/*
 *  Defines ballast resistance and the area of
 *  an electrode (Used with Circuit BCs)
 */
class ProvideMobility : public GeneralUserObject
{
public:
  ProvideMobility(const InputParameters & parameters);

  static InputParameters validParams();

  /// Function that returns the area of the electrode
  Real electrode_area() const;
  /// Function that returns the value of the ballast resistor
  Real ballast_resist() const;
  /// Function that returns the value of the coulombic charge
  Real coulomb_charge() const;

  /**
   * This is called before execute so you can reset any internal data.
   */
  virtual void initialize();
  /**
   * Called on every "object" (like every element or node).
   * In this case, it is called at every quadrature point on every element.
   */
  virtual void execute();
  /**
   * Called _once_ after execute has been called on all "objects".
   */
  virtual void finalize();

protected:
  /// Electrode area
  Real _electrode_area;
  /// Ballast resistor
  Real _ballast_resist;
  /// Coulombic charge
  Real _e;
};
