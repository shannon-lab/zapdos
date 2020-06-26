//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "AddDriftDiffusionAction.h"
#include "Parser.h"
#include "FEProblem.h"
#include "Factory.h"
#include "MooseEnum.h"
#include "AddVariableAction.h"
#include "Conversion.h"
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

registerMooseAction("ZapdosApp", AddDriftDiffusionAction, "add_variable");
registerMooseAction("ZapdosApp", AddDriftDiffusionAction, "add_kernel");
registerMooseAction("ZapdosApp", AddDriftDiffusionAction, "add_aux_kernel");

template <>
InputParameters
validParams<AddDriftDiffusionAction>()
{
  MooseEnum families(AddVariableAction::getNonlinearVariableFamilies());
  MooseEnum orders(AddVariableAction::getNonlinearVariableOrders());

  InputParameters params = validParams<AddVariableAction>();

  params.addParam<std::vector<NonlinearVariableName>>(
      "charged_particle", "User given variable name for energy independent charged particle");
  params.addParam<std::vector<NonlinearVariableName>>(
      "secondary_charged_particles",
      "These are charged particles whose advection term in determined by"
      " an effective potential.");
  params.addParam<std::vector<NonlinearVariableName>>(
      "eff_potentials",
      "The effective potentials that only affect their respective secondary"
      " charged particle.");
  params.addParam<NonlinearVariableName>("electrons",
                                         "User given variable name for energy dependent electrons");
  params.addParam<std::vector<NonlinearVariableName>>("reference_residual",
                                                      "The reference residual.");
  // params.addParam<std::vector<TagName>>("extra_tags", "The extra tags.");
  params.addParam<NonlinearVariableName>("potential", "The gives the potential a variable name");
  params.addParam<bool>("use_ad", false, "Whether or not to use automatic differentiation.");
  params.addParam<bool>(
      "Is_potential_unique",
      false,
      "Is this potential unique to this block?"
      "If not, then the potential variable should be defined in the Variable Block.");
  params.addParam<bool>("First_DriftDiffusionAction_in_block",
                        true,
                        "Is this the first DriftDiffusionAction for this block?"
                        "If not, then the potential diffusion kernel and Position auxkernel will "
                        "NOT be supplied by this action.");
  params.addParam<NonlinearVariableName>("mean_energy",
                                         "The gives the mean energy a variable name");
  params.addParam<std::vector<NonlinearVariableName>>(
      "Neutrals", "The names of the neutrals that should be added");
  params.addParam<std::vector<SubdomainName>>("block",
                                              "The subdomain that this action applies to.");
  params.addRequiredParam<Real>("position_units", "Units of position");
  params.addParam<bool>("using_offset", false, "Is the LogStabilizationMoles Kernel being used");
  params.addParam<Real>(
      "offset", 20.0, "The offset parameter that goes into the exponential function");
  params.addRequiredParam<std::string>("potential_units", "Units of potential");
  params.addRequiredParam<bool>("use_moles", "Whether to convert from units of moles to #.");
  params.addParam<std::vector<std::string>>(
      "Additional_Outputs",
      "Current list of available ouputs options in this action: Current, ElectronTemperature,"
      " EField");
  return params;
}

AddDriftDiffusionAction::AddDriftDiffusionAction(InputParameters params)
  : Action(params), _use_ad(getParam<bool>("use_ad"))
{
  if (_use_ad)
    _ad_prepend = "AD";
  else
    _ad_prepend = "";
}

