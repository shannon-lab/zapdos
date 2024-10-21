#include "AddScalarReactionsOld.h"
#include "Parser.h"
#include "FEProblem.h"
#include "Factory.h"
#include "MooseEnum.h"
#include "AddVariableAction.h"
#include "Conversion.h"
#include "DirichletBC.h"
#include "ActionFactory.h"
#include "MooseObjectAction.h"
#include "MooseApp.h"

#include "libmesh/vector_value.h"

#include "pcrecpp.h"

#include <sstream>
#include <stdexcept>

// libmesh includes
#include "libmesh/libmesh.h"
#include "libmesh/exodusII_io.h"
#include "libmesh/equation_systems.h"
#include "libmesh/nonlinear_implicit_system.h"
#include "libmesh/explicit_system.h"
#include "libmesh/string_to_enum.h"
#include "libmesh/fe.h"

registerMooseAction("CraneApp", AddScalarReactionsOld, "add_aux_variable");
registerMooseAction("CraneApp", AddScalarReactionsOld, "add_aux_scalar_kernel");
registerMooseAction("CraneApp", AddScalarReactionsOld, "add_scalar_kernel");
registerMooseAction("CraneApp", AddScalarReactionsOld, "add_function");
registerMooseAction("CraneApp", AddScalarReactionsOld, "add_user_object");

template <>
InputParameters
validParams<AddScalarReactionsOld>()
{
  MooseEnum families(AddVariableAction::getNonlinearVariableFamilies());
  MooseEnum orders(AddVariableAction::getNonlinearVariableOrders());

  InputParameters params = validParams<AddVariableAction>();
  params.addRequiredParam<std::vector<NonlinearVariableName>>(
      "species", "List of (tracked) species included in reactions (both products and reactants)");
  params.addParam<std::vector<Real>>("reaction_coefficient", "The reaction coefficients.");
  params.addParam<bool>(
      "include_electrons", false, "Whether or not electrons are being considered.");
  params.addParam<bool>("track_energy", false, "Whether or not to track gas energy/temperature.");
  params.addParam<bool>("track_electron_energy", false, "Whether or not to track electron energy.");
  params.addParam<bool>(
      "use_log", false, "Whether or not to use logarithmic densities. (N = exp(n))");
  params.addParam<std::vector<NonlinearVariableName>>(
      "species_energy",
      "List of (tracked) energy values. (Optional; requires 'track_energy' to be True.)");
  params.addParam<std::string>("electron_density", "The variable used for density of electrons.");
  params.addParam<std::vector<VariableName>>(
      "electron_energy", "Electron energy, used for energy-dependent reaction rates.");
  params.addParam<std::vector<std::string>>("gas_species",
                                            "All of the background gas species in the system.");
  params.addParam<std::vector<Real>>("gas_fraction", "The initial fraction of each gas species.");
  params.addParam<bool>(
      "gas_tracking", false, "If false, neutral gas is treated as uniform background (_n_gas).");
  params.addParam<bool>(
      "gas_temperature", false, "If false, neutral gas temperature is not a solution variable.");
  params.addParam<std::vector<VariableName>>("gas_temperature_variable",
                                             "The gas temperature variable (if applicable).");
  params.addParam<std::vector<VariableName>>(
      "potential", "The electric potential, used for energy-dependent reaction rates.");
  params.addRequiredParam<std::string>("reactions", "The list of reactions to be added");
  params.addParam<Real>("position_units", 1.0, "The units of position.");
  params.addParam<std::string>(
      "file_location",
      "",
      "The location of the reaction rate files. Default: empty string (current directory).");
  params.addParam<bool>("use_moles", "Whether to use molar units.");
  params.addParam<std::string>(
      "sampling_format",
      "reduced_field",
      "Sample rate constants with E/N (reduced_field) or Te (electron_energy).");
  params.addParam<std::vector<std::string>>("equation_constants",
                                            "The constants included in the reaction equation(s).");
  params.addParam<std::vector<std::string>>(
      "equation_values", "The values of the constants included in the reaction equation(s).");
  params.addParam<std::vector<NonlinearVariableName>>(
      "equation_variables", "Any nonlinear variables that appear in the equations.");
  params.addParam<std::vector<VariableName>>(
      "rate_provider_var", "The name of the variable used to sample from BOLOS files.");
  params.addClassDescription(
      "This Action automatically adds the necessary kernels and materials for a reaction network.");

  return params;
}

