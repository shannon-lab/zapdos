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

#include "ElementVariablePostprocessor.h"

/*
 *  Returns the inverse of the peak electron frequency
 */
class PlasmaFrequencyInverse : public ElementVariablePostprocessor
{
public:
  PlasmaFrequencyInverse(const InputParameters & parameters);

  static InputParameters validParams();

  virtual void initialize() override;
  using Postprocessor::getValue;
  virtual PostprocessorValue getValue() const override;
  virtual void finalize() override;
  virtual void threadJoin(const UserObject & y) override;

protected:
  virtual void computeQpValue() override;

  /// Value of the electron density in units of #/m^3
  Real _value;
  /// Coupled electron density variable
  Real _em_density;
  /// True if molar density is used
  const bool _use_moles;
  /// The inverse of the plasma frequency
  Real _inverse;
};
