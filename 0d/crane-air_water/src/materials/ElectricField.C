#include "ElectricField.h"
#include "MooseUtils.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("CraneApp", ElectricField);

template <>
InputParameters
validParams<ElectricField>()
{
  InputParameters params = validParams<Material>();
  params.addRequiredParam<std::string>("file_location", "The name of the file that stores the mobility table.");
  params.addParam<bool>("use_log", false, "Whether or not to use logarithmic form.");
  params.addCoupledVar("electron_density", "The electron density.");
  params.addCoupledVar("neutral_density", "The neutral gas density.");
  return params;
}

ElectricField::ElectricField(const InputParameters & parameters)
  : Material(parameters),
  _reduced_field(declareProperty<Real>("reduced_field")),
  _voltage(getMaterialProperty<Real>("voltage")),
  _gap_length(getMaterialProperty<Real>("gap_length")),
  _resistance(getMaterialProperty<Real>("resistance")),
  _gap_area(getMaterialProperty<Real>("gap_area")),
  _Vdr(declareProperty<Real>("Vdr")),
  _electron_density(coupledValue("electron_density")),
  _gas_density(isCoupled("neutral_density") ? coupledValue("neutral_density") : _zero),
  _reduced_field_old(getMaterialPropertyOld<Real>("reduced_field")),
  _use_log(getParam<bool>("use_log")),
  _n_gas(getMaterialProperty<Real>("n_gas"))
{
  std::string file_name = getParam<std::string>("file_location") + "/" + "electron_mobility.txt";
  MooseUtils::checkFileReadable(file_name);
  const char * charPath = file_name.c_str();
  std::ifstream myfile(charPath);
  Real value;

  std::vector<Real> reduced_field;
  std::vector<Real> mobility;
  if (myfile.is_open())
  {
    while (myfile >> value)
    {
      reduced_field.push_back(value);
      myfile >> value;
      mobility.push_back(value);
    }
    myfile.close();
  }
  else
    mooseError("Unable to open file");

  _mobility.setData(reduced_field, mobility);
}

void
ElectricField::initQpStatefulProperties()
{
  Real mult1;
  if (isCoupled("neutral_density"))
  {
    if (_use_log)
      mult1 = std::exp(_gas_density[_qp]);
    else
      mult1 = _gas_density[_qp];
  }
  else
  {
    if (_use_log)
      mult1 = _n_gas[_qp] * 6.022e23;
    else
      mult1 = _n_gas[_qp];
  }
    // mult1 = _n_gas[_qp] * 6.022e23;

  _reduced_field[_qp] = _voltage[_qp] / _gap_length[_qp] / mult1;
  // initialize the reduced field
  // This becomes reduced_field_old in subsequent calls to computeQpProperties
  // if (_use_log)
  // {
    // _reduced_field[_qp] = _voltage[_qp] / _gap_length[_qp] / std::exp(_gas_density[_qp]);
  // }
  // else
  // {
    // _reduced_field[_qp] = _voltage[_qp] / _gap_length[_qp] / _gas_density[_qp];
  // }
}

void
ElectricField::computeQpProperties()
{
  Real mult1;
  if (isCoupled("neutral_density"))
  {
    if (_use_log)
      mult1 = std::exp(_gas_density[_qp]) * 6.022e23;
    else
      mult1 = _gas_density[_qp];
  }
  else
  {
    if (_use_log)
      mult1 = _n_gas[_qp] * 6.022e23;
    else
      mult1 = _n_gas[_qp];
  }
    // mult1 = _n_gas[_qp] * 6.022e23;

  if (_use_log)
  {
    _Vdr[_qp] = mult1 * _reduced_field_old[_qp] * _mobility.sample(_reduced_field_old[_qp]);
    Real current = 1.602e-19 * _gap_area[_qp] * std::exp(_electron_density[_qp]) * 6.022e23 * _Vdr[_qp];

    _reduced_field[_qp] = _voltage[_qp] / ( _gap_length[_qp] + _resistance[_qp] * current /
      ( _reduced_field_old[_qp]*mult1 ) ) / mult1;

    // _Vdr[_qp] = std::exp(_gas_density[_qp]) * _reduced_field_old[_qp] * _mobility.sample(_reduced_field_old[_qp]);
    // Real current = 1.602e-19 * _gap_area[_qp] * std::exp(_electron_density[_qp]) * _Vdr[_qp];
    //
    // _reduced_field[_qp] = _voltage[_qp] / ( _gap_length[_qp] + _resistance[_qp] * current /
    //   ( _reduced_field_old[_qp]*std::exp(_gas_density[_qp]) ) ) / std::exp(_gas_density[_qp]);
  }
  else
  {
    _Vdr[_qp] = mult1 * _reduced_field_old[_qp] * _mobility.sample(_reduced_field_old[_qp]);
    Real current = 1.602e-19 * _gap_area[_qp] * _electron_density[_qp] * _Vdr[_qp];

    _reduced_field[_qp] = _voltage[_qp] / ( _gap_length[_qp] + _resistance[_qp] * current /
      ( _reduced_field_old[_qp]*mult1 ) ) / mult1;
    // _Vdr[_qp] = _gas_density[_qp] * _reduced_field_old[_qp] * _mobility.sample(_reduced_field_old[_qp]);
    // Real current = 1.602e-19 * _gap_area[_qp] * _electron_density[_qp] * _Vdr[_qp];
    //
    // _reduced_field[_qp] = _voltage[_qp] / ( _gap_length[_qp] + _resistance[_qp] * current /
    //   ( _reduced_field_old[_qp]*_gas_density[_qp] ) ) / _gas_density[_qp];
  }

}
