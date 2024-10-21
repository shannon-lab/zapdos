#include "EEDFRateConstantTownsend.h"
#include "MooseUtils.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("CraneApp", EEDFRateConstantTownsend);

template <>
InputParameters
validParams<EEDFRateConstantTownsend>()
{
  InputParameters params = validParams<Material>();
  params.addRequiredParam<FileName>(
      "property_file", "The file containing interpolation tables for material properties.");
  params.addRequiredParam<std::string>("reaction", "The full reaction equation.");
  params.addRequiredParam<Real>("position_units", "The units of position.");
  params.addRequiredParam<std::string>(
      "file_location", "The name of the file that stores the reaction rate tables.");
  params.addParam<bool>("elastic_collision",
                        false,
                        "Determining whether or not a collision is elastic. Energy change for "
                        "elastic collisions is calculated on the fly, not pre-assigned.");
  params.addParam<std::string>(
      "reaction_coefficient_format",
      "townsend",
      "The format of the reaction coefficient. Options: rate or townsend.");
  params.addParam<bool>("is_target_aux",
                        false,
                        "Whether the coupled target species is an aux variable or not. (If it is, "
                        "it does not contribute to jacobian terms.)");
  params.addCoupledVar("target_species", "The heavy (target) species. Optional (default: _n_gas).");
  params.addRequiredCoupledVar("mean_en", "The electron mean energy in log form.");
  params.addRequiredCoupledVar("em", "The electron density.");

  return params;
}

