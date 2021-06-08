#include "ADMMSEEDFRates.h"
#include "MooseUtils.h"
#include "Function.h"

// MOOSE includes
#include "MooseVariable.h"

registerADMooseObject("ZapdosApp", ADMMSEEDFRates);

InputParameters
ADMMSEEDFRates::validParams()
{
  InputParameters params = ADMaterial::validParams();
  params.addParam<std::vector<std::string>>("prop_names",
                                            "The names of the properties this material will have");
  params.addParam<std::vector<FunctionName>>("prop_values",
                                             "The corresponding names of the "
                                             "functions that are going to provide "
                                             "the values for the variables");
  params.addParam<std::vector<FunctionName>>("d_prop_d_actual_mean_en",
                                             "The corresponding names of the "
                                             "functions that are going to provide "
                                             "the derivative values wrt the"
                                             "actual mean energy for the variables");
  params.addCoupledVar("mean_energy", "The electron mean energy in log form.");
  params.addCoupledVar("electrons", "The electron density.");
  return params;
}

ADMMSEEDFRates::ADMMSEEDFRates(const InputParameters & parameters)
  : ADMaterial(parameters),
    _em(adCoupledValue("electrons")),
    _mean_en(adCoupledValue("mean_energy")),
    _prop_names(getParam<std::vector<std::string>>("prop_names")),
    _prop_values(getParam<std::vector<FunctionName>>("prop_values")),
    _d_prop_values_actual_mean_en(getParam<std::vector<FunctionName>>("d_prop_d_actual_mean_en"))
{
  unsigned int num_names = _prop_names.size();
  unsigned int num_values = _prop_values.size();
  unsigned int num_deriv = _d_prop_values_actual_mean_en.size();

  if ((num_names != num_values) || (num_names != num_deriv) || (num_values != num_deriv))
    mooseError(
        "Number of prop_names, prop_values and d_prop_d_actual_mean_en much match.");

  _num_props = num_names;

  _properties.resize(num_names);
  _functions.resize(num_names);
  _deriv_functions.resize(num_names);

  for (unsigned int i = 0; i < _num_props; i++)
  {
    _properties[i] = &declareADProperty<Real>(_prop_names[i]);
    _functions[i] = &getFunctionByName(_prop_values[i]);
    _deriv_functions[i] = &getFunctionByName(_d_prop_values_actual_mean_en[i]);
  }

}

void
ADMMSEEDFRates::initQpStatefulProperties()
{
  computeQpFunctions();
}

void
ADMMSEEDFRates::computeQpProperties()
{
  computeQpFunctions();
}

void
ADMMSEEDFRates::computeQpFunctions()
{
  for (unsigned int i = 0; i < _num_props; i++)
  {
    (*_properties[i])[_qp].value() = (*_functions[i]).value(_t, _q_point[_qp]);

    (*_properties[i])[_qp].derivatives() = (*_deriv_functions[i]).value(_t, _q_point[_qp]) *
                                            std::exp(_mean_en[_qp].value() - _em[_qp].value()) *
                                            (_mean_en[_qp].derivatives() - _em[_qp].derivatives());
  }
}
