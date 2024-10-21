#include "AddGeneralReactions.h"
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

registerMooseAction("CraneApp", AddGeneralReactions, "add_aux_variable");
registerMooseAction("CraneApp", AddGeneralReactions, "add_aux_kernel");
registerMooseAction("CraneApp", AddGeneralReactions, "add_material");
registerMooseAction("CraneApp", AddGeneralReactions, "add_kernel");
registerMooseAction("CraneApp", AddGeneralReactions, "add_function");

template <>
InputParameters
validParams<AddGeneralReactions>()
{
  MooseEnum families(AddVariableAction::getNonlinearVariableFamilies());
  MooseEnum orders(AddVariableAction::getNonlinearVariableOrders());

  InputParameters params = validParams<ChemicalReactionsBase>();
  params.addRequiredParam<std::string>(
      "reaction_coefficient_format",
      "The format of the reaction coefficient. Options: rate or townsend.");
  params.addParam<std::vector<VariableName>>(
      "potential", "The electric potential, used for energy-dependent reaction rates.");
  params.addParam<std::vector<std::string>>(
      "aux_species", "Auxiliary species that are not included in nonlinear solve.");
  params.addParam<std::vector<SubdomainName>>("block",
                                              "The subdomain that this action applies to.");
  params.addClassDescription(
      "This Action automatically adds the necessary kernels and materials for a reaction network.");

  return params;
}

AddGeneralReactions::AddGeneralReactions(InputParameters params)
  : ChemicalReactionsBase(params),
    _coefficient_format(getParam<std::string>("reaction_coefficient_format")),
    _aux_species(getParam<std::vector<std::string>>("aux_species"))

{
  if (_coefficient_format == "townsend" && !isParamValid("electron_density"))
    mooseError(
        "Coefficient format type 'townsend' requires an input parameter 'electron_density'!");

  if (_coefficient_format == "townsend" && !isParamValid("electron_energy"))
    mooseError("Coefficient format type 'townsend' requires an input parameter 'electron_energy'!");
}

