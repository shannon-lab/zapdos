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
#include "LinearInterpolation.h"

class DataReadScalar;

template <>
InputParameters validParams<DataReadScalar>();

class DataReadScalar : public AuxScalarKernel
{
public:
  DataReadScalar(const InputParameters & parameters);

protected:
  virtual Real computeValue();
  SplineInterpolation _coefficient_interpolation;
  // LinearInterpolation _coefficient_interpolation_linear;
  const VariableValue & _sampler_var;
  Real _sampler_const;
  std::string _sampling_format;
  bool _use_time;
  bool _use_log;
  Real _scale_factor;
};