// Here are a few functions for removing whitespace before/after expressions.
// (Makes the reaction input formatting more forgiving!)
// static inline string &ltrim(string &s)
// {
//   s.erase(s.begin(),find_if_not(s.begin(),s.end(),[](int c){return isspace(c);}));
//   return s;
// }
//
// static inline string &rtrim(string &s)
// {
//   s.erase(find_if_not(s.rbegin(),s.rend(),[](int c){return isspace(c);}).base(), s.end());
//   return s;
// }
//
// static inline string trim(string &s)
// {
//   return ltrim(rtrim(s));
// }

AddScalarReactionsOld::AddScalarReactionsOld(InputParameters params)
  : Action(params),
    _species(getParam<std::vector<NonlinearVariableName>>("species")),
    _species_energy(getParam<std::vector<NonlinearVariableName>>("species_energy")),
    _input_reactions(getParam<std::string>("reactions")),
    _r_units(getParam<Real>("position_units")),
    _sampling_format(getParam<std::string>("sampling_format")),
    _use_log(getParam<bool>("use_log")),
    _energy_change(false)
{
  std::istringstream iss(_input_reactions);
  std::string token;
  std::string token2;
  std::vector<std::string> rate_coefficient_string;
  std::vector<std::string> threshold_energy_string;
  // std::vector<std::string> _rate_equation_string;

  size_t pos;
  size_t pos_start;
  size_t pos_end;
  size_t eq_start;
  size_t eq_end;
  int counter;
  counter = 0;
  while (std::getline(iss >> std::ws,
                      token)) // splits by \n character (default) and ignores leading whitespace
  {
    pos = token.find(':'); // Looks for colon, which separates reaction and rate coefficients

    // Brackets enclose the energy gain/loss (if applicable)
    pos_start = token.find('[');
    pos_end = token.find(']');

    // Curly braces enclose equation constants (Arrhenius form)
    eq_start = token.find('{');
    eq_end = token.find('}');

    _reaction.push_back(token.substr(0, pos)); // Stores reactions
    rate_coefficient_string.push_back(token.substr(pos + 1, pos_start - (pos + 1)));

    trim(_reaction[counter]);
    trim(rate_coefficient_string[counter]);

    if (pos_start != std::string::npos)
    {
      threshold_energy_string.push_back(token.substr(pos_start + 1, pos_end - pos_start - 1));
      _energy_change = true;
    }
    else
    {
      threshold_energy_string.push_back("\0");
    }

    if (eq_start != std::string::npos)
    {
      _rate_equation_string.push_back(token.substr(eq_start + 1, eq_end - eq_start - 1));
      _rate_equation.push_back(true);
    }
    else
    {
      _rate_equation_string.push_back("NONE");
      _rate_equation.push_back(false);
    }
    counter += 1;
  }

  _num_reactions = _reaction.size();
  _rate_coefficient.resize(_num_reactions, 0);
  _threshold_energy.resize(_num_reactions, 0);

  _elastic_collision.resize(_num_reactions, false);
  _rate_type.resize(_num_reactions);
  _aux_var_name.resize(_num_reactions);
  for (unsigned int i = 0; i < _num_reactions; ++i)
  {
    if (threshold_energy_string[i] == "\0")
    {
      _threshold_energy[i] = 0.0;
    }
    else if (threshold_energy_string[i] == "elastic")
    {
      _threshold_energy[i] = 0.0;
      _elastic_collision[i] = true;
    }
    else
    {
      _threshold_energy[i] = std::stod(threshold_energy_string[i]);
    }
    _aux_var_name[i] = "rate_constant" + std::to_string(i); // Stores name of rate coefficients
    if (rate_coefficient_string[i] == std::string("BOLOS"))
    {
      _rate_coefficient[i] = NAN;
      _rate_type[i] = "EEDF";
    }
    else if (_rate_equation[i] == true)
    {
      _rate_coefficient[i] = NAN;
      _rate_type[i] = "Equation";
      // USE THIS CODE TO SEE IF VARIABLE IS CONTAINED WITHIN EQUATION
      //////////
      // if (_rate_equation_string[i].find("Tgas") != std::string::npos)
      // {
      //   std::cout << "found!" << std::endl;
      // }
      //////////

      // Here we need to parse the individual reaction equations to find the
      // variables and constants.
      // std::istringstream iss(_rate_equation_string[i]);
      // std::string token;
      // while (std::getline(iss >> std::ws, token,'/'))
      // {
      //   std::cout << token << std::endl;
      // }
    }
    else
    {
      _rate_coefficient[i] = std::stod(rate_coefficient_string[i]);
      _rate_type[i] = "Constant";
    }
  }

  _reactants.resize(_num_reactions);
  _products.resize(_num_reactions);
  _reversible_reaction.resize(_num_reactions);
  _electron_index.resize(_num_reactions, 0);
  // _species_electron.resize(_num_reactions, std::vector<bool>(_species.size()));

  // Split each reaction equation into reactants and products
  int superelastic_reactions =
      0; // stores number of superelastic reactions, which will be added to _num_reactions
  for (unsigned int i = 0; i < _num_reactions; ++i)
  {
    std::istringstream iss2(_reaction[i]);
    std::string token;

    // Isolate individual terms of each reaction
    unsigned int counter = 0;
    bool react_check = true;
    while (std::getline(iss2 >> std::ws, token, ' '))
    {
      // Check for non-variable entries. Skip the plus signs, and if an equals
      // sign shows up we switch from reactants to products.
      // (This is a pretty hacky way to do this...but it works.)
      if (token == "+")
      {
        // If "+", skip to next iteration
        continue;
      }
      else if (token == "=" || token == "->" || token == "=>")
      {
        // If "=", switch from reactants to products, reset counter, and then
        // skip to next iteration.
        _reversible_reaction[i] = false;
        react_check = false;
        counter = 0;
        continue;
      }
      else if (token == "<=>" || token == "<->")
      {
        superelastic_reactions += 1;
        _reversible_reaction[i] = true;

        react_check = false;
        counter = 0;
        continue;
        // mooseError("Cannot handle superelastic reactions yet. Add two separate reactions.");
      }

      // Check if we are on the left side (reactants) or right side (products)
      // of the reaction equation.
      _all_participants.push_back(token);
      if (react_check)
      {
        _reactants[i].push_back(token);
      }
      else
      {
        _products[i].push_back(token);
      }
      counter = counter + 1;
    }

    _num_reactants.push_back(_reactants[i].size());
    _num_products.push_back(_products[i].size());
    _species_count.resize(_num_reactions, std::vector<Real>(_species.size()));
    for (unsigned int j = 0; j < _species.size(); ++j)
    {
      for (unsigned int k = 0; k < _reactants[i].size(); ++k)
      {
        if (_reactants[i][k] == _species[j])
        {
          _species_count[i][j] -= 1;
        }
        if (getParam<bool>("include_electrons") == true)
        {
          if (_reactants[i][k] == getParam<std::string>("electron_density"))
          {
            _electron_index[i] = k;
          }
        }
      }
      for (unsigned int k = 0; k < _products[i].size(); ++k)
      {
        if (_products[i][k] == _species[j])
        {
          _species_count[i][j] += 1;
        }
      }
    }
  }

  std::string new_reaction;
  int new_index = _num_reactions - 1;

  // We also need to resize rate_coefficient and threshold_energy to account
  // for the new reaction(s)
  _superelastic_index.resize(_num_reactions + superelastic_reactions, 0);
  _superelastic_reaction.resize(_num_reactions + superelastic_reactions, false);
  _rate_coefficient.resize(_num_reactions + superelastic_reactions);
  _threshold_energy.resize(_num_reactions + superelastic_reactions);
  _rate_equation.resize(_num_reactions + superelastic_reactions);
  _species_count.resize(_num_reactions + superelastic_reactions,
                        std::vector<Real>(_species.size()));
  _reactants.resize(_reactants.size() + superelastic_reactions);
  _products.resize(_products.size() + superelastic_reactions);
  _aux_var_name.resize(_num_reactions + superelastic_reactions);
  if (superelastic_reactions > 0)
  {
    for (unsigned int i = 0; i < _num_reactions; ++i)
    {
      if (_reversible_reaction[i] == true)
      {
        // _reaction.resize(_num_reactions + 1);
        new_index += 1;
        // This index refers to the ORIGINAL reaction. Example:
        // If reaction #2 out of 5 (index = 1 from [0,4]) is reversible, then a
        // 6th reaction (index = 5) will be added. This is the superelastic reaction.
        // _superelastic_index is intended to refer back to the original reversible
        // reaction later in the code, so we can reverse any energy change and refer
        // to the forward reaction rate if necessary. Thus in this particular case,
        // _superelastic_index[5] = 1.
        _superelastic_index[new_index] = i;
        _superelastic_reaction[new_index] = true;
        _rate_coefficient[new_index] = NAN;
        _threshold_energy[new_index] = -_threshold_energy[i];
        _aux_var_name[new_index] = "rate_constant" + std::to_string(new_index);
        if (_rate_equation[i] == true)
        {
          _rate_equation[new_index] = true;
        }
        else
        {
          _rate_equation[new_index] = false;
        }

        // Here we reverse the products and reactants to build superelastic reactions.
        for (MooseIndex(_num_products[i]) j = 0; j < _num_products[i]; ++j)
        {
          new_reaction.append(_products[i][j]);
          _reactants[new_index].push_back(_products[i][j]);
          if (j == _num_products[i] - 1)
          {
            break;
          }
          else
          {
            new_reaction.append(" + ");
          }
        }
        new_reaction.append(" -> ");
        for (unsigned int j = 0; j < _reactants[i].size(); ++j)
        {
          new_reaction.append(_reactants[i][j]);
          _products[new_index].push_back(_reactants[i][j]);
          if (j == _reactants[i].size() - 1)
          {
            break;
          }
          else
          {
            new_reaction.append(" + ");
          }
        }
        _reaction.push_back(new_reaction);
      }

      // Calculate coefficients
      for (unsigned int j = 0; j < _species.size(); ++j)
      {
        for (unsigned int k = 0; k < _reactants[new_index].size(); ++k)
        {
          if (_reactants[new_index][k] == _species[j])
          {
            _species_count[new_index][j] -= 1;
          }
          if (getParam<bool>("include_electrons") == true)
          {
            if (_reactants[new_index][k] == getParam<std::string>("electron_density"))
            {
              _electron_index[new_index] = k;
            }
          }
        }
        for (unsigned int k = 0; k < _products[new_index].size(); ++k)
        {
          if (_products[new_index][k] == _species[j])
          {
            _species_count[new_index][j] += 1;
          }
        }
      }
    }
  }

  _num_reactions += superelastic_reactions;
  // for (unsigned int i=0; i<_num_reactions; ++i)
  // {
  //   std::cout << _reaction[i] << std::endl;
  //   for (unsigned int j=0; j<_species.size(); ++j)
  //   {
  //     std::cout << _species[j] << ", " << _species_count[i][j] << std::endl;
  //   }
  // }
  // mooseError("TEST");
  _reaction_coefficient_name.resize(_num_reactions);
  // Find the unique species across all reaction pathways
  // Note that this also accounts for species that are not tracked in case
  // some of the species are considered to be uniform background gases or
  // arbitrary source/sink terms.
  sort(_all_participants.begin(), _all_participants.end());
  std::vector<std::string>::iterator it;
  it = std::unique(_all_participants.begin(), _all_participants.end());
  _all_participants.resize(std::distance(_all_participants.begin(), it));

  // Find the stoichometric coefficient for each participant.
  _stoichiometric_coeff.resize(_reaction.size());

  for (unsigned int i = 0; i < _reaction.size(); ++i)
  {
    _stoichiometric_coeff[i].resize(_all_participants.size(), 0);

    for (unsigned int j = 0; j < _all_participants.size(); ++j)
    {
      for (unsigned int k = 0; k < _reactants[i].size(); ++k)
      {
        if (_reactants[i][k] == _all_participants[j])
        {
          _stoichiometric_coeff[i][j] -= 1;
        }
      }

      for (unsigned int k = 0; k < _products[i].size(); ++k)
      {
        if (_products[i][k] == _all_participants[j])
        {
          _stoichiometric_coeff[i][j] += 1;
        }
      }
    }
  }
  _reaction_participants.resize(_num_reactions);
  _reaction_stoichiometric_coeff.resize(_num_reactions);
  // Now we find which index of _all_participants is associated with _species
  // so they can be accurately referred to later if necessary.

  _species_index.resize(
      _species.size()); // Stores vector of indices relating _all_participants to _species.
  std::vector<std::string>::iterator iter;

  for (unsigned int i = 0; i < _species.size(); ++i)
  {
    iter = std::find(_all_participants.begin(), _all_participants.end(), _species[i]);
    _species_index[i] = std::distance(_all_participants.begin(), iter);
  }

  // Finally, we reduce _all_participants to find just the relevant participants
  // (and stoichiometric coefficients) for each individual reaction.

  for (unsigned int i = 0; i < _num_reactions; ++i)
  {
    std::vector<std::string> species_temp(
        _reactants[i]); // Copy reactants into new temporary vector
    species_temp.insert(species_temp.end(),
                        _products[i].begin(),
                        _products[i].end()); // Append products to new temp vector (so it now stores
                                             // all reactants and products)

    // Separate out the unique values from species_temp
    sort(species_temp.begin(), species_temp.end());
    std::vector<std::string>::iterator it;
    it = std::unique(species_temp.begin(), species_temp.end());
    species_temp.resize(std::distance(species_temp.begin(), it));
    // _reaction_participants[i].resize(species_temp.size());

    // Copy over the species from species_temp to the permanent _reaction_participants vector
    // Now each unique participant per reaction is stored in _reaction_participants.
    // Note that reaction_participants only stores the TRACKED species.
    for (unsigned int j = 0; j < species_temp.size(); ++j)
    {
      if (std::find(_species.begin(), _species.end(), species_temp[j]) != _species.end())
        _reaction_participants[i].push_back(species_temp[j]);
    }

    _reaction_stoichiometric_coeff[i].resize(_reaction_participants[i].size(), 0);

    for (unsigned int j = 0; j < _reaction_participants[i].size(); ++j)
    {
      for (unsigned int k = 0; k < _reactants[i].size(); ++k)
      {
        if (_reactants[i][k] == _reaction_participants[i][j])
        {
          _reaction_stoichiometric_coeff[i][j] -= 1;
        }
      }

      for (unsigned int k = 0; k < _products[i].size(); ++k)
      {
        if (_products[i][k] == _reaction_participants[i][j])
        {
          _reaction_stoichiometric_coeff[i][j] += 1;
        }
      }
    }
  }

  // for (unsigned int i=0; i<_num_reactions; ++i)
  // {
  //   std::cout << "Reaction: " << _reaction[i] << std::endl;
  //   for (unsigned int j=0; j<_reaction_participants[i].size(); ++j)
  //     std::cout << "    " << _reaction_participants[i][j] << ", " <<
  //     _reaction_stoichiometric_coeff[i][j] << std::endl;
  // }
}

