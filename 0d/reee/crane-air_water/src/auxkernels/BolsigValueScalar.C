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

#include "BolsigValueScalar.h"

registerMooseObject("CraneApp", BolsigValueScalar);

template <>
InputParameters
validParams<BolsigValueScalar>()
{
  InputParameters params = validParams<AuxScalarKernel>();
  params.addRequiredParam<UserObjectName>("data_provider", "The name of the UserObject that supplies the rate constant for this timestep.");
  params.addRequiredParam<std::string>("data_type", "Choose the electron diffusivity or mobility to fetch from Bolsig+ results. Options: diffusivity or mobility.");
  params.addParam<bool>("sample_value", false, "Whether or not to sample outputs. (If output_table = false in BoltzmannSolverScalar, this should be false.)");
  params.addCoupledVar("sample_variable", "The variable being used to sample rate coefficient values. Traditionally either reduced electric field or electron temperature.");
  return params;
}

BolsigValueScalar::BolsigValueScalar(const InputParameters & parameters)
  : AuxScalarKernel(parameters),
  _data(getUserObject<BoltzmannSolverScalar>("data_provider")),
  _data_type(getParam<std::string>("data_type")),
  _sample_value(getParam<bool>("sample_value")),
  _sampler_var(coupledScalarValue("sample_variable"))
{
}

Real
BolsigValueScalar::computeValue()
{
  // std::cout << _data.test(0) << std::endl;
  // return 0.0;

  if (_data_type == "diffusivity")
  {
    mooseError("No diffusivity function yet! Whoops!");
  }
  else if (_data_type == "mobility" && !_sample_value)
  {
    return _data.electron_mobility();
  }
  else if (_data_type == "mobility" && _sample_value)
  {
    return _data.electron_mobility_sample(_sampler_var[0]/1e-21);
  }
  else if (_data_type == "electron_temperature" && !_sample_value)
  {
    return _data.electron_temperature();
  }
  else if (_data_type == "electron_temperature" && _sample_value)
  {
    return _data.electron_temperature_sample(_sampler_var[0]/1e-21);
  }
  else
  {
    mooseError("_type of "+_data_type+" not recognized! Choose \'diffusivity\' or \'mobility\'.");
  }
}
