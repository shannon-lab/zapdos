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
class RateCoefficientProvider;
// class Function;

template <>
InputParameters validParams<RateCoefficientProvider>();

class RateCoefficientProvider : public GeneralUserObject
{
public:
  RateCoefficientProvider(const InputParameters & parameters);

  Real reaction_coefficient() const;
  Real reaction_coefficient_derivative() const;
  Real electron_temperature(const Real E_N) const;
  // Real reduced_field(const Real reduced_field_old, const Real gas_density) const;

  virtual void initialize();

  virtual void execute();

  virtual void finalize();

protected:
  SplineInterpolation _coefficient_interpolation;
  Real _rate_constant;

  std::string _sampling_format;
  std::string _rate_format;
  const VariableValue & _reduced_field_value;
  // Function & _function;
  // const Point & _point;
  // Real _reaction_rate;
  // Real _d_k_d_en;
  // std::string _sampling_format;
};

