#include "AddScalarReactions.h"
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

registerMooseAction("CraneApp", AddScalarReactions, "add_aux_variable");
registerMooseAction("CraneApp", AddScalarReactions, "add_aux_scalar_kernel");
registerMooseAction("CraneApp", AddScalarReactions, "add_scalar_kernel");
registerMooseAction("CraneApp", AddScalarReactions, "add_function");
registerMooseAction("CraneApp", AddScalarReactions, "add_user_object");

template <>
InputParameters
validParams<AddScalarReactions>()
{
  MooseEnum families(AddVariableAction::getNonlinearVariableFamilies());
  MooseEnum orders(AddVariableAction::getNonlinearVariableOrders());

  InputParameters params = validParams<ChemicalReactionsBase>();
  params.addParam<std::vector<std::string>>(
      "aux_species", "Auxiliary species that are not included in nonlinear solve.");
  params.addParam<std::string>("boltzmann_input_file",
                               "The name of the input file being used for Bolsig+.");
  params.addParam<bool>("output_table",
                        false,
                        "Whether or not to use an output table used for Bolsig+. If false, Bolsig+ "
                        "should be run every timestep.");
  params.addParam<std::string>("cross_section_data",
                               "The file name of the cross section data used for Bolsig+.");
  params.addParam<std::vector<VariableName>>(
      "reduced_field", "The name of the reduced_field variable. (Required for running Bolsig+.)");
  params.addParam<std::vector<VariableName>>(
      "neutral_density",
      "The name of the total neutral density AuxVariable. (Required for running Bolsig+.)");
  params.addParam<std::vector<VariableName>>(
      "ionization_fraction",
      "The name of the ionization fraction AuxVariable. (Not required for running Bolsig+, but may "
      "affect results negatively if not included.)");
  params.addParam<std::vector<VariableName>>(
      "mole_fractions", "The name of the mole fractions of the target species for Bolsig+.");
  params.addParam<std::string>(
      "table_variable", "The variable being used to tabulate rate and transport coefficients.");
  params.addParam<int>("run_every",
                       1,
                       "How many timesteps should pass before rerunning Bolsig+. (If "
                       "output_table=false, this should be left to 1 so it runs every timestep.)");
  params.addParam<Real>(
      "cutoff_time",
      -1,
      "After this simulation time has been reached, Bolsig+ will no longer be run.");
  params.addParam<Real>("conversion_factor",
                        1,
                        "Convert the results by this multiplication factor. Bolsig+ calculates "
                        "everything in SI units (m, m^2, m^3, etc.).");
  params.addClassDescription(
      "This Action automatically adds the necessary kernels and materials for a reaction network.");
  return params;
}

AddScalarReactions::AddScalarReactions(InputParameters params)
  : ChemicalReactionsBase(params), _aux_species(getParam<std::vector<std::string>>("aux_species"))
// _use_bolsig(getParam<bool>("use_bolsig"))
{
}

