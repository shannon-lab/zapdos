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

#include "ValueProvider.h"
#include "Function.h"

registerMooseObject("CraneApp", ValueProvider);

template <>
InputParameters
validParams<ValueProvider>()
{
  InputParameters params = validParams<GeneralUserObject>();
  params.addParam<FileName>("property_file", "",
      "The file containing interpolation tables for material properties.");
  params.addParam<std::string>("file_location", "", "The name of the file that stores the reaction rate tables.");
  params.addParam<std::string>("sampling_format", "reduced_field",
    "The format that the rate constant files are in. Options: reduced_field and electron_energy.");
  return params;
}

ValueProvider::ValueProvider(const InputParameters & parameters)
  : GeneralUserObject(parameters),
  _sampling_format(getParam<std::string>("sampling_format"))
{
    std::vector<Real> reduced_field;
    std::vector<Real> electron_temperature;
    std::string file_name = getParam<std::string>("file_location") + "/" + getParam<FileName>("property_file");
    MooseUtils::checkFileReadable(file_name);
    const char * charPath = file_name.c_str();
    std::ifstream myfile(charPath);
    Real value;

    if (myfile.is_open())
    {
      while (myfile >> value)
      {
        reduced_field.push_back(value);
        myfile >> value;
        electron_temperature.push_back(value);
      }
      myfile.close();
    }
    else
      mooseError("Unable to open file");

    _coefficient_interpolation.setData(reduced_field, electron_temperature);
}

Real
ValueProvider::electron_temperature(const Real E_N) const
{
  return _coefficient_interpolation.sample(E_N) * 11600.0;
  // return 51614.665625302761;
  // return 50000.0;
}

void
ValueProvider::initialize()
{
}

void
ValueProvider::execute()
{
}

void
ValueProvider::finalize()
{
}
