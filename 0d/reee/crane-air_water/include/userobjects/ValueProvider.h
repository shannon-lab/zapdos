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

#pragma once

#include "GeneralUserObject.h"
#include "SplineInterpolation.h"

// Forward Declarations
class ValueProvider;
// class Function;

template <>
InputParameters validParams<ValueProvider>();

class ValueProvider : public GeneralUserObject
{
public:
  ValueProvider(const InputParameters & parameters);

  Real electron_temperature(const Real E_N) const;

  virtual void initialize();

  virtual void execute();

  virtual void finalize();

protected:
  SplineInterpolation _coefficient_interpolation;
  Real _rate_constant;

  std::string _sampling_format;
  std::string _rate_format;
};