void
AddDriftDiffusionAction::act()
{
  MooseSharedPointer<Action> action;
  MooseSharedPointer<MooseObjectAction> moose_object_action;

  //
  unsigned int _dim = _mesh->dimension();

  // Converting the given names into VariableName
  NonlinearVariableName em_name;
  NonlinearVariableName mean_en_name;
  NonlinearVariableName potential_name;

  bool em_present = (isParamValid("electrons") ? true : false);
  bool mean_en_present = (isParamValid("mean_energy") ? true : false);
  bool potential_present = (isParamValid("potential") ? true : false);
  if (em_present)
    em_name = getParam<NonlinearVariableName>("electrons");
  if (mean_en_present)
    mean_en_name = getParam<NonlinearVariableName>("mean_energy");
  if (potential_present)
    potential_name = getParam<NonlinearVariableName>("potential");

  std::vector<NonlinearVariableName> Ions =
      getParam<std::vector<NonlinearVariableName>>("charged_particle");
  std::vector<NonlinearVariableName> Neutrals =
      getParam<std::vector<NonlinearVariableName>>("Neutrals");

  unsigned int number_ions = Ions.size();
  unsigned int number_neutrals = Neutrals.size();

  if (!potential_present && (em_present || (number_ions > 0)))
    mooseError("There are electrons or charged_particles that are missing their potential! Please "
               "check your input.");

  std::vector<NonlinearVariableName> sec_particle =
      getParam<std::vector<NonlinearVariableName>>("secondary_charged_particles");
  std::vector<NonlinearVariableName> eff_potentials =
      getParam<std::vector<NonlinearVariableName>>("eff_potentials");

  unsigned int number_sec_particle = sec_particle.size();
  unsigned int number_eff_potentials = eff_potentials.size();

  if (number_sec_particle != number_eff_potentials)
    mooseError("There are secondary_charged_particles that are missing their corresponding "
               "effective potential (eff_potentials)! Please check your input.");

  // Converting the given additional outputs
  std::vector<std::string> Outputs = getParam<std::vector<std::string>>("Additional_Outputs");

  unsigned int number_outputs = Outputs.size();

  // Converting the boolean statements
  bool Using_offset = getParam<bool>("using_offset");
  bool New_potential = getParam<bool>("Is_potential_unique");
  bool First_Action = getParam<bool>("First_DriftDiffusionAction_in_block");

  // The variable type for the nonlinear variables
  auto fe_type = AddVariableAction::feType(_pars);
  auto type = AddVariableAction::determineType(fe_type, 1);
  auto var_params = _factory.getValidParams(type);
  var_params.set<MooseEnum>("order") = "FIRST";
  var_params.set<MooseEnum>("family") = "LAGRANGE";
  var_params.set<std::vector<SubdomainName>>("block") =
      getParam<std::vector<SubdomainName>>("block");

  // The variable type for the aux variables
  auto aux_params = _factory.getValidParams(type);
  aux_params.set<MooseEnum>("order") = "CONSTANT";
  aux_params.set<MooseEnum>("family") = "MONOMIAL";
  aux_params.set<std::vector<SubdomainName>>("block") =
      getParam<std::vector<SubdomainName>>("block");

  if (_current_task == "add_variable")
  {
    // Add the ion variables and their density aux variables
    for (unsigned int cur_num = 0; cur_num < number_ions; cur_num++)
    {
      std::string ion_name = Ions[cur_num];
      _problem->addVariable(type, ion_name, var_params);
      _problem->addAuxVariable(type, ion_name + "_density", aux_params);
    }

    // Add the neutrals variables and their density aux variables
    for (unsigned int cur_num = 0; cur_num < number_neutrals; cur_num++)
    {
      std::string neutrals_name = Neutrals[cur_num];
      _problem->addVariable(type, neutrals_name, var_params);
      _problem->addAuxVariable(type, neutrals_name + "_density", aux_params);
    }

    // Adding electrons, mean energy, and potential variables
    if (em_present)
    {
      _problem->addVariable(type, em_name, var_params);
      _problem->addAuxVariable(type, em_name + "_density", aux_params);
    }
    if (mean_en_present)
    {
      _problem->addVariable(type, mean_en_name, var_params);
    }
    if (New_potential && potential_present)
    {
      _problem->addVariable(type, potential_name, var_params);
    }

    // Adding charged particles who are effective by an effective potential
    for (unsigned int cur_num = 0; cur_num < number_sec_particle; cur_num++)
    {
      std::string sec_particle_name = sec_particle[cur_num];
      _problem->addVariable(type, sec_particle_name, var_params);
      _problem->addAuxVariable(type, sec_particle_name + "_density", aux_params);
    }

    // Adding the position aux variable, needed if position scaling is used
    if (First_Action)
    {
      if (_dim == 1)
      {
        _problem->addAuxVariable(
            type,
            "position" + Moose::stringify(getParam<std::vector<SubdomainName>>("block")),
            aux_params);
      }
      else
      {
        for (unsigned int component = 0; component < _dim; ++component)
        {
          std::string dir = "x_";
          if (component == 1)
            dir = "y_";
          if (component == 2)
            dir = "z_";
          _problem->addAuxVariable(
              type,
              dir + "position" + Moose::stringify(getParam<std::vector<SubdomainName>>("block")),
              aux_params);
        }
      }
    }

    // Adding variables needed for the additional outputs
    for (unsigned int cur_num = 0; cur_num < number_outputs; cur_num++)
    {
      std::string output_name = Outputs[cur_num];

      if (output_name == "Current")
      {
        if (em_present)
          _problem->addAuxVariable(type, "Current_" + em_name, aux_params);

        for (unsigned int cur_num = 0; cur_num < number_ions; cur_num++)
        {
          std::string ion_name = Ions[cur_num];
          _problem->addAuxVariable(type, "Current_" + ion_name, aux_params);
        }

        for (unsigned int cur_num = 0; cur_num < number_sec_particle; cur_num++)
        {
          std::string sec_particle_name = sec_particle[cur_num];
          _problem->addAuxVariable(type, "Current_" + sec_particle_name, aux_params);
        }
      }

      else if (output_name == "ElectronTemperature")
      {
        _problem->addAuxVariable(type, "e_temp", aux_params);
      }

      else if (output_name == "EField")
      {
        for (unsigned int component = 0; component < _dim; ++component)
        {
          std::string dir = "x";
          if (component == 1)
            dir = "y";
          if (component == 2)
            dir = "z";

          _problem->addAuxVariable(
              type,
              "EField" + dir + Moose::stringify(getParam<std::vector<SubdomainName>>("block")),
              aux_params);
        }
      }

      else if (output_name != "Current" || output_name != "ElectronTemperature" ||
               output_name != "EField")
      {
        mooseError("Currently this action does not have one of the desired outputs or spelling is "
                   "incorrect."
                   " Please input the AuxKernel manually or check spelling.");
      }
    }
  }

  else if (_current_task == "add_kernel")
  {
    // This section adds all necessary kernels for electrons, ions, neutrals,
    // and electron temperature.
    // Note that the same kernels are added for electrons, temperature, and
    // ions when using automatic differentiation. (Same with neutrals, but
    // with no advection term.)

    // Adding energy dependent electron kernels, if present in block
    if (em_present)
    {
      if (_use_ad)
        addADKernels(em_name, potential_name, Using_offset, true, false);
      else
        addElectronKernels(em_name, potential_name, mean_en_name, Using_offset);
      addChargeSourceKernels(potential_name, em_name);
    }

    // Adding energy electron mean energy kernels, if present in block
    if (mean_en_present)
    {
      if (_use_ad)
        addADKernels(mean_en_name, potential_name, Using_offset, true, true);
      else
        addMeanEnergyKernels(em_name, potential_name, mean_en_name, Using_offset);
    }

    // Adding Kernels for the charged particle
    for (unsigned int cur_num = 0; cur_num < number_ions; cur_num++)
    {
      std::string ion_name = Ions[cur_num];

      if (_use_ad)
        addADKernels(ion_name, potential_name, Using_offset, true, false);
      else
        addChargedParticlesKernels(ion_name, potential_name, Using_offset);
      addChargeSourceKernels(potential_name, ion_name);
    }

    // Adding the diffusion Kernel for the potential
    if (potential_present && First_Action)
    {
      InputParameters params = _factory.getValidParams("CoeffDiffusionLin");
      params.set<NonlinearVariableName>("variable") = {potential_name};
      params.set<Real>("position_units") = getParam<Real>("position_units");
      params.set<std::vector<SubdomainName>>("block") =
          getParam<std::vector<SubdomainName>>("block");
      _problem->addKernel("CoeffDiffusionLin",
                          potential_name + "_diffusion" +
                              Moose::stringify(getParam<std::vector<SubdomainName>>("block")) +
                              "_block",
                          params);
    }

    // Adding Kernels for the neutrals
    for (unsigned int cur_num = 0; cur_num < number_neutrals; cur_num++)
    {
      std::string neutral_name = Neutrals[cur_num];

      if (_use_ad)
        addADKernels(neutral_name, potential_name, Using_offset, false, false);
      else
        addNeutralParticlesKernels(neutral_name, Using_offset);
    }

    // Adding Kernels for charged particles who are effective by an effective potential
    for (unsigned int cur_num = 0; cur_num < number_sec_particle; cur_num++)
    {
      std::string sec_particle_name = sec_particle[cur_num];
      std::string eff_potentials_name = eff_potentials[cur_num];

      addChargedParticlesKernels(sec_particle_name, eff_potentials_name, Using_offset);
      addChargeSourceKernels(potential_name, sec_particle_name);
    }
  }

  else if (_current_task == "add_aux_kernel")
  {
    // AuxKernels for position;
    if (First_Action)
    {
      if (_dim == 1)
      {
        addPosition("position" + Moose::stringify(getParam<std::vector<SubdomainName>>("block")),
                    0);
      }
      else
      {
        for (unsigned int component = 0; component < _dim; ++component)
        {
          std::string dir = "x_";
          if (component == 1)
            dir = "y_";
          if (component == 2)
            dir = "z_";
          addPosition(dir + "position" +
                          Moose::stringify(getParam<std::vector<SubdomainName>>("block")),
                      component);
        }
      }
    }

    // Adding the aux kernels needed to convert the log form of the densities
    if (em_present)
    {
      addDensityLog(em_name);
    }
    for (unsigned int cur_num = 0; cur_num < number_ions; cur_num++)
    {
      std::string ion_name = Ions[cur_num];
      addDensityLog(ion_name);
    }
    for (unsigned int cur_num = 0; cur_num < number_neutrals; cur_num++)
    {
      std::string neutral_name = Neutrals[cur_num];
      addDensityLog(neutral_name);
      ;
    }
    for (unsigned int cur_num = 0; cur_num < number_sec_particle; cur_num++)
    {
      std::string sec_particle_name = sec_particle[cur_num];
      addDensityLog(sec_particle_name);
    }

    for (unsigned int cur_num = 0; cur_num < number_outputs; cur_num++)
    {
      std::string output_name = Outputs[cur_num];

      // AuxKernels for current
      if (output_name == "Current")
      {
        if (em_present)
        {
          addCurrent(em_name, potential_name);
        }

        for (unsigned int cur_num = 0; cur_num < number_ions; cur_num++)
        {
          std::string ion_name = Ions[cur_num];
          addCurrent(ion_name, potential_name);
        }

        for (unsigned int cur_num = 0; cur_num < number_sec_particle; cur_num++)
        {
          std::string sec_particle_name = sec_particle[cur_num];
          std::string eff_potentials_name = eff_potentials[cur_num];
          addCurrent(sec_particle_name, eff_potentials_name);
        }
      }

      // Adding Efield Aux kernels
      else if (output_name == "EField")
      {
        for (unsigned int component = 0; component < _dim; ++component)
        {
          std::string dir = "x";
          if (component == 1)
            dir = "y";
          if (component == 2)
            dir = "z";

          addEfield("EField" + dir +
                        Moose::stringify(getParam<std::vector<SubdomainName>>("block")),
                    potential_name,
                    component);
        }
      }

      // Adding Electron Temperature Aux kernels
      else if (output_name == "ElectronTemperature")
      {
        InputParameters params = _factory.getValidParams("ElectronTemperature");
        params.set<AuxVariableName>("variable") = "e_temp";
        params.set<std::vector<VariableName>>("electron_density") = {em_name};
        params.set<std::vector<VariableName>>("mean_en") = {mean_en_name};
        params.set<std::vector<SubdomainName>>("block") =
            getParam<std::vector<SubdomainName>>("block");
        _problem->addAuxKernel("ElectronTemperature", "e_temp", params);
      }
    }
  }
}

