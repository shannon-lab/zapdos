#include "ChemicalReactions.h"
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

registerMooseAction("CraneApp", ChemicalReactions, "add_aux_variable");
registerMooseAction("CraneApp", ChemicalReactions, "add_aux_scalar_kernel");
registerMooseAction("CraneApp", ChemicalReactions, "add_material");
registerMooseAction("CraneApp", ChemicalReactions, "add_kernel");
registerMooseAction("CraneApp", ChemicalReactions, "add_scalar_kernel");
registerMooseAction("CraneApp", ChemicalReactions, "add_function");

template <>
InputParameters
validParams<ChemicalReactions>()
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
  params.addRequiredParam<std::string>(
      "reaction_coefficient_format",
      "The format of the reaction coefficient. Options: rate or townsend.");
  params.addParam<std::string>(
      "file_location",
      "",
      "The location of the reaction rate files. Default: empty string (current directory).");
  params.addParam<bool>("use_moles", "Whether to use molar units.");
  params.addParam<std::string>(
      "sampling_format",
      "reduced_field",
      "Sample rate constants with E/N (reduced_field) or Te (electron_energy).");
  params.addParam<bool>(
      "scalar_problem", false, "The problem is scalar if it is a pure ODE problem (Global/0D).");
  params.addParam<std::vector<std::string>>("equation_constants",
                                            "The constants included in the reaction equation(s).");
  params.addParam<std::vector<std::string>>(
      "equation_values", "The values of the constants included in the reaction equation(s).");
  params.addParam<std::vector<VariableName>>(
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

ChemicalReactions::ChemicalReactions(InputParameters params)
  : Action(params),
    _species(getParam<std::vector<NonlinearVariableName>>("species")),
    _species_energy(getParam<std::vector<NonlinearVariableName>>("species_energy")),
    _input_reactions(getParam<std::string>("reactions")),
    _r_units(getParam<Real>("position_units")),
    _coefficient_format(getParam<std::string>("reaction_coefficient_format")),
    _sampling_format(getParam<std::string>("sampling_format")),
    _use_log(getParam<bool>("use_log")),
    _scalar_problem(getParam<bool>("scalar_problem")),
    _energy_change(false)
{
  // 1) split into reactants and products
  // 2) split products into products and reaction rate
  // 3) check reaction rate; if constant, store. If "BOLOS", read data file.
  // 4) split reactants and products into individual species
  // 5) Apply appropriate kernels and/or materials. (In the act() function.)

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
        _aux_var_name[new_index] = "rate_constant" + std::to_string(i);
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
  }

  _num_reactions += superelastic_reactions;
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
}

