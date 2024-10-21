#include "DiffusionRateTemp.h"
#include "MooseUtils.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("CraneApp", DiffusionRateTemp);

template <>
InputParameters
validParams<DiffusionRateTemp>()
{
  InputParameters params = validParams<Material>();
  params.addRequiredParam<std::string>("file_location", "The name of the file that stores the mobility table.");
  // params.addRequiredParam<std::string>("reaction", "The full reaction equation.");
  // params.addRequiredParam<Real>("", "The value of the reaction rate (constant).");

  return params;
}

DiffusionRateTemp::DiffusionRateTemp(const InputParameters & parameters)
  : Material(parameters),
    _diff_rate(declareProperty<Real>("diffusion_rate")),
    _gap_length(getMaterialProperty<Real>("gap_length")),
    _radius(getMaterialProperty<Real>("radius"))
{
  std::string file_name = getParam<std::string>("file_location") + "/" + "electron_temperature.txt";
  MooseUtils::checkFileReadable(file_name);
  const char * charPath = file_name.c_str();
  std::ifstream myfile(charPath);
  Real value;

  std::vector<Real> reduced_field;
  std::vector<Real> temperature;
  if (myfile.is_open())
  {
    while (myfile >> value)
    {
      reduced_field.push_back(value);
      myfile >> value;
      temperature.push_back(value);
    }
    myfile.close();
  }
  else
    mooseError("Unable to open file");

  _elec_temp.setData(reduced_field, temperature);
}

void
DiffusionRateTemp::computeQpProperties()
{
  // Should be around ~5250 for current testing purposes
  // _reaction_rate[_qp] = _rate_value;
  // _diff_rate[_qp] = 1.52 * (760.0 / _pressure[_qp]) * (300.0 / 273.16) * (_elec_temp[_qp] / 11600) *
  //   ( std::pow(2.405/_radius,2.0) + std::pow(3.141/_gap_length,2.0) );

  _diff_rate[_qp] = 1.52 * (760.0 / 100.0) * (300.0 / 273.16) * (50946 / 11600) *
    ( std::pow(2.405/0.4,2.0) + std::pow(3.141/0.4,2.0) );
}