// Adding Kernels for the electrons
void
AddDriftDiffusionAction::addElectronKernels(const std::string & em_name,
                                            const std::string & potential_name,
                                            const std::string & mean_en_name,
                                            const bool & Using_offset)
{
  InputParameters params = _factory.getValidParams("ElectronTimeDerivative");
  params.set<NonlinearVariableName>("variable") = {em_name};
  params.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
  _problem->addKernel("ElectronTimeDerivative", em_name + "_time_deriv", params);

  InputParameters params1 = _factory.getValidParams("EFieldAdvectionElectrons");
  params1.set<NonlinearVariableName>("variable") = {em_name};
  params1.set<std::vector<VariableName>>("potential") = {potential_name};
  params1.set<std::vector<VariableName>>("mean_en") = {mean_en_name};
  params1.set<Real>("position_units") = getParam<Real>("position_units");
  params1.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
  _problem->addKernel("EFieldAdvectionElectrons", em_name + "_advection", params1);

  InputParameters params2 = _factory.getValidParams("CoeffDiffusionElectrons");
  params2.set<NonlinearVariableName>("variable") = {em_name};
  params2.set<std::vector<VariableName>>("mean_en") = {mean_en_name};
  params2.set<Real>("position_units") = getParam<Real>("position_units");
  params2.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
  _problem->addKernel("CoeffDiffusionElectrons", em_name + "_diffusion", params2);

  if (Using_offset)
  {
    InputParameters params3 = _factory.getValidParams("LogStabilizationMoles");
    params3.set<NonlinearVariableName>("variable") = {em_name};
    params3.set<Real>("offset") = getParam<Real>("offset");
    params3.set<std::vector<SubdomainName>>("block") =
        getParam<std::vector<SubdomainName>>("block");
    _problem->addKernel("LogStabilizationMoles", em_name + "_log_stabilization", params3);
  }
}