void
AddScalarReactionsOld::act()
{
  int v_index;
  std::vector<int> other_index;
  std::vector<int> reactant_indices;

  // Allocate space for all three reactants. (Used as a check to see if the other
  // reactants are tracked; if they are, they are passed as coupled variables.)
  // Note: possible to replace with 'args' as a coupled variable array?
  std::vector<std::string> other_variables;
  other_variables.resize(3);
  other_variables[0] = "v";
  other_variables[1] = "w";
  other_variables[2] = "x";
  bool find_other;

  std::vector<bool> include_species;
  std::string product_kernel_name;
  std::string reactant_kernel_name;
  std::string energy_kernel_name;
  std::vector<NonlinearVariableName> variables =
      getParam<std::vector<NonlinearVariableName>>("species");

  bool gas_tracking = getParam<bool>("gas_tracking");
  std::vector<std::string> gas_species = getParam<std::vector<std::string>>("gas_species");

  if (gas_tracking)
  {
    // mooseError("Functionality for tracking neutral gas densities and temperatures is under
    // development.");
    std::cout
        << "WARNING: Functionality for tracking neutral gas densities is still under development."
        << std::endl;
  }

  if (_current_task == "add_aux_variable")
  {
    for (unsigned int i = 0; i < _num_reactions; ++i)
    {
      _problem->addAuxScalarVariable(_aux_var_name[i], FIRST);
    }
  }

  if (_current_task == "add_user_object")
  {
    for (unsigned int i = 0; i < _num_reactions; ++i)
    {
      // If this particular reaction is not reversible, skip to the next one.
      // If it is, we add the necessary user object to calculate the 7-term
      // polynomial expansion.
      // (This just sets the coefficients. The actual equilibrium constant
      // is calculated through an auxiliary variable, as all other rate coefficients are.)
      if (!_reversible_reaction[i])
        continue;
      else
      {
        InputParameters params = _factory.getValidParams("PolynomialCoefficients");
        params.set<std::vector<Real>>("stoichiometric_coeff") = _reaction_stoichiometric_coeff[i];
        params.set<std::vector<std::string>>("participants") = _reaction_participants[i];
        params.set<std::string>("file_location") = "PolynomialCoefficients";
        params.set<ExecFlagEnum>("execute_on") = "INITIAL";
        _problem->addUserObject(
            "PolynomialCoefficients", "superelastic_coeff" + std::to_string(i), params);
      }
    }
  }

  if (_current_task == "add_aux_scalar_kernel")
  {
    for (unsigned int i = 0; i < _num_reactions; ++i)
    {
      if (_rate_type[i] == "EEDF" && !_superelastic_reaction[i])
      {
        InputParameters params = _factory.getValidParams("DataReadScalar");
        params.set<AuxVariableName>("variable") = {_aux_var_name[i]};
        params.set<std::vector<VariableName>>("sampler") = {"reduced_field"};
        params.set<FileName>("property_file") = "reaction_" + _reaction[i] + ".txt";
        params.set<std::string>("file_location") = getParam<std::string>("file_location");
        params.set<ExecFlagEnum>("execute_on") = "TIMESTEP_BEGIN";
        _problem->addAuxScalarKernel("DataReadScalar", "aux_rate" + std::to_string(i), params);
      }
      else if (_rate_type[i] == "Equation" && !_superelastic_reaction[i])
      {
        InputParameters params = _factory.getValidParams("ParsedScalarRateCoefficient");
        params.set<AuxVariableName>("variable") = {_aux_var_name[i]};
        params.set<std::string>("function") = _rate_equation_string[i];
        params.set<bool>("file_read") = true;
        params.set<std::vector<std::string>>("file_value") = {"Te"};
        params.set<std::vector<std::string>>("constant_names") =
            getParam<std::vector<std::string>>("equation_constants");
        params.set<std::vector<std::string>>("constant_expressions") =
            getParam<std::vector<std::string>>("equation_values");
        params.set<UserObjectName>("electron_temperature") = "value_provider";
        params.set<std::vector<VariableName>>("reduced_field") = {"reduced_field"};
        if (getParam<bool>("gas_temperature"))
        {
          params.set<bool>("gas_temperature") = true;
          std::vector<NonlinearVariableName> gas_temp =
              getParam<std::vector<NonlinearVariableName>>("equation_variables");
          std::string temp_var;
          for (unsigned int m = 0; m < gas_temp.size(); ++m)
          {
            if (gas_temp[m] == "Tgas")
              temp_var = gas_temp[m];
            break;
          }
          params.set<std::vector<VariableName>>("args") = {temp_var};
        }
        params.set<std::vector<VariableName>>("args") = {"Te"};
        // params.set<ExecFlagEnum>("execute_on") = "TIMESTEP_BEGIN NONLINEAR";
        params.set<ExecFlagEnum>("execute_on") = "TIMESTEP_BEGIN";
        _problem->addAuxScalarKernel(
            "ParsedScalarRateCoefficient", "aux_rate" + std::to_string(i), params);
      }
      else if (_rate_type[i] == "Constant" && !_superelastic_reaction[i])
      {
        InputParameters params = _factory.getValidParams("AuxInitialConditionScalar");
        params.set<Real>("initial_condition") = _rate_coefficient[i];
        params.set<AuxVariableName>("variable") = {_aux_var_name[i]};
        params.set<ExecFlagEnum>("execute_on") = "INITIAL";
        _problem->addAuxScalarKernel(
            "AuxInitialConditionScalar", "aux_initialization_rxn" + std::to_string(i), params);
      }
      else if (_superelastic_reaction[i])
      {
        InputParameters params = _factory.getValidParams("SuperelasticRateCoefficientScalar");
        params.set<AuxVariableName>("variable") = {_aux_var_name[i]};
        params.set<std::vector<VariableName>>("forward_coefficient") = {
            _aux_var_name[_superelastic_index[i]]};
        params.set<Real>("Tgas_const") = 300;
        params.set<UserObjectName>("polynomial_provider") =
            "superelastic_coeff" + std::to_string(_superelastic_index[i]);
        params.set<ExecFlagEnum>("execute_on") = "TIMESTEP_BEGIN";
        _problem->addAuxScalarKernel(
            "SuperelasticRateCoefficientScalar", "aux_rate" + std::to_string(i), params);
      }
    }
  }

  if (_current_task == "add_scalar_kernel")
  {
    int index; // stores index of species in the reactant/product arrays
    std::vector<std::string>::iterator iter;
    std::vector<Real> rxn_coeff = getParam<std::vector<Real>>("reaction_coefficient");
    for (unsigned int i = 0; i < _num_reactions; ++i)
    {
      if (_reactants[i].size() == 1)
      {
        product_kernel_name = "Product1BodyScalar";
        reactant_kernel_name = "Reactant1BodyScalar";
      }
      else if (_reactants[i].size() == 2)
      {
        product_kernel_name = "Product2BodyScalar";
        reactant_kernel_name = "Reactant2BodyScalar";
      }
      else
      {
        product_kernel_name = "Product3BodyScalar";
        reactant_kernel_name = "Reactant3BodyScalar";
      }

      for (MooseIndex(_species) j = 0; j < _species.size(); ++j)
      {
        iter = std::find(_reactants[i].begin(), _reactants[i].end(), _species[j]);
        index = std::distance(_reactants[i].begin(), iter);

        if (iter != _reactants[i].end())
        {
          reactant_indices.resize(_reactants[i].size());
          for (unsigned int k = 0; k < _reactants[i].size(); ++k)
            reactant_indices[k] = k;
          reactant_indices.erase(reactant_indices.begin() + index);
          for (unsigned int k = 0; k < reactant_indices.size(); ++k)
          {
            find_other =
                std::find(_species.begin(), _species.end(), _reactants[i][reactant_indices[k]]) !=
                _species.end();
            if (find_other)
              continue;
            else
              reactant_indices.erase(reactant_indices.begin() + k);
          }
          v_index = std::abs(index - 1);
          find_other =
              std::find(_species.begin(), _species.end(), _reactants[i][v_index]) != _species.end();
          if (_species_count[i][j] < 0)
          {
            InputParameters params = _factory.getValidParams(reactant_kernel_name);
            params.set<NonlinearVariableName>("variable") = _species[j];
            params.set<Real>("coefficient") = _species_count[i][j];
            params.set<Real>("n_gas") = 3.219e18;
            params.set<std::vector<VariableName>>("rate_coefficient") = {_aux_var_name[i]};
            params.set<bool>("rate_constant_equation") = true;
            if (find_other)
            {
              for (unsigned int k = 0; k < reactant_indices.size(); ++k)
                params.set<std::vector<VariableName>>(other_variables[k]) = {
                    _reactants[i][reactant_indices[k]]};
            }
            _problem->addScalarKernel(
                reactant_kernel_name, "kernel" + std::to_string(j) + "_" + _reaction[i], params);
          }
        }

        iter = std::find(_products[i].begin(), _products[i].end(), _species[j]);
        include_species.resize(_reactants[i].size());
        for (unsigned int k = 0; k < _reactants[i].size(); ++k)
        {
          include_species[k] =
              std::find(_species.begin(), _species.end(), _reactants[i][k]) != _species.end();
        }
        if (iter != _products[i].end())
        {

          if (_species_count[i][j] > 0)
          {
            InputParameters params = _factory.getValidParams(product_kernel_name);
            params.set<NonlinearVariableName>("variable") = _species[j];
            params.set<Real>("n_gas") = 3.219e18;
            params.set<std::vector<VariableName>>("rate_coefficient") = {_aux_var_name[i]};
            params.set<bool>("rate_constant_equation") = true;
            params.set<Real>("coefficient") = _species_count[i][j];
            for (unsigned int k = 0; k < _reactants[i].size(); ++k)
            {
              if (include_species[k])
              {
                params.set<std::vector<VariableName>>(other_variables[k]) = {_reactants[i][k]};
                if (_species[j] == _reactants[i][k])
                {
                  params.set<bool>(other_variables[k] + "_eq_u") = true;
                }
              }
            }
            _problem->addScalarKernel(product_kernel_name,
                                      "kernel_prod" + std::to_string(j) + "_" + _reaction[i],
                                      params);
          }
        }
      }
    }
  }
}
