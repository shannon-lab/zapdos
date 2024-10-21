#include "EEDFRateConstant.h"
#include "MooseUtils.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("CraneApp", EEDFRateConstant);

template <>
InputParameters
validParams<EEDFRateConstant>()
{
  InputParameters params = validParams<Material>();
  params.addRequiredParam<FileName>(
      "property_file", "The file containing interpolation tables for material properties.");
  params.addRequiredParam<std::string>("reaction", "The full reaction equation.");
  params.addRequiredParam<Real>("position_units", "The units of position.");
  params.addRequiredParam<std::string>("file_location", "The name of the file that stores the reaction rate tables.");
  params.addParam<bool>("elastic_collision", false, "If the reaction is elastic (true/false).");
  params.addCoupledVar("sampler", "The variable used to sample.");
  params.addCoupledVar("target_species", "The target species in this collision.");
  params.addCoupledVar("mean_en", "The electron mean energy.");
  params.addRequiredCoupledVar("em", "The electron density.");
  return params;
}

EEDFRateConstant::EEDFRateConstant(const InputParameters & parameters)
  : Material(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _elastic(getParam<bool>("elastic_collision")),
    _reaction_rate(declareProperty<Real>("k_"+getParam<std::string>("reaction"))),
    _d_k_d_en(declareProperty<Real>("d_k_d_en_"+getParam<std::string>("reaction"))),
    _energy_elastic(declareProperty<Real>("energy_elastic_"+getParam<std::string>("reaction"))),
    _massIncident(getMaterialProperty<Real>("mass"+(*getVar("em",0)).name())),
    _massTarget(isCoupled("target_species") ? getMaterialProperty<Real>("mass"+(*getVar("target_species",0)).name()) : getMaterialProperty<Real>("mass"+(*getVar("em",0)).name())),
    _sampler(isCoupled("sampler") ? coupledValue("sampler") : _zero),
    _em(isCoupled("em") ? coupledValue("em") : _zero),
    _mean_en(isCoupled("mean_en") ? coupledValue("mean_en") : _zero)
{
  if (!isCoupled("sampler"))
    mooseError("Sampling variable is not coupled! Please input the variable (aux or nonlinear) that will be used to sample from data files.");
  std::vector<Real> val_x;
  std::vector<Real> rate_coefficient;
  std::string file_name = getParam<std::string>("file_location") + "/" + getParam<FileName>("property_file");
  MooseUtils::checkFileReadable(file_name);
  const char * charPath = file_name.c_str();
  std::ifstream myfile(charPath);
  Real value;

  if (myfile.is_open())
  {
    while (myfile >> value)
    {
      val_x.push_back(value);
      myfile >> value;
      rate_coefficient.push_back(value);
    }
    myfile.close();
  }
  else
    mooseError("Unable to open file");

  _coefficient_interpolation.setData(val_x, rate_coefficient);
}

void
EEDFRateConstant::computeQpProperties()
{
  _reaction_rate[_qp] = _coefficient_interpolation.sample(_sampler[_qp]);
  _d_k_d_en[_qp] = _coefficient_interpolation.sampleDerivative(_sampler[_qp]);

  if (_reaction_rate[_qp] < 0.0)
  {
    _reaction_rate[_qp] = 0.0;
  }

  if (_elastic)
  {
    _energy_elastic[_qp] = -3.0 * (_massIncident[_qp] / _massTarget[_qp]) * 2.0 / 3.0 * _mean_en[_qp];
  }
  else
    _energy_elastic[_qp] = 0.0;


}