/*void
AddDriftDiffusionAction::addElectronADKernels(const std::string & em_name,
                                         const std::string & potential_name,
                                         const std::string & mean_en_name,
                                         const bool & Using_offset)
{
}*/

// Adding Kernels for the energy independent charged particles
void
AddDriftDiffusionAction::addChargedParticlesKernels(const std::string & ion_name,
                                                    const std::string & potential_name,
                                                    const bool & Using_offset)
{
  InputParameters params = _factory.getValidParams("ElectronTimeDerivative");
  params.set<NonlinearVariableName>("variable") = ion_name;
  params.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
  _problem->addKernel("ElectronTimeDerivative", ion_name + "_time_deriv", params);

  InputParameters params1 = _factory.getValidParams("EFieldAdvection");
  params1.set<NonlinearVariableName>("variable") = ion_name;
  params1.set<std::vector<VariableName>>("potential") = {potential_name};
  params1.set<Real>("position_units") = getParam<Real>("position_units");
  params1.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
  _problem->addKernel("EFieldAdvection", ion_name + "_advection", params1);

  InputParameters params2 = _factory.getValidParams("CoeffDiffusion");
  params2.set<NonlinearVariableName>("variable") = ion_name;
  params2.set<Real>("position_units") = getParam<Real>("position_units");
  params2.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
  _problem->addKernel("CoeffDiffusion", ion_name + "_diffusion", params2);

  if (Using_offset)
  {
    InputParameters params3 = _factory.getValidParams("LogStabilizationMoles");
    params3.set<NonlinearVariableName>("variable") = ion_name;
    params3.set<Real>("offset") = getParam<Real>("offset");
    params3.set<std::vector<SubdomainName>>("block") =
        getParam<std::vector<SubdomainName>>("block");
    _problem->addKernel("LogStabilizationMoles", ion_name + "_log_stabilization", params3);
  }
}