EEDFRateConstantTownsend::EEDFRateConstantTownsend(const InputParameters & parameters)
  : Material(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _coefficient_format(getParam<std::string>("reaction_coefficient_format")),
    _reaction_rate(declareProperty<Real>("k_" + getParam<std::string>("reaction"))),
    _townsend_coefficient(declareProperty<Real>("alpha_" + getParam<std::string>("reaction"))),
    _energy_elastic(declareProperty<Real>("energy_elastic_" + getParam<std::string>("reaction"))),
    _d_k_d_en(declareProperty<Real>("d_k_d_en_" + getParam<std::string>("reaction"))),
    _d_alpha_d_en(declareProperty<Real>("d_alpha_d_en_" + getParam<std::string>("reaction"))),
    _d_alpha_d_var_id(
        declareProperty<unsigned int>("d_alpha_d_var_id_" + getParam<std::string>("reaction"))),
    _target_coupled(declareProperty<bool>("target_coupled_" + getParam<std::string>("reaction"))),
    _is_target_aux(getParam<bool>("is_target_aux")),
    //    _n_gas(getMaterialProperty<Real>("n_gas")),
    // _massIncident(getMaterialProperty<Real>("massHe+")),
    _massIncident(getMaterialProperty<Real>("mass" + (*getVar("em", 0)).name())),
    _massTarget(isCoupled("target_species")
                    ? getMaterialProperty<Real>("mass" + (*getVar("target_species", 0)).name())
                    : getMaterialProperty<Real>("mass" + (*getVar("em", 0)).name())),

    // Electron information
    _target_species(isCoupled("target_species") ? coupledValue("target_species") : _zero),
    // _target_id(coupled("target_species") ? coupled("target_species") : 0),
    _em(isCoupled("em") ? coupledValue("em") : _zero),
    _mean_en(isCoupled("mean_en") ? coupledValue("mean_en") : _zero),

    // Elastic collision check
    _elastic_collision(getParam<bool>("elastic_collision"))
{
  if (isCoupled("target_species") && !_is_target_aux)
    _target_id = coupled("target_species");
  std::vector<Real> temp_x;
  std::vector<Real> temp_y;
  std::vector<Real> actual_mean_energy;
  std::vector<Real> rate_coefficient;
  std::string file_name =
      getParam<std::string>("file_location") + "/" + getParam<FileName>("property_file");
  MooseUtils::checkFileReadable(file_name);
  const char * charPath = file_name.c_str();
  std::ifstream myfile(charPath);
  Real value;

  if (myfile.is_open())
  {
    while (myfile >> value)
    {
      temp_x.push_back(value);
      myfile >> value;
      temp_y.push_back(value);

      actual_mean_energy.push_back(1);
      rate_coefficient.push_back(1);
    }
    myfile.close();
  }
  else
    mooseError("Unable to open file");

  // if (std::is_sorted(actual_mean_energy.begin(), actual_mean_energy.end())) {
  //   std::cout << "TRUE" << std::endl;
  // }
  // else
  // {
  //   std::cout << "FALSE" << std::endl;
  // }
  // for (int i = 45; i < 75; ++i)
  // {
  //   std::cout << i << ", " << actual_mean_energy[i] << std::endl;
  // }

  // Ensure that arrays are sorted (should be done externally or by Bolsig+ wrapper; this is not
  // permanent)
  std::vector<size_t> idx(actual_mean_energy.size());
  std::iota(idx.begin(), idx.end(), 0);
  // std::sort(idx.begin(), idx.end(), [&actual_mean_energy](size_t i1, size_t i2){return
  // actual_mean_energy[i1] < actual_mean_energy[i2];});
  std::sort(
      idx.begin(), idx.end(), [&temp_x](size_t i1, size_t i2) { return temp_x[i1] < temp_x[i2]; });
  for (MooseIndex(idx) i = 0; i < idx.size(); ++i)
  {
    // actual_mean_energy[i] = actual_mean_energy[idx[i]];
    actual_mean_energy[i] = temp_x[idx[i]];
    rate_coefficient[i] = temp_y[idx[i]];
    // std::cout << i << ", " << actual_mean_energy[i] << std::endl;
  }
  // std::sort(actual_mean_energy.begin(), actual_mean_energy.end());
  // std::cout << "Sorted: " << std::endl;
  // for (int i = 45; i < 75; ++i)
  // {
  //
  //   // std::cout << i << ", " << idx[i] << ", " << actual_mean_energy[i] << std::endl;
  //   std::cout << actual_mean_energy[i] << ", " << actual_mean_energy[idx[i]] << std::endl;
  // }
  _coefficient_interpolation.setData(actual_mean_energy, rate_coefficient);

  if (_coefficient_format != "rate" && _coefficient_format != "townsend")
    mooseError("Reaction coefficient format '" + _coefficient_format +
               "' not recognized. Only 'townsend' and 'rate' are accepted.");
}

void
EEDFRateConstantTownsend::computeQpProperties()
{
  Real actual_mean_energy = std::exp(_mean_en[_qp] - _em[_qp]);
  // if (_coefficient_format == "townsend")
  // {
  _townsend_coefficient[_qp] = _coefficient_interpolation.sample(actual_mean_energy);
  //  std::cout << _townsend_coefficient[_qp] << ", " << getParam<std::string>("reaction")  <<
  //  std::endl;
  _d_alpha_d_en[_qp] = _coefficient_interpolation.sampleDerivative(actual_mean_energy);
   if (isCoupled("target_species"))
    {
      _townsend_coefficient[_qp] =
          _townsend_coefficient[_qp] * std::exp(_target_species[_qp]) / 40.5250683981307;
      if (!_is_target_aux)
      {
        _d_alpha_d_en[_qp] = _d_alpha_d_en[_qp] * std::exp(_target_species[_qp]) / 40.5250683981307;
        _d_alpha_d_var_id[_qp] = _target_id;
      }
    }
   

  if (_elastic_collision == true)
  {
    _energy_elastic[_qp] = -3.0 * _massIncident[_qp] / _massTarget[_qp] * 2.0 / 3.0 *
                           std::exp(_mean_en[_qp] - _em[_qp]);
  }
  // }
  // else
  // {
  //   _reaction_rate[_qp] = _coefficient_interpolation.sample(actual_mean_energy);
  //   _d_k_d_en[_qp] = _coefficient_interpolation.sampleDerivative(actual_mean_energy);
  // }
}
