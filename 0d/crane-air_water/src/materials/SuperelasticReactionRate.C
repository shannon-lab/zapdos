#include "SuperelasticReactionRate.h"
#include "MooseUtils.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("CraneApp", SuperelasticReactionRate);

template <>
InputParameters
validParams<SuperelasticReactionRate>()
{
  InputParameters params = validParams<Material>();
  params.addRequiredParam<std::string>("reaction", "The full reaction equation.");
  params.addRequiredParam<std::string>("original_reaction", "The original (reversible) reaction from which this reaction was derived.");
  params.addRequiredParam<std::vector<Real>>("stoichiometric_coeff", "The coefficients of each reactant and product.");
  params.addRequiredParam<std::vector<std::string>>("participants", "All reaction participants.");
  params.addRequiredParam<std::string>("file_location", "The name of the file that stores the reaction rate tables.");
  params.addCoupledVar("gas_temperature", "The temperature of the background gas. Needed for rate constant calculation. Default: 300 K.");
  return params;
}

SuperelasticReactionRate::SuperelasticReactionRate(const InputParameters & parameters)
  : Material(parameters),
    _reaction_rate(declareProperty<Real>("k_" + getParam<std::string>("reaction"))),
    _enthalpy_reaction(declareProperty<Real>("delta_H")),
    _reversible_rate(getMaterialProperty<Real>("k_" + getParam<std::string>("original_reaction"))),
    _coefficients(getParam<std::vector<Real>>("stoichiometric_coeff")),
    _participants(getParam<std::vector<std::string>>("participants")),
    _Tgas(isCoupled("gas_temperature") ? coupledValue("gas_temperature") : _zero)
{
  // This material follows the method outlined in:
  // Mikhail S Finko et al 2017 J. Phys. D: Appl. Phys. 50 485201
  // Section 2.2, Equation 13

  // Read the participant species' coefficients from files
  std::string file_name;
  std::vector<std::vector<Real>> polynomial_coefficients;
  polynomial_coefficients.resize(_participants.size());
  _power_coefficient = 0.0;
  for (unsigned int i = 0; i < _participants.size(); ++i)
  {
    _power_coefficient += _coefficients[i];  // Finko, equation 7
    file_name = getParam<std::string>("file_location") + "/" + _participants[i] + ".txt";
    MooseUtils::checkFileReadable(file_name);
    const char * charPath = file_name.c_str();
    std::ifstream myfile(charPath);
    Real value;

    if (myfile.is_open())
    {
      while (myfile >> value)
      {
        polynomial_coefficients[i].push_back(value);
      }
      myfile.close();
    }
    else
    {
      mooseError("Unable to open file: " + file_name);
    }
  }

  // Sum the coefficients
  delta_a.resize(polynomial_coefficients[0].size(), 0.0);
  for (unsigned int i = 0; i < polynomial_coefficients.size(); ++i)
  {
    for (unsigned int j = 0; j < polynomial_coefficients[i].size(); ++j)
    {
      delta_a[j] += _coefficients[i] * polynomial_coefficients[i][j];
    }
  }
}

void
SuperelasticReactionRate::computeQpProperties()
{
  // Finko, equation 8
  _enthalpy_reaction[_qp] = delta_a[0] + (delta_a[1]/2.0)*_Tgas[_qp] + (delta_a[2]/3.0)*std::pow(_Tgas[_qp],2.0) +
    (delta_a[3]/4.0)*std::pow(_Tgas[_qp],3.0) + (delta_a[4]/5.0)*std::pow(_Tgas[_qp],4.0) +
    (delta_a[5]/_Tgas[_qp]);

  // Finko, equation 13 (work in progress...)
  _equilibrium_constant = std::pow(1.0, _power_coefficient) * std::exp(delta_a[0]*(std::log(_Tgas[_qp] - 1)) +
  (delta_a[1]/2.0)*_Tgas[_qp] + (delta_a[2]/6.0)*std::pow(_Tgas[_qp], 2.0) + (delta_a[3]/12.0)*std::pow(_Tgas[_qp], 3.0) +
  (delta_a[4]/20.0)*std::pow(_Tgas[_qp], 4.0) - delta_a[5]*std::pow(_Tgas[_qp], -1.0) + delta_a[6]);

  _reaction_rate[_qp] = _reversible_rate[_qp] / _equilibrium_constant;
  // std::cout << _reversible_rate[_qp] << std::endl;
}