/*void
AddDriftDiffusionAction::addChargedParticlesADKernels(const std::string & ion_name,
                                                 const std::string & potential_name,
                                                 const bool & Using_offset)
{
}*/

// Adding Kernels for the neutral particles
void
AddDriftDiffusionAction::addNeutralParticlesKernels(const std::string & neutral_name,
                                                    const bool & Using_offset)
{
  InputParameters params = _factory.getValidParams("ElectronTimeDerivative");
  params.set<NonlinearVariableName>("variable") = neutral_name;
  params.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
  _problem->addKernel("ElectronTimeDerivative", neutral_name + "_time_deriv", params);

  InputParameters params1 = _factory.getValidParams("CoeffDiffusion");
  params1.set<NonlinearVariableName>("variable") = neutral_name;
  params1.set<Real>("position_units") = getParam<Real>("position_units");
  params1.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
  _problem->addKernel("CoeffDiffusion", neutral_name + "_diffusion", params1);

  if (Using_offset)
  {
    InputParameters params2 = _factory.getValidParams("LogStabilizationMoles");
    params2.set<NonlinearVariableName>("variable") = neutral_name;
    params2.set<Real>("offset") = (getParam<Real>("offset"));
    params2.set<std::vector<SubdomainName>>("block") =
        getParam<std::vector<SubdomainName>>("block");
    _problem->addKernel("LogStabilizationMoles", neutral_name + "_log_stabilization", params2);
  }
}

