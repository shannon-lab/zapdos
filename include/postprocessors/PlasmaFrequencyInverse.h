//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef PlasmaFrequencyInverse_H
#define PlasmaFrequencyInverse_H

#include "ElementVariablePostprocessor.h"

// Forward Declarations
class PlasmaFrequencyInverse;

// Input parameters
template <>
InputParameters validParams<PlasmaFrequencyInverse>();

/// A postprocessor for collecting the nodal min or max value
class PlasmaFrequencyInverse : public ElementVariablePostprocessor
{
public:

  /**
   * Class constructor
   * @param parameters The input parameters
   */
  PlasmaFrequencyInverse(const InputParameters & parameters);

  virtual void initialize() override;
  virtual Real getValue() override;
  virtual void threadJoin(const UserObject & y) override;

protected:
  /// Get the extreme value at each quadrature point
  virtual void computeQpValue() override;

  /// The extreme value
  Real _value;
  Real _em_density;
  bool _use_moles;
};

#endif
