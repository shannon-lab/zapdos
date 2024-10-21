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

#include "ParsedScalarRateCoefficient.h"

registerMooseObject("CraneApp", ParsedScalarRateCoefficient);

template <>
InputParameters
validParams<ParsedScalarRateCoefficient>()
{
  InputParameters params = validParams<AuxScalarKernel>();
  params += validParams<FunctionParserUtils>();
  params.addClassDescription("Parsed function AuxKernel.");

  params.addRequiredCustomTypeParam<std::string>(
      "function", "FunctionExpression", "function expression");
  params.addCoupledVar("args", "coupled variables");
  params.addCoupledVar("reduced_field", 0, "The reduced electric field, if reading from a file.");
  params.addParam<std::vector<std::string>>(
      "constant_names", "Vector of constants used in the parsed function (use this for kB etc.)");
  params.addParam<std::vector<std::string>>(
      "constant_expressions",
      "Vector of values for the constants in constant_names (can be an FParser expression)");
  params.addParam<bool>("file_read", false, "Whether or not to pull a constant value from a file.");
  params.addParam<bool>("gas_temperature", false, "Whether or not gas temperature is a tracked variable.");
  params.addParam<std::string>("gas_temperature_name", "Tgas", "The name of the gas temperature variable (if applicable). Defaults to Tgas.");
  // params.addParam<std::vector<std::string>>("file_value", "The name of the value being taken from a file.");
  // params.addRequiredParam<UserObjectName>("electron_temperature",
          // "The name of the UserObject that can provide the rate coefficient.");
  return params;
}

ParsedScalarRateCoefficient::ParsedScalarRateCoefficient(const InputParameters & parameters)
  : AuxScalarKernel(parameters),
    FunctionParserUtils(parameters),
    _function(getParam<std::string>("function")),
    _nargs(coupledScalarComponents("args")),
    _args(_nargs),
    _reduced_field(coupledScalarValue("reduced_field")),
    _constant_names(getParam<std::vector<std::string>>("constant_names")),
    _constant_expressions(getParam<std::vector<std::string>>("constant_expressions"))
    // _data(getUserObject<ValueProvider>("electron_temperature"))
{
  // build variables argument
  // TODO: if electron temperature is a coupled variable, it will appear in args.
  // Need to supply a check to see if "Te" is there. (A boolean imput parameter?)
  std::string variables;
  for (unsigned int i = 0; i < _nargs; ++i)
  {
    variables += (i == 0 ? "" : ",") + getScalarVar("args", i)->name();
    _args[i] = &coupledScalarValue("args", i);
  }

  // base function object
  _func_F = ADFunctionPtr(std::make_shared<ADFunction>());

  // set FParser interneal feature flags
  setParserFeatureFlags(_func_F);

  // Append any values read from a file to the constant expressions
  // if (getParam<bool>("file_read"))
  // {
    // Real extra_value = _data.electron_temperature(7.7e-20);
    // _constant_names.push_back(getParam<std::vector<std::string>>("file_value")[0]);
    // std::cout << _reduced_field[_i] << std::endl;
    // if (isCoupledScalar("reduced_field"))
      // _constant_expressions.push_back(std::to_string(_data.electron_temperature(_reduced_field[_i])));
    // else
      // _constant_expressions.push_back(std::to_string(_data.electron_temperature(7.7e-20)));
  // }


  // add the constant expressions to the parser
  addFParserConstants(_func_F,
                      _constant_names,
                      _constant_expressions);


  // parse function
  if (_func_F->Parse(_function, variables) >= 0)
    mooseError(
        "Invalid function\n", _function, "\nin ParsedAux ", name(), ".\n", _func_F->ErrorMsg());
  // optimize
  if (!_disable_fpoptimizer)
    _func_F->Optimize();

  // just-in-time compile
  if (_enable_jit)
    _func_F->JITCompile();

  // reserve storage for parameter passing bufefr
  _func_params.resize(_nargs);
}

Real
ParsedScalarRateCoefficient::computeValue()
{
  for (unsigned int j = 0; j < _nargs; ++j)
    _func_params[j] = (*_args[j])[_i];
  return evaluate(_func_F);
}