/*AddDriftDiffusionAction::addNeutralParticlesADKernels(const std::string & ion_name,
                                                 const std::string & potential_name,
                                                 const bool & Using_offset)
{
}*/

// Adding Kernels for the electron mean energy
void
AddDriftDiffusionAction::addMeanEnergyKernels(const std::string & em_name,
                                              const std::string & potential_name,
                                              const std::string & mean_en_name,
                                              const bool & Using_offset)
{
  InputParameters params = _factory.getValidParams("ElectronTimeDerivative");
  params.set<NonlinearVariableName>("variable") = {mean_en_name};
  params.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
  /*
  params.set<std::vector<TagName>>("extra_vector_tags") =
      getParam<std::vector<TagName>>("extra_tags");
      */
  _problem->addKernel("ElectronTimeDerivative", mean_en_name + "_time_deriv", params);

  InputParameters params1 = _factory.getValidParams("EFieldAdvectionEnergy");
  params1.set<NonlinearVariableName>("variable") = {mean_en_name};
  params1.set<std::vector<VariableName>>("potential") = {potential_name};
  params1.set<std::vector<VariableName>>("em") = {em_name};
  params1.set<Real>("position_units") = getParam<Real>("position_units");
  params1.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
  /*
  params1.set<std::vector<TagName>>("extra_vector_tags") =
      getParam<std::vector<TagName>>("extra_tags");
  */
  _problem->addKernel("EFieldAdvectionEnergy", mean_en_name + "_advection", params1);

  InputParameters params2 = _factory.getValidParams("CoeffDiffusionEnergy");
  params2.set<NonlinearVariableName>("variable") = {mean_en_name};
  params2.set<std::vector<VariableName>>("em") = {em_name};
  params2.set<Real>("position_units") = getParam<Real>("position_units");
  params2.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
  /*
  params2.set<std::vector<TagName>>("extra_vector_tags") =
      getParam<std::vector<TagName>>("extra_tags");
  */
  _problem->addKernel("CoeffDiffusionEnergy", mean_en_name + "_diffusion", params2);

  InputParameters params3 = _factory.getValidParams("JouleHeating");
  params3.set<NonlinearVariableName>("variable") = {mean_en_name};
  params3.set<std::vector<VariableName>>("potential") = {potential_name};
  params3.set<std::vector<VariableName>>("em") = {em_name};
  params3.set<std::string>("potential_units") = getParam<std::string>("potential_units");
  params3.set<Real>("position_units") = getParam<Real>("position_units");
  params3.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
  /*
  params3.set<std::vector<TagName>>("extra_vector_tags") =
      getParam<std::vector<TagName>>("extra_tags");
      */
  _problem->addKernel("JouleHeating", mean_en_name + "_joule_heating", params3);

  if (Using_offset)
  {
    InputParameters params4 = _factory.getValidParams("LogStabilizationMoles");
    params4.set<NonlinearVariableName>("variable") = {mean_en_name};
    // params4.set<Real>("offset") = (getParam<Real>("offset") - 5.0);
    // params4.set<Real>("offset") = (getParam<Real>("offset") - 2.0);
    params4.set<Real>("offset") = getParam<Real>("offset");
    params4.set<std::vector<SubdomainName>>("block") =
        getParam<std::vector<SubdomainName>>("block");
    /*
    params4.set<std::vector<TagName>>("extra_vector_tags") =
        getParam<std::vector<TagName>>("extra_tags");
        */
    _problem->addKernel("LogStabilizationMoles", mean_en_name + "_log_stabilization", params4);
  }
}

