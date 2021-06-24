#pragma once

#include "ADVectorIntegratedBC.h"

/**
 *  Electric field boundary condition derived from Faraday's law. User-supplied
 *  time derivative function for applied magnetic field based on current sets
 *  curl of E on the surface.
 */
class FaradayCurrentBC : public ADVectorIntegratedBC
{
public:
  static InputParameters validParams();

  FaradayCurrentBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual();

  /// Vacuum permeability
  const Real _mu;

  /// System driving frequency
  const Real & _frequency;

  /// Current dot function
  const Function &  _current_dot;
};