void
AddScalarReactions::act()
{
  // Some quick error checks
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
  bool find_aux;

  std::vector<bool> include_species;
  std::string product_kernel_name;
  std::string reactant_kernel_name;
  std::string energy_kernel_name;
  // std::vector<NonlinearVariableName> variables =
  //     getParam<std::vector<NonlinearVariableName>>("species");

  /*
   * In scalar form, rate constants are added as AuxScalarVariables.
   *
   * If the _track_rates option is set to true, AuxScalarKernels and AuxScalarVariables will be
   * automatically generated to track the reaction rate for each reaction (e.g. k*n1*n2). This may
   * incur significant computational cost to the simulation depending on the number of reactions and
   * number of nodes.
   */
  if (_current_task == "add_aux_variable")
  {
    for (unsigned int i = 0; i < _num_reactions; ++i)
    {
      if (_reaction_lumped[i])
        continue;
      auto params = _factory.getValidParams("MooseVariableScalar");
      //_problem->addAuxScalarVariable(_aux_var_name[i], FIRST);
      _problem->addAuxVariable("MooseVariableScalar", _aux_var_name[i], params);
      if (_track_rates == true)
      {
        //_problem->addAuxScalarVariable("rate" + std::to_string(i), FIRST);
        _problem->addAuxVariable("MooseVariableScalar", "rate" + std::to_string(i), params);
      }
    }
  }

  if (_current_task == "add_user_object")
  {
    if (_use_bolsig)
    {
      // Here we add the UserObject controlling Bolsig+.
      InputParameters params = _factory.getValidParams("BoltzmannSolverScalar");
      params.set<std::string>("boltzmann_input_file") =
          getParam<std::string>("boltzmann_input_file");
      params.set<bool>("output_table") = getParam<bool>("output_table");
      params.set<std::string>("table_variable") = getParam<std::string>("table_variable");
      params.set<ExecFlagEnum>("execute_on") = "INITIAL TIMESTEP_BEGIN";
      params.set<std::vector<VariableName>>("reduced_field") =
          getParam<std::vector<VariableName>>("reduced_field");
      params.set<std::vector<VariableName>>("neutral_density") =
          getParam<std::vector<VariableName>>("neutral_density");
      params.set<std::vector<VariableName>>("ionization_fraction") =
          getParam<std::vector<VariableName>>("ionization_fraction");
      params.set<std::vector<VariableName>>("mole_fractions") =
          getParam<std::vector<VariableName>>("mole_fractions");
      params.set<std::vector<std::string>>("reaction_type") = _reaction_identifier;
      params.set<std::vector<int>>("reaction_number") = {_eedf_reaction_number};
      params.set<int>("number_reactions") = _eedf_reaction_counter;
      params.set<int>("n_steps") = getParam<int>("run_every");
      params.set<Real>("cutoff_time") = getParam<Real>("cutoff_time");
      params.set<Real>("conversion_factor") = getParam<Real>("conversion_factor");
      params.set<std::vector<std::string>>("reaction_species") = _reaction_species;
      params.set<std::string>("cross_section_data") = getParam<std::string>("cross_section_data");
      _problem->addUserObject("BoltzmannSolverScalar", "bolsig", params);
    }

    for (unsigned int i = 0; i < _num_reactions; ++i)
    {
      if (_reaction_lumped[i])
        continue;
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
      if (_reaction_lumped[i])
        continue;
      if (_rate_type[i] == "EEDF" && !_superelastic_reaction[i])
      {
        if (_use_bolsig)
        {
          InputParameters params = _factory.getValidParams("EEDFRateCoefficientScalar");
          params.set<UserObjectName>("rate_provider") = "bolsig";
          params.set<AuxVariableName>("variable") = {_aux_var_name[i]};
          params.set<bool>("sample_value") = true;
          params.set<std::vector<VariableName>>("sample_variable") = {
              getParam<std::string>("sampling_variable")};
          // params.set<int>("reaction_number") = i;
          params.set<int>("reaction_number") = _eedf_reaction_number[i];
          _problem->addAuxScalarKernel(
              "EEDFRateCoefficientScalar", "aux_rate" + std::to_string(i), params);
        }
        else
        {
          InputParameters params = _factory.getValidParams("DataReadScalar");
          params.set<AuxVariableName>("variable") = {_aux_var_name[i]};
          params.set<std::vector<VariableName>>("sampler") = {
              getParam<std::string>("sampling_variable")};
          if (_is_identified[i])
          {
            params.set<FileName>("property_file") = _reaction_identifier[_eedf_reaction_number[i]];
          }
          else
          {
            params.set<FileName>("property_file") = "reaction_" + _reaction[i] + ".txt";
          }
          params.set<std::string>("file_location") = getParam<std::string>("file_location");
          params.set<ExecFlagEnum>("execute_on") = "TIMESTEP_BEGIN";
          _problem->addAuxScalarKernel("DataReadScalar", "aux_rate" + std::to_string(i), params);
        }
      }
      else if (_rate_type[i] == "Equation" && !_superelastic_reaction[i])
      {
        InputParameters params = _factory.getValidParams("ParsedScalarRateCoefficient");
        params.set<AuxVariableName>("variable") = {_aux_var_name[i]};
        params.set<std::string>("function") = _rate_equation_string[i];
        params.set<bool>("file_read") = true;
        // params.set<std::vector<std::string>>("file_value") = {"Te"};
        params.set<std::vector<std::string>>("constant_names") =
            getParam<std::vector<std::string>>("equation_constants");
        params.set<std::vector<std::string>>("constant_expressions") =
            getParam<std::vector<std::string>>("equation_values");
        // params.set<UserObjectName>("electron_temperature") = "value_provider";
        // params.set<std::vector<VariableName>>("reduced_field") = {"reduced_field"};
        // if (getParam<bool>("gas_temperature"))
        // {
        //   params.set<bool>("gas_temperature") = true;
        //   std::vector<NonlinearVariableName> gas_temp =
        //   getParam<std::vector<NonlinearVariableName>>("equation_variables"); std::string
        //   temp_var; for (unsigned int m = 0; m<gas_temp.size(); ++m)
        //   {
        //     if (gas_temp[m] == "Tgas")
        //       temp_var = gas_temp[m];
        //       break;
        //   }
        //   params.set<std::vector<VariableName>>("args") = {temp_var};
        //   // params.set<std::vector<VariableName>>("args") = getParam<std::vector<VariableName>>("equation_variables");
        //
        // }
        // params.set<std::vector<VariableName>>("args") = {"Te"};
        params.set<std::vector<VariableName>>("args") =
            getParam<std::vector<VariableName>>("equation_variables");
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

      /*
       * If the _track_rates option is set to true, AuxKernels and AuxVariables will be
       * automatically generated to track the reaction rate for each reaction (e.g. k*n1*n2). This
       * may incur significant computational cost to the simulation depending on the number of
       * reactions and number of nodes.
       */
      if (_track_rates == true)
      {

        if (_reactants[i].size() == 1)
        {
          InputParameters params = _factory.getValidParams("ReactionRateOneBodyScalar");
          params.set<std::vector<VariableName>>("v") = {(_reactants[i][0])};
          params.set<AuxVariableName>("variable") = {"rate" + std::to_string(i)};
          params.set<std::vector<VariableName>>("rate_coefficient") = {_aux_var_name[i]};
          params.set<Real>("coefficient") = 1; //_reaction_stoichiometric_coeff[i].back();
          params.set<ExecFlagEnum>("execute_on") = "TIMESTEP_BEGIN";
          _problem->addAuxScalarKernel(
              "ReactionRateOneBodyScalar", "Calc_Production_Rate" + std::to_string(i), params);
        }
        else if (_reactants[i].size() == 2)
        {
          InputParameters params = _factory.getValidParams("ReactionRateTwoBodyScalar");
          params.set<std::vector<VariableName>>("v") = {(_reactants[i][0])};
          params.set<std::vector<VariableName>>("w") = {(_reactants[i][1])};
          params.set<AuxVariableName>("variable") = {"rate" + std::to_string(i)};
          params.set<std::vector<VariableName>>("rate_coefficient") = {_aux_var_name[i]};
          params.set<Real>("coefficient") = 1; //_reaction_stoichiometric_coeff[i].back();
          params.set<ExecFlagEnum>("execute_on") = "TIMESTEP_BEGIN";
          _problem->addAuxScalarKernel(
              "ReactionRateTwoBodyScalar", "Calc_Production_Rate" + std::to_string(i), params);
        }

        else if (_reactants[i].size() == 3)
        {
          InputParameters params = _factory.getValidParams("ReactionRateThreeBodyScalar");
          params.set<std::vector<VariableName>>("v") = {(_reactants[i][0])};
          params.set<std::vector<VariableName>>("w") = {(_reactants[i][1])};
          params.set<std::vector<VariableName>>("z") = {(_reactants[i][2])};
          params.set<AuxVariableName>("variable") = {"rate" + std::to_string(i)};
          params.set<std::vector<VariableName>>("rate_coefficient") = {_aux_var_name[i]};
          params.set<Real>("coefficient") = 1; //_reaction_stoichiometric_coeff[i].back();
          params.set<ExecFlagEnum>("execute_on") = "TIMESTEP_BEGIN";
          _problem->addAuxScalarKernel(
              "ReactionRateThreeBodyScalar", "Calc_Production_Rate" + std::to_string(i), params);
        }
      }
    }
  }

  if (_current_task == "add_scalar_kernel")
  {
    int index; // stores index of species in the reactant/product arrays
    std::vector<std::string>::iterator iter;
    std::vector<std::string>::iterator iter_aux;
    std::vector<Real> rxn_coeff = getParam<std::vector<Real>>("reaction_coefficient");
    for (unsigned int i = 0; i < _num_reactions; ++i)
    {
      if (_reaction_lumped[i])
        continue;
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
      if (_use_log)
      {
        product_kernel_name += "Log";
        reactant_kernel_name += "Log";
      }

      // if (_energy_change[i] && _rate_type[i] != "EEDF")
      // {
      if (_energy_change[i])
      {
        Real energy_sign;
        for (unsigned int t = 0; t < _energy_variable.size(); ++t)
        {
          if (_rate_type[i] != "EEDF")
          {
            if (_electron_energy_term[t])
              energy_sign = 1.0;
            else
              energy_sign = -1.0;

            int non_electron_index;
            // find_other = std::find(_species.begin(), _species.end(), _reactants[i][v_index]) !=
            // _species.end(); Coupled variable must be generalized to allow for 3 reactants
            InputParameters params = _factory.getValidParams(energy_kernel_name);
            // params.set<NonlinearVariableName>("variable") = _electron_energy[0];
            params.set<NonlinearVariableName>("variable") = _energy_variable[t];
            // params.set<std::vector<VariableName>>("em") = {"em"};
            params.set<std::vector<VariableName>>("em") = {
                getParam<std::string>("electron_density")};
            // Find the non-electron reactant
            for (unsigned int k = 0; k < _reactants[i].size(); ++k)
            {
              if (_reactants[i][k] == getParam<std::string>("electron_density"))
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

        // Find any aux variables in the species list.
        // If found, this index is skipped.
        iter_aux = std::find(_aux_species.begin(), _aux_species.end(), _species[j]);

        if (iter_aux != _aux_species.end())
        {
          continue;
        }
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
            if (!find_other)
              find_other = std::find(_aux_species.begin(),
                                     _aux_species.end(),
                                     _reactants[i][reactant_indices[k]]) != _aux_species.end();
            if (find_other)
              continue;
            else
              reactant_indices.erase(reactant_indices.begin() + k);
            /*
            find_other =
                std::find(_species.begin(), _species.end(), _reactants[i][reactant_indices[k]]) !=
                _species.end();
            if (find_other)
              continue;
            else
              reactant_indices.erase(reactant_indices.begin() + k);
            */
          }
          v_index = std::abs(index - 1);
          // find_other =
          //    std::find(_species.begin(), _species.end(), _reactants[i][v_index]) !=
          //    _species.end();
          if (_species_count[i][j] < 0)
          {
            InputParameters params = _factory.getValidParams(reactant_kernel_name);
            params.set<NonlinearVariableName>("variable") = _species[j];
            params.set<Real>("coefficient") = _species_count[i][j];
            params.set<std::vector<VariableName>>("rate_coefficient") = {_aux_var_name[i]};
            params.set<bool>("rate_constant_equation") = true;
            if (find_other)
            {
              for (unsigned int k = 0; k < reactant_indices.size(); ++k)
                params.set<std::vector<VariableName>>(other_variables[k]) = {
                    _reactants[i][reactant_indices[k]]};
            }
            _problem->addScalarKernel(reactant_kernel_name,
                                      "kernel" + std::to_string(i) + "_" + std::to_string(j) + "_" +
                                          _reaction[i],
                                      params);
          }
        }

        iter = std::find(_products[i].begin(), _products[i].end(), _species[j]);
        include_species.resize(_reactants[i].size());
        for (unsigned int k = 0; k < _reactants[i].size(); ++k)
        {
          include_species[k] =
              std::find(_species.begin(), _species.end(), _reactants[i][k]) != _species.end();
          if (include_species[k] == false)
            include_species[k] =
                std::find(_aux_species.begin(), _aux_species.end(), _reactants[i][k]) !=
                _aux_species.end();
        }
        if (iter != _products[i].end())
        {

          if (_species_count[i][j] > 0)
          {
            InputParameters params = _factory.getValidParams(product_kernel_name);
            params.set<NonlinearVariableName>("variable") = _species[j];
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
                                      "kernel_prod" + std::to_string(i) + "_" + std::to_string(j) +
                                          "_" + _reaction[i],
                                      params);
          }
        }
      }
    }
  }
}