/*void
AddDriftDiffusionAction::addMeanEnergyADKernels(const std::string & em_name,
                                         const std::string & potential_name,
                                         const std::string & mean_en_name,
                                         const bool & Using_offset)
{
}*/

// Adding potentials charge sources
void
AddDriftDiffusionAction::addChargeSourceKernels(const std::string & potential_name,
                                                const std::string & charged_particle_name)
{
  InputParameters params = _factory.getValidParams("ChargeSourceMoles_KV");
  params.set<NonlinearVariableName>("variable") = {potential_name};
  params.set<std::vector<VariableName>>("charged") = {charged_particle_name};
  params.set<std::string>("potential_units") = getParam<std::string>("potential_units");
  params.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
  _problem->addKernel("ChargeSourceMoles_KV", charged_particle_name + "_charge_source", params);
}

/*void
AddDriftDiffusionAction::addChargeSourceADKernels(const std::string & potential_name,
                                             const std::string & charged_particle_name)
{
}*/

// Adding Kernels for the electrons
void
AddDriftDiffusionAction::addADKernels(const std::string & name,
                                      const std::string & potential_name,
                                      const bool & Using_offset,
                                      const bool & charged,
                                      const bool & energy)
{
  _problem->haveADObjects(true);

  InputParameters params = _factory.getValidParams("ADTimeDerivativeLog");
  params.set<NonlinearVariableName>("variable") = {name};
  params.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
  _problem->addKernel("ADTimeDerivativeLog", name + "_time_deriv", params);

  if (charged)
  {
    InputParameters params1 = _factory.getValidParams("ADEFieldAdvection");
    params1.set<NonlinearVariableName>("variable") = {name};
    params1.set<std::vector<VariableName>>("potential") = {potential_name};
    params1.set<Real>("position_units") = getParam<Real>("position_units");
    params1.set<std::vector<SubdomainName>>("block") =
        getParam<std::vector<SubdomainName>>("block");
    _problem->addKernel("ADEFieldAdvection", name + "_advection", params1);
    //_problem->haveADObjects(true);
  }

  InputParameters params2 = _factory.getValidParams("ADCoeffDiffusion");
  params2.set<NonlinearVariableName>("variable") = {name};
  params2.set<Real>("position_units") = getParam<Real>("position_units");
  params2.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
  _problem->addKernel("ADCoeffDiffusion", name + "_diffusion", params2);
  //_problem->haveADObjects(true);

  if (energy)
  {
    InputParameters params3 = _factory.getValidParams("ADJouleHeating");
    params3.set<NonlinearVariableName>("variable") = {name};
    params3.set<std::vector<VariableName>>("potential") = {potential_name};
    params3.set<std::vector<VariableName>>("em") = {getParam<NonlinearVariableName>("electrons")};
    params3.set<std::string>("potential_units") = getParam<std::string>("potential_units");
    params3.set<Real>("position_units") = getParam<Real>("position_units");
    params3.set<std::vector<SubdomainName>>("block") =
        getParam<std::vector<SubdomainName>>("block");
    /*
    params3.set<std::vector<TagName>>("extra_vector_tags") =
        getParam<std::vector<TagName>>("extra_tags");
        */
    _problem->addKernel("ADJouleHeating", name + "_joule_heating", params3);
    //_problem->haveADObjects(true);
  }

  if (Using_offset)
  {
    InputParameters params4 = _factory.getValidParams("LogStabilizationMoles");
    params4.set<NonlinearVariableName>("variable") = {name};
    params4.set<Real>("offset") = getParam<Real>("offset");
    params4.set<std::vector<SubdomainName>>("block") =
        getParam<std::vector<SubdomainName>>("block");
    _problem->addKernel("LogStabilizationMoles", name + "_log_stabilization", params4);
    //_problem->haveADObjects(true);
  }
}

