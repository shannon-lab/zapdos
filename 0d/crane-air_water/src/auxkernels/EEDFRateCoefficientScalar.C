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

#include "EEDFRateCoefficientScalar.h"

registerMooseObject("CraneApp", EEDFRateCoefficientScalar);

template <>
InputParameters
validParams<EEDFRateCoefficientScalar>()
{
  InputParameters params = validParams<AuxScalarKernel>();
  params.addRequiredParam<UserObjectName>("rate_provider", "The name of the UserObject that supplies the rate constant for this timestep.");
  params.addRequiredParam<int>("reaction_number", "The number of the reaction (as defined by the reactions list added to the ChemicalReactions action.)");
  params.addParam<bool>("sample_value", false, "Whether or not to sample outputs. (If output_table = false in BoltzmannSolverScalar, this should be false.)");
  params.addCoupledVar("sample_variable", "The variable being used to sample rate coefficient values. Traditionally either reduced electric field or electron temperature.");
  return params;
}

EEDFRateCoefficientScalar::EEDFRateCoefficientScalar(const InputParameters & parameters)
  : AuxScalarKernel(parameters),
  _data(getUserObject<BoltzmannSolverScalar>("rate_provider")),
  _reaction_number(getParam<int>("reaction_number")),
  _sample_value(getParam<bool>("sample_value")),
  _sampler_var(coupledScalarValue("sample_variable"))
{
}

Real
EEDFRateCoefficientScalar::computeValue()
{
  // std::cout << _data.test(0) << std::endl;
  // return 0.0;
  Real val;
  if (_sample_value)
  {
    val = _data.coefficient_sample(_reaction_number, _sampler_var[0]/1e-21);
    if (val < 0.0)
    {
      return 0.0;
    }
    else
    {
      return val;
    }
    // return _data.coefficient_sample(_reaction_number, _sampler_var[0]/1e-21);
  }
  else
  {
    return _data.test(_reaction_number);
  }
}
