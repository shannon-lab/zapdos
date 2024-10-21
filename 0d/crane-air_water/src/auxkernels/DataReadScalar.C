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

#include "DataReadScalar.h"

registerMooseObject("CraneApp", DataReadScalar);

template <>
InputParameters
validParams<DataReadScalar>()
{
  InputParameters params = validParams<AuxScalarKernel>();
  params.addCoupledVar("sampler", 0, "The variable with which the data will be sampled.");
  params.addParam<bool>("use_time", false, "Whether or not to sample with time.");
  params.addParam<bool>("use_log", false, "Whether or not to return the natural logarithm of the sampled data.");
  params.addParam<Real>("scale_factor", 1.0, "Multiplies the sampled output by a given factor. Convert from m^3 to cm^3, for example.(Optional)");
  params.addParam<Real>("const_sampler", 0, "The value with which the data will be sampled.");
  params.addParam<FileName>("property_file", "",
      "The file containing interpolation tables for material properties.");
  params.addParam<std::string>("file_location", "", "The name of the file that stores the reaction rate tables.");
  params.addParam<std::string>("sampling_format", "reduced_field",
    "The format that the rate constant files are in. Options: reduced_field and electron_energy.");
  return params;
}

DataReadScalar::DataReadScalar(const InputParameters & parameters)
  : AuxScalarKernel(parameters),
    _sampler_var(coupledScalarValue("sampler")),
    _sampler_const(getParam<Real>("const_sampler")),
    _sampling_format(getParam<std::string>("sampling_format")),
    _use_time(getParam<bool>("use_time")),
    _use_log(getParam<bool>("use_log")),
    _scale_factor(getParam<Real>("scale_factor"))
{
  std::vector<Real> x_val;
  std::vector<Real> y_val;
  std::string file_name = getParam<std::string>("file_location") + "/" + getParam<FileName>("property_file");
  MooseUtils::checkFileReadable(file_name);
  const char * charPath = file_name.c_str();
  std::ifstream myfile(charPath);
  Real value;

  if (myfile.is_open())
  {
    while (myfile >> value)
    {
      x_val.push_back(value);
      myfile >> value;
      y_val.push_back(value);
    }
    myfile.close();
  }
  else
    mooseError("Unable to open file");

  _coefficient_interpolation.setData(x_val, y_val);
  // _coefficient_interpolation_linear.setData(x_val, y_val);
}

Real
DataReadScalar::computeValue()
{
  Real val;
  if (isCoupledScalar("sampler"))
    val = _coefficient_interpolation.sample(_sampler_var[_i]);
  else if (!isCoupledScalar("sampler") && _use_time)
    // val = _coefficient_interpolation_linear.sample(_t);
    val = _coefficient_interpolation.sample(_t);
  else
    val = _coefficient_interpolation.sample(_sampler_const);

  // Ensure positivity
  if (val < 0.0)
  {
    val = 0.0;
  }
  val = val * _scale_factor;

  if (_use_log && val>0)
    return log(val);
  else if (_use_log && val<=0)
    return 1e-4;
  else
    return val;
}
