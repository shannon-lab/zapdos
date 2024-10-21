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
class PolynomialCoefficients;
// class Function;

template <>
InputParameters validParams<PolynomialCoefficients>();

class PolynomialCoefficients : public GeneralUserObject
{
public:
  PolynomialCoefficients(const InputParameters & parameters);

  Real delta_a(const int i) const;
  Real power_coefficient() const;

  virtual void initialize();

  virtual void execute();

  virtual void finalize();

protected:
  const std::vector<Real> & _coefficients;
  const std::vector<std::string> & _participants;

  std::vector<std::vector<Real>> _polynomial_coefficients;
  std::vector<Real> _delta_a;
  Real _power_coefficient;
};