void
AddGeneralReactions::act()
{
  int v_index;
  std::vector<int> other_index;
  std::vector<int> reactant_indices;
  std::vector<bool> reactant_species; // This says whether the reactant corresponding to
                                      // reactant_indices is a species.
  // std::vector<bool> reactant_aux; // This says whether each reactant is an aux variable or not.
  // This is important because aux variables do not contribute to the jacobian!
  std::vector<std::string> other_variables;
  other_variables.resize(3);
  other_variables[0] = "v";
  other_variables[1] = "w";
  other_variables[2] = "x";
  bool find_other;
  bool find_aux;
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

  // if (_current_task == "add_aux_variable")
  // {
  //   for (unsigned int i=0; i < _num_reactions; ++i)
  //   {
  //     _problem->addAuxVariable(_aux_var_name[i], FIRST);
  //   }
  // }

  if (_current_task == "add_material")
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
        params.set<std::vector<VariableName>>("mean_en") = {_electron_energy[0]};
        // params.set<std::string>("reaction_coefficient_format") = _coefficient_format;
        // params.set<std::string>("sampling_format") = _sampling_format;

        // This section determines if the target species is a tracked variable.
        // If it isn't, the target is assumed to be the background gas (_n_gas).
        // (This cannot handle gas mixtures yet.)
        bool target_species_tracked = false;
        bool target_species_aux = false;
        for (unsigned int j = 0; j < _species.size(); ++j)
        {
          // Checking for the target species in electron-impact reactions, so
          // electrons are ignored.
          // if (getParam<bool>("include_electrons") == true)
          // {
          if (_species[j] == getParam<std::string>("electron_density"))
          {
            continue;
          }
          // }

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
        for (unsigned int j = 0; j < _aux_species.size(); ++j)
        {
          for (unsigned int k = 0; k < _reactants[i].size(); ++k)
          {
            if (_reactants[i][k] == _aux_species[j])
            {
              target_species_aux = true;
              break;
            }
          }

          if (target_species_aux)
            break;
        }
        if (target_species_tracked)
        {
          params.set<std::vector<VariableName>>("target_species") = {_reactants[i][target]};
        }
        // if (target_species_aux)
        params.set<bool>("is_target_aux") = target_species_aux;

        params.set<bool>("elastic_collision") = {_elastic_collision[i]};
        params.set<FileName>("property_file") = "reaction_" + _reaction[i] + ".txt";
        params.set<std::vector<SubdomainName>>("block") =
            getParam<std::vector<SubdomainName>>("block");
        _problem->addMaterial("EEDFRateConstantTownsend",
                              "reaction_" + std::to_string(i) + std::to_string(i) + "_" +
                                  getParam<std::vector<SubdomainName>>("block")[0],
                              params);
      }
      else if (_rate_type[i] == "EEDF" && _coefficient_format == "rate")
      // else if (_rate_type[i] )
      {
        Real position_units = getParam<Real>("position_units");
        InputParameters params = _factory.getValidParams("ZapdosEEDFRateConstant");
        params.set<std::string>("reaction") = _reaction[i];
        params.set<std::string>("file_location") = getParam<std::string>("file_location");
        params.set<Real>("position_units") = position_units;
        params.set<std::string>("sampling_format") = _sampling_variable;
        params.set<FileName>("property_file") = "reaction_" + _reaction[i] + ".txt";
        params.set<std::vector<VariableName>>("em") = {_reactants[i][_electron_index[i]]};
        params.set<std::vector<VariableName>>("mean_en") = {_electron_energy[0]};
        params.set<bool>("elastic_collision") = _elastic_collision[i];
        params.set<std::vector<SubdomainName>>("block") =
            getParam<std::vector<SubdomainName>>("block");
        _problem->addMaterial(
            "ZapdosEEDFRateConstant", "reaction_" + std::to_string(i) + std::to_string(i), params);
      }
      else if (_rate_type[i] == "Constant")
      {
        InputParameters params = _factory.getValidParams("GenericRateConstant");
        params.set<std::string>("reaction") = _reaction[i];
        params.set<Real>("reaction_rate_value") = _rate_coefficient[i];
        params.set<std::vector<SubdomainName>>("block") =
            getParam<std::vector<SubdomainName>>("block");
        _problem->addMaterial(
            "GenericRateConstant", "reaction_" + std::to_string(i) + std::to_string(i), params);
      }
      else if (_rate_type[i] == "Equation")
      {
        // For equations, we need to use DerivativeParsedMaterial
        // This will allow the derivative of the coefficient to be taken w.r.t
        // nonlinear variables, which will contribute to the Jacobian.
        InputParameters params = _factory.getValidParams("DerivativeParsedMaterial");
        // params.set<std::string>("f_name") = _reaction_coefficient_name[i];
        params.set<std::string>("f_name") = "k_" + _reaction[i];
        params.set<std::vector<VariableName>>("args") =
            getParam<std::vector<VariableName>>("equation_variables");
        params.set<std::vector<std::string>>("constant_names") =
            getParam<std::vector<std::string>>("equation_constants");
        params.set<std::vector<std::string>>("constant_expressions") =
            getParam<std::vector<std::string>>("equation_values");
        params.set<std::string>("function") = _rate_equation_string[i];
        params.set<unsigned int>("derivative_order") = 2;
        params.set<std::vector<SubdomainName>>("block") =
            getParam<std::vector<SubdomainName>>("block");
        _problem->addMaterial("DerivativeParsedMaterial",
                              "reaction_" + std::to_string(i) + std::to_string(i),
                              params);
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
        params.set<std::vector<SubdomainName>>("block") =
            getParam<std::vector<SubdomainName>>("block");
        _problem->addMaterial("SuperelasticReactionRate",
                              "reaction_" + std::to_string(i) + std::to_string(i),
                              params);
      }
      // Now we check for reactions that include a change of energy.
      // Will this require  its own material?
      // if (_energy_change[i] == true)
      // {
      // Gas temperature is almost in place, but not finished yet.
      // std::cout << "WARNING: energy dependence is not yet implemented." << std::endl;
      // }
    }
  }

  // Add appropriate kernels to each reactant and product.
  if (_current_task == "add_kernel")
  {
    int non_electron_index;
    int index; // stores index of species in the reactant/product arrays
    std::vector<std::string>::iterator iter;
    std::vector<std::string>::iterator iter_aux;
    for (unsigned int i = 0; i < _num_reactions; ++i)
    {
      energy_kernel_name = "ElectronEnergyTerm";
      if (_elastic_collision[i])
        energy_kernel_name += "Elastic";
      // if (!isnan(_rate_coefficient[i]) || _rate_equation[i] == true || _superelastic_reaction[i]
      // == true || getParam<bool>("track_electron_energy") == false)
      if (_coefficient_format == "townsend" && _rate_type[i] == "EEDF")
      {
        energy_kernel_name += "Townsend";
        product_kernel_name = "ElectronImpactReactionProduct";
        reactant_kernel_name = "ElectronImpactReactionReactant";
        // if (getParam<bool>("track_electron_energy") == true)
        // {
        //   if (_coefficient_format == "townsend")
        //   {
        //     product_kernel_name = "ElectronImpactReactionProduct";
        //     reactant_kernel_name = "ElectronImpactReactionReactant";
        //   }
        // }
      }
      // else if (_coefficient_format == "rate")
      else
      {
        energy_kernel_name += "Rate";
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
      // std::cout << energy_kernel_name << ", " << _energy_change[i] << std::endl;

      // if (_energy_change[i] && _rate_type[i] == "EEDF")
      // {
      if (_energy_change[i])
      {
        Real energy_sign;
        for (unsigned int t = 0; t < _energy_variable.size(); ++t)
        {
          if (_electron_energy_term[t])
            energy_sign = 1.0;
          else
            energy_sign = -1.0;

          if (_rate_type[i] == "EEDF")
          {
            for (unsigned int k = 0; k < _reactants[i].size(); ++k)
            {
              if (_reactants[i][k] == "em")
                continue;
              else
                non_electron_index = k;
            }
            // Check if value is tracked, and if so, add as coupled variable.
            find_other =
                std::find(_species.begin(), _species.end(), _reactants[i][non_electron_index]) !=
                _species.end();
            find_aux = std::find(_aux_species.begin(),
                                 _aux_species.end(),
                                 _reactants[i][non_electron_index]) != _aux_species.end();
            if (_elastic_collision[i])
            {
              // First we find the correct target species to add (need species mass for elastic
              // energy change calculation)
              InputParameters params = _factory.getValidParams(energy_kernel_name);
              // params.set<NonlinearVariableName>("variable") = _electron_energy[0];
              params.set<NonlinearVariableName>("variable") = _energy_variable[t];
              params.set<std::string>("reaction") = _reaction[i];
              if (_coefficient_format == "townsend")
                params.set<std::vector<VariableName>>("potential") =
                    getParam<std::vector<VariableName>>("potential");
              params.set<std::vector<VariableName>>("electron_species") = {
                  getParam<std::string>("electron_density")};
              if (find_other || find_aux)
                params.set<std::vector<VariableName>>("target_species") = {
                    _reactants[i][non_electron_index]};
              params.set<Real>("position_units") = _r_units;
              params.set<std::vector<SubdomainName>>("block") =
                  getParam<std::vector<SubdomainName>>("block");
              _problem->addKernel(energy_kernel_name,
                                  "elastic_kernel" + std::to_string(i) + "_" + _reaction[i],
                                  params);
            }
            else
            {
              InputParameters params = _factory.getValidParams(energy_kernel_name);
              // if (find_other || find_aux)
              //  params.set<std::vector<VariableName>>("v") = {_reactants[i][non_electron_index]};
              params.set<NonlinearVariableName>("variable") = _electron_energy[0];
              params.set<std::vector<VariableName>>("em") = {"em"};
              if (_coefficient_format == "townsend")
              {
                params.set<std::vector<VariableName>>("potential") =
                    getParam<std::vector<VariableName>>("potential");
              }
              else
              {
                // If rate format, the target species is needed.
                if (find_other || find_aux)
                  params.set<std::vector<VariableName>>("v") = {_reactants[i][non_electron_index]};
              }
              // params.set<std::vector<VariableName>>("v") = {"Ar"};
              params.set<std::string>("reaction") = _reaction[i];
              params.set<Real>("threshold_energy") = energy_sign * _threshold_energy[i];
              params.set<Real>("position_units") = _r_units;
              params.set<std::vector<SubdomainName>>("block") =
                  getParam<std::vector<SubdomainName>>("block");
              _problem->addKernel(energy_kernel_name,
                                  "energy_kernel" + std::to_string(i) + "_" + _reaction[i],
                                  params);
            }
          }
          else if (_rate_type[i] != "EEDF")
          {
            // find_other = std::find(_species.begin(), _species.end(), _reactants[i][v_index]) !=
            // _species.end(); Coupled variable must be generalized to allow for 3 reactants
            InputParameters params = _factory.getValidParams(energy_kernel_name);
            params.set<NonlinearVariableName>("variable") = _electron_energy[0];
            params.set<std::vector<VariableName>>("em") = {"em"};
            // Find the non-electron reactant
            for (unsigned int k = 0; k < _reactants[i].size(); ++k)
            {
              if (_reactants[i][k] == "em")
                continue;
              else
                non_electron_index = k;
            }
            // Check if value is tracked, and if so, add as coupled variable.
            find_other =
                std::find(_species.begin(), _species.end(), _reactants[i][non_electron_index]) !=
                _species.end();
            find_aux = std::find(_aux_species.begin(),
                                 _aux_species.end(),
                                 _reactants[i][non_electron_index]) != _aux_species.end();
            if (find_other || find_aux)
              params.set<std::vector<VariableName>>("v") = {_reactants[i][non_electron_index]};

            // params.set<std::vector<VariableName>>("v") = {"Ar*"};
            params.set<std::string>("reaction") = _reaction[i];
            params.set<Real>("threshold_energy") = energy_sign * _threshold_energy[i];
            params.set<Real>("position_units") = _r_units;
            params.set<std::vector<SubdomainName>>("block") =
                getParam<std::vector<SubdomainName>>("block");
            _problem->addKernel(energy_kernel_name,
                                "energy_kernel" + std::to_string(i) + "_" + _reaction[i],
                                params);
          }
        }
      }

      for (MooseIndex(_species) j = 0; j < _species.size(); ++j)
      {
        iter = std::find(_reactants[i].begin(), _reactants[i].end(), _species[j]);
        index = std::distance(_reactants[i].begin(), iter);

        // Here we check to see if the current species is an auxiliary variable.
        // If it is, no kernels are added and we skip to the next species.
        iter_aux = std::find(_aux_species.begin(), _aux_species.end(), _species[j]);
        if (iter_aux != _aux_species.end())
          continue;

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
          reactant_species.resize(reactant_indices.size());
          for (unsigned int k = 0; k < reactant_indices.size(); ++k)
          {
            find_other =
                std::find(_species.begin(), _species.end(), _reactants[i][reactant_indices[k]]) !=
                _species.end();
            find_aux = std::find(_aux_species.begin(),
                                 _aux_species.end(),
                                 _reactants[i][reactant_indices[k]]) != _aux_species.end();
            if (find_other)
              continue;
            else
              reactant_indices.erase(reactant_indices.begin() + k);
          }
          v_index = std::abs(index - 1);
          find_other =
              std::find(_species.begin(), _species.end(), _reactants[i][v_index]) != _species.end();
          find_aux = std::find(_aux_species.begin(), _aux_species.end(), _reactants[i][v_index]) !=
                     _aux_species.end();
          if (_species_count[i][j] < 0)
          {
            if (_coefficient_format == "townsend" && _rate_type[i] == "EEDF")
            {
              InputParameters params = _factory.getValidParams(reactant_kernel_name);
              // params.set<NonlinearVariableName>("variable") = _reactants[i][index];
              params.set<NonlinearVariableName>("variable") = _species[j];
              params.set<std::vector<VariableName>>("mean_en") = {_electron_energy[0]};
              params.set<std::vector<VariableName>>("potential") =
                  getParam<std::vector<VariableName>>("potential");
              params.set<std::vector<VariableName>>("em") = {
                  getParam<std::string>("electron_density")};
              params.set<Real>("position_units") = _r_units;
              params.set<std::string>("reaction") = _reaction[i];
              params.set<std::string>("reaction_coefficient_name") = _reaction_coefficient_name[i];
              params.set<std::vector<SubdomainName>>("block") =
                  getParam<std::vector<SubdomainName>>("block");
              _problem->addKernel(
                  reactant_kernel_name, "kernel" + std::to_string(j) + "_" + _reaction[i], params);
            }
            // else if (_coefficient_format == "rate" || _rate_type[i] != "EEDF")
            else if (_coefficient_format == "rate" && _rate_type[i] == "EEDF")
            {
              InputParameters params = _factory.getValidParams("Electron" + reactant_kernel_name);
              params.set<NonlinearVariableName>("variable") = _species[j];
              params.set<Real>("coefficient") = _species_count[i][j];
              params.set<std::string>("reaction") = _reaction[i];
              params.set<std::vector<VariableName>>("energy") = {_electron_energy[0]};
              if (find_other && !find_aux)
              {
                for (unsigned int k = 0; k < reactant_indices.size(); ++k)
                {
                  params.set<std::vector<VariableName>>(other_variables[k]) = {
                      _reactants[i][reactant_indices[k]]};
                  // If the current species does not equal the electron density, then BY DEFINITION
                  // the other species must be the electron density.
                  if (_species[j] != getParam<std::string>("electron_density"))
                    params.set<bool>("_" + other_variables[k] + "_eq_electron") = true;
                }
              }
              params.set<std::vector<SubdomainName>>("block") =
                  getParam<std::vector<SubdomainName>>("block");
              _problem->addKernel("Electron" + reactant_kernel_name,
                                  "kernel" + std::to_string(j) + "_" + _reaction[i],
                                  params);
            }
            else
            {
              InputParameters params = _factory.getValidParams(reactant_kernel_name);
              params.set<NonlinearVariableName>("variable") = _species[j];
              params.set<Real>("coefficient") = _species_count[i][j];
              // std::cout << getParam<std::vector<SubdomainName>>("block")[0] << ", " <<
              // _species_count[i][j] << std::endl; mooseError("TESTING");
              params.set<std::string>("reaction") = _reaction[i];
              if (find_other || find_aux)
              {
                for (unsigned int k = 0; k < reactant_indices.size(); ++k)
                {
                  params.set<std::vector<VariableName>>(other_variables[k]) = {
                      _reactants[i][reactant_indices[k]]};
                  if (_species[j] == _reactants[i][reactant_indices[k]])
                    params.set<bool>("_" + other_variables[k] + "_eq_u") = true;
                }
                // params.set<std::vector<VariableName>>("v") = {_reactants[i][v_index]};
              }
              params.set<std::vector<SubdomainName>>("block") =
                  getParam<std::vector<SubdomainName>>("block");
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
          // if (std::find(_aux_species.begin(), _aux_species.end(), _reactants[i][k]) !=
          // _aux_species.end()) include_species[k] = false;
          if (include_species[k] == false)
            include_species[k] =
                std::find(_aux_species.begin(), _aux_species.end(), _reactants[i][k]) !=
                _aux_species.end();
        }
        if (iter != _products[i].end())
        {

          if (_species_count[i][j] > 0)
          {
            if (_coefficient_format == "townsend" && _rate_type[i] == "EEDF")
            {
              /*AddGeneralReactions::addEEDFReactionKernel(VariableName potential, std::string n_e,
               * unsigned int var_num, unsigned int rxn_num, std::string kernel_name)*/

              addEEDFReactionKernel(getParam<std::vector<VariableName>>("potential"),
                                    getParam<std::string>("electron_density"),
                                    j,
                                    i,
                                    product_kernel_name,
                                    getParam<std::vector<SubdomainName>>("block"));
              /*InputParameters params = _factory.getValidParams(product_kernel_name);*/
              /*params.set<NonlinearVariableName>("variable") = _species[j];*/
              /*params.set<std::vector<VariableName>>("mean_en") = {_electron_energy[0]};*/
              /*if (_coefficient_format == "townsend")*/
                /*params.set<std::vector<VariableName>>("potential") =*/
                    /*getParam<std::vector<VariableName>>("potential");*/
              /*params.set<std::vector<VariableName>>("em") = {*/
                  /*getParam<std::string>("electron_density")};*/
              /*params.set<Real>("position_units") = _r_units;*/
              /*params.set<std::string>("reaction") = _reaction[i];*/
              /*params.set<std::string>("reaction_coefficient_name") = _reaction_coefficient_name[i];*/
              /*params.set<std::vector<SubdomainName>>("block") =*/
                  /*getParam<std::vector<SubdomainName>>("block");*/
              /*_problem->addKernel(product_kernel_name,*/
                                  /*"kernel_prod" + std::to_string(j) + "_" + _reaction[i],*/
                                  /*params);*/
            }
            // else if (_coefficient_format == "rate")
            else if (_coefficient_format == "rate" && _rate_type[i] == "EEDF")
            {
              InputParameters params = _factory.getValidParams("Electron" + product_kernel_name);
              params.set<NonlinearVariableName>("variable") = _species[j];
              params.set<std::string>("reaction") = _reaction[i];
              params.set<Real>("coefficient") = _species_count[i][j];
              params.set<std::vector<VariableName>>("energy") =
                  getParam<std::vector<VariableName>>("electron_energy");
              for (unsigned int k = 0; k < _reactants[i].size(); ++k)
              {
                if (_reactants[i][k] == getParam<std::string>("electron_density"))
                {
                  params.set<std::vector<VariableName>>("electron") = {_electron_energy[0]};
                  if (_species[j] == _reactants[i][k])
                    params.set<bool>("_electron_eq_u") = true;
                }
                else if (include_species[k])
                {
                  params.set<std::vector<VariableName>>("target") = {_reactants[i][k]};
                  // This next if statement should never be satisfied...
                  if (_species[j] == _reactants[i][k])
                    params.set<bool>("_target_eq_u") = true;
                }
              }
              params.set<std::vector<SubdomainName>>("block") =
                  getParam<std::vector<SubdomainName>>("block");
              _problem->addKernel("Electron" + product_kernel_name,
                                  "kernel_prod" + std::to_string(j) + "_" + _reaction[i],
                                  params);
            }
            else
            {
              InputParameters params = _factory.getValidParams(product_kernel_name);
              params.set<NonlinearVariableName>("variable") = _species[j];
              params.set<std::string>("reaction") = _reaction[i];
              // This loop includes reactants as long as they are tracked species.
              // If a species is not tracked, it is treated as a background gas.
              for (unsigned int k = 0; k < _reactants[i].size(); ++k)
              {
                // std::cout << _reaction[i] << ": \n" << "  " << _reactants[i][k] << ", " <<
                // include_species[k] << std::endl;
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
              params.set<std::vector<SubdomainName>>("block") =
                  getParam<std::vector<SubdomainName>>("block");
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

/* Adds reaction kernels (product for now, soon to be both reactants and products) */
void
AddGeneralReactions::addEEDFReactionKernel(std::vector<VariableName> potential,
                                           std::string n_e,
                                           unsigned int var_num,
                                           unsigned int rxn_num,
                                           std::string kernel_name,
                                           std::vector<SubdomainName> block)
{
  InputParameters params = _factory.getValidParams(kernel_name);
  params.set<NonlinearVariableName>("variable") = _species[var_num];
  params.set<std::vector<VariableName>>("mean_en") = {_electron_energy[0]};
  params.set<std::vector<VariableName>>("potential") = potential;
  params.set<std::vector<VariableName>>("em") = {n_e};
  params.set<Real>("position_units") = _r_units;
  params.set<std::string>("reaction") = _reaction[rxn_num];
  params.set<std::string>("reaction_coefficient_name") = _reaction_coefficient_name[rxn_num];
  params.set<std::vector<SubdomainName>>("block") = block;
  _problem->addKernel(kernel_name, "kernel_prod" + std::to_string(var_num) + "_" + _reaction[rxn_num], params);
}

/* Adds reaction coefficient materials (one per reaction) */
/*
void
//AddGeneralReactions::addReactionCoefficient(const std::string & var_name)
AddGeneralReactions::addReactionCoefficient(const std::string & var_name)
{
  mooseError("It works!");
}
*/

