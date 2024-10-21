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

#include "AuxScalarKernel.h"
#include "SplineInterpolation.h"
#include "PolynomialCoefficients.h"

class SuperelasticRateCoefficientScalar;

template <>
InputParameters validParams<SuperelasticRateCoefficientScalar>();

class SuperelasticRateCoefficientScalar : public AuxScalarKernel
{
public:
  SuperelasticRateCoefficientScalar(const InputParameters & parameters);

protected:
  virtual Real computeValue();

  const VariableValue & _forward_coefficient;
  const VariableValue & _Tgas;
  Real _Tgas_const;
  const PolynomialCoefficients & _polynomial;
};