void
ChemicalReactions::act()
{
  int v_index;
  std::vector<int> other_index;
  std::vector<int> reactant_indices;
  std::vector<std::string> other_variables;
  other_variables.resize(3);
  other_variables[0] = "v";
  other_variables[1] = "w";
  other_variables[2] = "x";
  bool find_other;
  std::vector<bool> include_species;
  unsigned int target; // stores index of target species for electron-impact reactions
  std::string product_kernel_name;
  std::string reactant_kernel_name;
  std::string energy_kernel_name;
  std::vector<NonlinearVariableName> variables =
      getParam<std::vector<NonlinearVariableName>>("species");
  // std::vector<VariableName> electron_energy =
  // getParam<std::vector<VariableName>>("electron_energy");
  // std::string electron_density = getParam<std::string>("electron_density");

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

  else if (_current_task == "add_function" && _scalar_problem == false)
  {
    mooseError("Unable to add parsed materials! (Work in progress...)");
  }
  //
  // if (_current_task == "add_user_object" && _scalar_problem == true)
  // {
  //   for (unsigned int i=0; i<_num_reactions; ++i)
  //   {
  //     // if (_rate_type[i] == "EEDF")
  //     // {
  //     //   InputParameters params = _factory.getValidParams("RateCoefficientProvider");
  //     //   params.set<std::string>("file_location") = getParam<std::string>("file_location");
  //     //   params.set<std::string>("sampling_format") = _sampling_format;
  //     //   params.set<FileName>("property_file") = "reaction_"+_reaction[i]+".txt";
  //     //   params.set<std::string>("rate_format") = _rate_type[i];
  //     //   params.set<std::vector<VariableName>>("reduced_field") = getParam<std::vector<VariableName>>("rate_provider_var");
  //     //   // params.set<std::vector<VariableName>>("reduced_field") = {"Te"};
  //     //   _problem->addUserObject("RateCoefficientProvider", "rate_coefficient"+std::to_string(i), params);
  //     // }
  //     // else if (_rate_type[i] == "Constant")
  //     if (_rate_type[i] == "Constant")
  //     {
  //       InputParameters params = _factory.getValidParams("RateCoefficientProvider");
  //       params.set<Real>("rate_constant") = _rate_coefficient[i];
  //       params.set<std::string>("rate_format") = _rate_type[i];
  //       _problem->addUserObject("RateCoefficientProvider", "rate_coefficient"+std::to_string(i),
  //       params);
  //     }
  //     // else if (_rate_type[i] == "Equation")
  //     else if (_rate_type[i] == "Equation" || _rate_type[i] == "EEDF")
  //     {
  //       // This is essentially a "default" UserObject. It is not used.
  //       // This is done to prevent having multiple different kernels just to distinguish between
  //       // equation-based rate constants and the file or constant values.
  //       // Possible to include default UserObject from kernel? Not sure...
  //       InputParameters params = _factory.getValidParams("RateCoefficientProvider");
  //       // params.set<std::string>("rate_format") = _rate_type[i];
  //       params.set<std::string>("rate_format") = "Equation";
  //       _problem->addUserObject("RateCoefficientProvider", "rate_coefficient"+std::to_string(i),
  //       params);
  //     }
  //     else
  //     {
  //       mooseError("No scalar kernel available for rate format type " + _rate_type[i] + "!");
  //     }
  //   }
  // }

  if (_current_task == "add_aux_variable" && _scalar_problem == true)
  {
    for (unsigned int i = 0; i < _num_reactions; ++i)
    {
      // if (_rate_type[i] == "Equation" || _rate_type[i] == "EEDF")
      // {
      // if (_rate_type[i] == "Constant")
      // {
      // _problem->addAuxScalarVariable(_aux_var_name[i], FIRST);
      // _problem->createInitialConditionAction(_aux_var_name[i], 5.0);
      // }
      // else
      _problem->addAuxScalarVariable(_aux_var_name[i], FIRST);
    }
  }

  if (_current_task == "add_aux_scalar_kernel" && _scalar_problem == true)
  {
    for (unsigned int i = 0; i < _num_reactions; ++i)
    {
      if (_rate_type[i] == "EEDF")
      {
        InputParameters params = _factory.getValidParams("DataReadScalar");
        params.set<AuxVariableName>("variable") = {_aux_var_name[i]};
        params.set<std::vector<VariableName>>("sampler") = {"reduced_field"};
        params.set<FileName>("property_file") = "reaction_" + _reaction[i] + ".txt";
        params.set<std::string>("file_location") = "OutputRates_Crane_ex3";
        params.set<ExecFlagEnum>("execute_on") = "TIMESTEP_BEGIN";
        _problem->addAuxScalarKernel("DataReadScalar", "aux_rate" + std::to_string(i), params);
      }
      else if (_rate_type[i] == "Equation")
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
      else // Constant is only other option
      {
        InputParameters params = _factory.getValidParams("AuxInitialConditionScalar");
        params.set<Real>("initial_condition") = _rate_coefficient[i];
        params.set<AuxVariableName>("variable") = {_aux_var_name[i]};
        params.set<ExecFlagEnum>("execute_on") = "INITIAL";
        _problem->addAuxScalarKernel(
            "AuxInitialConditionScalar", "aux_initialization_rxn" + std::to_string(i), params);
      }
      // continue;
      // InputParameters params = _factory.getValidParams("")
    }
  }

  if (_current_task == "add_material" && _scalar_problem == false)
  {
    for (unsigned int i = 0; i < _num_reactions; ++i)
    {
      _reaction_coefficient_name[i] = "alpha_" + _reaction[i];
      if (_rate_type[i] == "EEDF" && _coefficient_format == "townsend")
      {
        // BOLOS and BOLSIG+ both get stored as NAN in _rate_coefficient, as to
        // rate constants based on an equation (_rate_equation).
        // Superelastic reactions need to have their constants calculated separately.
        // Coefficient format chooses which specific material to apply.
        Real position_units = getParam<Real>("position_units");
        InputParameters params = _factory.getValidParams("EEDFRateConstantTownsend");
        params.set<std::string>("reaction") = _reaction[i];
        params.set<std::string>("file_location") = getParam<std::string>("file_location");
        params.set<Real>("position_units") = position_units;
        params.set<std::vector<VariableName>>("em") = {_reactants[i][_electron_index[i]]};
        params.set<std::vector<VariableName>>("mean_en") =
            getParam<std::vector<VariableName>>("electron_energy");
        params.set<std::string>("reaction_coefficient_format") = _coefficient_format;
        params.set<std::string>("sampling_format") = _sampling_format;

        // This section determines if the target species is a tracked variable.
        // If it isn't, the target is assumed to be the background gas (_n_gas).
        // (This cannot handle gas mixtures yet.)
        bool target_species_tracked = false;
        for (unsigned int j = 0; j < _species.size(); ++j)
        {
          // Checking for the target species in electron-impact reactions, so
          // electrons are ignored.
          if (getParam<bool>("include_electrons") == true)
          {
            if (_species[j] == getParam<std::string>("electron_density"))
            {
              continue;
            }
          }

          for (unsigned int k = 0; k < _reactants[i].size(); ++k)
          {
            if (_reactants[i][k] == _species[j])
            {
              target_species_tracked = true;
              target = k;
              break;
            }
          }

          if (target_species_tracked)
            break;
        }
        if (target_species_tracked)
        {
          params.set<std::vector<VariableName>>("target_species") = {_reactants[i][target]};
        }
        params.set<bool>("elastic_collision") = {_elastic_collision[i]};
        params.set<FileName>("property_file") = "reaction_" + _reaction[i] + ".txt";

        _problem->addMaterial("EEDFRateConstantTownsend", "reaction_" + std::to_string(i), params);
      }
      else if (_rate_type[i] == "EEDF" && _coefficient_format == "rate")
      {
        Real position_units = getParam<Real>("position_units");
        InputParameters params = _factory.getValidParams("EEDFRateConstant");
        params.set<std::string>("reaction") = _reaction[i];
        params.set<std::string>("file_location") = getParam<std::string>("file_location");
        params.set<Real>("position_units") = position_units;
        params.set<std::string>("sampling_format") = _sampling_format;
        params.set<FileName>("property_file") = "reaction_" + _reaction[i] + ".txt";
        _problem->addMaterial("EEDFRateConstant", "reaction_" + std::to_string(i), params);
      }
      else if (_rate_type[i] == "Constant")
      {
        InputParameters params = _factory.getValidParams("GenericRateConstant");
        params.set<std::string>("reaction") = _reaction[i];
        params.set<Real>("reaction_rate_value") = _rate_coefficient[i];
        _problem->addMaterial("GenericRateConstant", "reaction_" + std::to_string(i), params);
      }
      else if (_rate_type[i] == "Equation")
      {
        std::cout << "WARNING: CRANE cannot yet handle equation-based equations." << std::endl;
        // This should be a mooseError...but I'm using it for testing purposes.
      }
      else if (_superelastic_reaction[i] == true)
      {
        // first we need to figure out which participants exist, and pass only
        // those stoichiometric coefficients and names.
        std::vector<std::string> active_participants;

        for (unsigned int k = 0; k < _reactants[i].size(); ++k)
        {
          active_participants.push_back(_reactants[i][k]);
        }
        for (unsigned int k = 0; k < _products[i].size(); ++k)
        {
          active_participants.push_back(_products[i][k]);
        }
        sort(active_participants.begin(), active_participants.end());
        std::vector<std::string>::iterator it;
        it = std::unique(active_participants.begin(), active_participants.end());
        active_participants.resize(std::distance(active_participants.begin(), it));

        // Now we find the correct index to obtain the necessary stoichiometric values
        std::vector<std::string>::iterator iter;
        std::vector<Real> active_constants;
        for (unsigned int k = 0; k < active_participants.size(); ++k)
        {
          iter =
              std::find(_all_participants.begin(), _all_participants.end(), active_participants[k]);
          active_constants.push_back(
              _stoichiometric_coeff[i][std::distance(_all_participants.begin(), iter)]);
        }

        InputParameters params = _factory.getValidParams("SuperelasticReactionRate");
        params.set<std::string>("reaction") = _reaction[i];
        params.set<std::string>("original_reaction") = _reaction[_superelastic_index[i]];
        params.set<std::vector<Real>>("stoichiometric_coeff") = active_constants;
        params.set<std::vector<std::string>>("participants") = active_participants;
        params.set<std::string>("file_location") = "PolynomialCoefficients";
        _problem->addMaterial("SuperelasticReactionRate", "reaction_" + std::to_string(i), params);
      }

      // Now we check for reactions that include a change of energy.
      // Will this require  its own material?
      if (_energy_change == true)
      {
        // Gas temperature is almost in place, but not finished yet.
        std::cout << "WARNING: energy dependence is not yet implemented." << std::endl;
      }
    }
  }

  // adds scalar kernels (if 0D problem)
  if (_current_task == "add_scalar_kernel" && _scalar_problem == true)
  {
    int index; // stores index of species in the reactant/product arrays
    std::vector<std::string>::iterator iter;
    std::vector<Real> rxn_coeff = getParam<std::vector<Real>>("reaction_coefficient");
    for (unsigned int i = 0; i < _num_reactions; ++i)
    {
      // std::cout << rxn_coeff[i] << std::endl;
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
            // params.set<Real>("n_gas") = 3.219e24;
            params.set<Real>("n_gas") = 3.219e18;
            // params.set<Real>("n_gas") = 1;
            // params.set<UserObjectName>("rate_provider") = "rate_coefficient"+std::to_string(i);
            // params.set<std::string>("reaction") = _reaction[i];
            // if (_rate_equation[i])
            // if (_rate_type[i] == "Equation" || _rate_type[i] == "EEDF")
            // {
            params.set<std::vector<VariableName>>("rate_coefficient") = {_aux_var_name[i]};
            params.set<bool>("rate_constant_equation") = true;
            // }
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
            // std::cout << _species_count[i][j] << std::endl;
            // std::cout <<
            InputParameters params = _factory.getValidParams(product_kernel_name);
            params.set<NonlinearVariableName>("variable") = _species[j];
            // params.set<Real>("n_gas") = 3.219e24;
            params.set<Real>("n_gas") = 3.219e18;
            // params.set<Real>("n_gas") = 1;
            // params.set<Real>("reaction_coefficient") = rxn_coeff[i];
            // params.set<UserObjectName>("rate_provider") = "rate_coefficient"+std::to_string(i);
            // if (_rate_equation[i])
            // if (_rate_type[i] == "Equation" || _rate_type[i] == "EEDF")
            // {
            params.set<std::vector<VariableName>>("rate_coefficient") = {_aux_var_name[i]};
            params.set<bool>("rate_constant_equation") = true;
            // }
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

  // Add appropriate kernels to each reactant and product.
  if (_current_task == "add_kernel" && _scalar_problem == false)
  {
    int index; // stores index of species in the reactant/product arrays
    std::vector<std::string>::iterator iter;
    for (unsigned int i = 0; i < _num_reactions; ++i)
    {
      // if (!isnan(_rate_coefficient[i]) || _rate_equation[i] == true || _superelastic_reaction[i]
      // == true || getParam<bool>("track_electron_energy") == false)
      if (_coefficient_format == "rate")
      {
        if (_reactants[i].size() == 1)
        {
          product_kernel_name = "ProductFirstOrder";
          reactant_kernel_name = "ReactantFirstOrder";
        }
        else if (_reactants[i].size() == 2)
        {
          product_kernel_name = "ProductSecondOrder";
          reactant_kernel_name = "ReactantSecondOrder";
        }
        else
        {
          product_kernel_name = "ProductThirdOrder";
          reactant_kernel_name = "ReactantThirdOrder";
        }
        if (_use_log)
        {
          product_kernel_name += "Log";
          reactant_kernel_name += "Log";
        }
      }
      else if (_coefficient_format == "townsend")
      {
        if (getParam<bool>("track_electron_energy") == true)
        {
          if (_coefficient_format == "townsend")
          {
            product_kernel_name = "ElectronImpactReactionProduct";
            reactant_kernel_name = "ElectronImpactReactionReactant";
          }
        }
      }

      for (MooseIndex(_species) j = 0; j < _species.size(); ++j)
      {
        iter = std::find(_reactants[i].begin(), _reactants[i].end(), _species[j]);
        index = std::distance(_reactants[i].begin(), iter);

        if (iter != _reactants[i].end())
        {
          // Now we see if the second reactant is a tracked species.
          // We only treat two-body reactions now. This will need to be changed for three-body
          // reactions. e.g. 1) find size of reactants array 2) use find() to search other values
          // inside that size that are not == index 3) same result!
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
            if (_coefficient_format == "townsend")
            {
              InputParameters params = _factory.getValidParams(reactant_kernel_name);
              // params.set<NonlinearVariableName>("variable") = _reactants[i][index];
              params.set<NonlinearVariableName>("variable") = _species[j];
              params.set<std::vector<VariableName>>("mean_en") =
                  getParam<std::vector<VariableName>>("electron_energy");
              params.set<std::vector<VariableName>>("potential") =
                  getParam<std::vector<VariableName>>("potential");
              params.set<std::vector<VariableName>>("em") = {
                  getParam<std::string>("electron_density")};
              params.set<Real>("position_units") = _r_units;
              params.set<std::string>("reaction") = _reaction[i];
              // params.set<std::string>("reaction_coefficient_name") =
              // _reaction_coefficient_name[i];
              _problem->addKernel(
                  reactant_kernel_name, "kernel" + std::to_string(j) + "_" + _reaction[i], params);
            }
            else if (_coefficient_format == "rate")
            {
              InputParameters params = _factory.getValidParams(reactant_kernel_name);
              params.set<NonlinearVariableName>("variable") = _species[j];
              params.set<Real>("coefficient") = _species_count[i][j];
              params.set<std::string>("reaction") = _reaction[i];

              if (find_other)
              {
                for (unsigned int k = 0; k < reactant_indices.size(); ++k)
                  params.set<std::vector<VariableName>>(other_variables[k]) = {
                      _reactants[i][reactant_indices[k]]};
                // params.set<std::vector<VariableName>>("v") = {_reactants[i][v_index]};
              }
              _problem->addKernel(
                  reactant_kernel_name, "kernel" + std::to_string(j) + "_" + _reaction[i], params);
            }
          }
        }

        // Now we do the same thing for the products side of the reaction
        iter = std::find(_products[i].begin(), _products[i].end(), _species[j]);
        // index = std::distance(_products[i].begin(), iter);
        // species_v = std::find(_species.begin(), _species.end(), _reactants[i][0]) !=
        // _species.end(); species_w = std::find(_species.begin(), _species.end(), _reactants[i][1])
        // != _species.end();
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
            if (_coefficient_format == "townsend")
            {
              InputParameters params = _factory.getValidParams(product_kernel_name);
              params.set<NonlinearVariableName>("variable") = _species[j];
              params.set<std::vector<VariableName>>("mean_en") =
                  getParam<std::vector<VariableName>>("electron_energy");
              if (_coefficient_format == "townsend")
                params.set<std::vector<VariableName>>("potential") =
                    getParam<std::vector<VariableName>>("potential");
              params.set<std::vector<VariableName>>("em") = {
                  getParam<std::string>("electron_density")};
              params.set<Real>("position_units") = _r_units;
              params.set<std::string>("reaction") = _reaction[i];
              params.set<std::string>("reaction_coefficient_name") = _reaction_coefficient_name[i];
              _problem->addKernel(product_kernel_name,
                                  "kernel_prod" + std::to_string(j) + "_" + _reaction[i],
                                  params);
            }
            else if (_coefficient_format == "rate")
            {
              InputParameters params = _factory.getValidParams(product_kernel_name);
              params.set<NonlinearVariableName>("variable") = _species[j];
              params.set<std::string>("reaction") = _reaction[i];
              // This loop includes reactants as long as they are tracked species.
              // If a species is not tracked, it is treated as a background gas.
              for (unsigned int k = 0; k < _reactants[i].size(); ++k)
              {
                if (include_species[k])
                {
                  params.set<std::vector<VariableName>>(other_variables[k]) = {_reactants[i][k]};
                  if (_species[j] == _reactants[i][k])
                  {
                    params.set<bool>("_" + other_variables[k] + "_eq_u") = true;
                  }
                }
              }
              params.set<Real>("coefficient") = _species_count[i][j];
              _problem->addKernel(product_kernel_name,
                                  "kernel_prod" + std::to_string(j) + "_" + _reaction[i],
                                  params);
            }
          }
        }
      }

      // To do: add energy kernels here
    }
  }
}