// Adding the Aux kernels to convert scaled position units
void
AddDriftDiffusionAction::addPosition(const std::string & position_name, const int & component)
{
  InputParameters params = _factory.getValidParams("Position");
  params.set<AuxVariableName>("variable") = {position_name};
  params.set<Real>("position_units") = getParam<Real>("position_units");
  params.set<int>("component") = component;
  _problem->addAuxKernel("Position", position_name, params);
}

// Adding the Aux kernels to convert densities from log form
void
AddDriftDiffusionAction::addDensityLog(const std::string & particle_name)
{
  InputParameters params = _factory.getValidParams("DensityMoles");
  params.set<AuxVariableName>("variable") = particle_name + "_density";
  params.set<std::vector<VariableName>>("density_log") = {particle_name};
  params.set<bool>("use_moles") = getParam<bool>("use_moles");
  params.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
  _problem->addAuxKernel("DensityMoles", particle_name + "_density", params);
}

// Adding the Aux kernels for current
void
AddDriftDiffusionAction::addCurrent(const std::string & particle_name,
                                    const std::string & potential_name)
{
  InputParameters params = _factory.getValidParams("Current");
  params.set<AuxVariableName>("variable") = {"Current_" + particle_name};
  params.set<std::vector<VariableName>>("potential") = {potential_name};
  params.set<std::vector<VariableName>>("density_log") = {particle_name};
  params.set<Real>("position_units") = getParam<Real>("position_units");
  params.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
  _problem->addAuxKernel(_ad_prepend + "Current", "Current_" + particle_name, params);
}

// Adding the Aux kernels for the Efield
void
AddDriftDiffusionAction::addEfield(const std::string & Efield_name,
                                   const std::string & potential_name,
                                   const int & component)
{
  InputParameters params = _factory.getValidParams("Efield");
  params.set<AuxVariableName>("variable") = {Efield_name};
  params.set<std::vector<VariableName>>("potential") = {potential_name};
  params.set<Real>("position_units") = getParam<Real>("position_units");
  params.set<int>("component") = component;
  params.set<std::string>("potential_units") = getParam<std::string>("potential_units");
  params.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
  _problem->addAuxKernel("Efield", Efield_name, params);
}
