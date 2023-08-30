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

/// A postprocessor for collecting the nodal min or max value
class PlasmaFrequencyInverse : public ElementVariablePostprocessor
{
public:
  /**
   * Class constructor
   * @param parameters The input parameters
   */
  PlasmaFrequencyInverse(const InputParameters & parameters);

  static InputParameters validParams();

  virtual void initialize() override;
  using Postprocessor::getValue;
  virtual PostprocessorValue getValue() const override;
  virtual void finalize() override;
  virtual void threadJoin(const UserObject & y) override;

protected:
  /// Get the extreme value at each quadrature point
  virtual void computeQpValue() override;

  /// The extreme value
  Real _value;
  Real _em_density;
  bool _use_moles;
  Real _inverse;
};
