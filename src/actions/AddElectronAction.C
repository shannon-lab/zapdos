#include "AddElectronAction.h"
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








registerMooseAction("ZapdosApp", AddElectronAction, "add_kernel");
registerMooseAction("ZapdosApp", AddElectronAction, "add_aux_kernel");
registerMooseAction("ZapdosApp", AddElectronAction, "add_bc");

template <>
InputParameters
validParams<AddElectronAction>()
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
  params.addParam<NonlinearVariableName>("potential", "The gives the potential a variable name");
  params.addParam<bool>("use_ad", false, "Whether or not to use automatic differentiation.");
  params.addParam<bool>(
      "Is_potential_unique",
      false,
      "Is this potential unique to this block?"
      "If not, then the potential variable should be defined in the Variable Block.");
  params.addParam<bool>("First_DriftDiffusionActionAD_in_block",
                        true,
                        "Is this the first DriftDiffusionActionAD for this block?"
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
  params.addParam<Real>(
      "mean_offset", 15.0, "The offset parameter for the mean energy that goes into the exponential function");
  params.addRequiredParam<std::string>("potential_units", "Units of potential");
  params.addRequiredParam<bool>("use_moles", "Whether to convert from units of moles to #.");
  params.addParam<std::vector<std::string>>(
      "Additional_Outputs",
      "Current list of available ouputs options in this action: Current, ElectronTemperature,"
      " EField");
  params.addParam<MooseEnum>("order", "FIRST", "The variable order.");
  params.addParam<std::vector<BoundaryName>>("boundary","Boundary for first electrons");
  params.addParam<Real>("r","the reflection coefficient");
  return params;
}
AddElectronAction::AddElectronAction(InputParameters params)
  : Action(params){}


void AddElectronAction::act()
{
  MooseSharedPointer<Action> action;
  MooseSharedPointer<MooseObjectAction> moose_object_action;

  // Converting the given names into VariableName
  NonlinearVariableName em_name;
  NonlinearVariableName potential_name;
  NonlinearVariableName mean_en_name;



  bool em_present = (isParamValid("electrons") ? true : false);
  bool potential_present = (isParamValid("potential") ? true : false);
  bool mean_en_present = (isParamValid("mean_energy") ? true : false);

  if (em_present)
    em_name = getParam<NonlinearVariableName>("electrons"); //why is this necessary?
  if (potential_present)
    potential_name = getParam<NonlinearVariableName>("potential");
  if (mean_en_present)
    mean_en_name = getParam<NonlinearVariableName>("mean_energy");


  // Converting the given additional outputs
  std::vector<std::string> Outputs = getParam<std::vector<std::string>>("Additional_Outputs");

  ///unsigned int number_outputs = Outputs.size();

  // Converting the boolean statements
  ///bool Using_offset = getParam<bool>("using_offset");
  ///bool New_potential = getParam<bool>("Is_potential_unique");
  ///bool First_Action = getParam<bool>("First_DriftDiffusionActionAD_in_block");
  // The variable type for the nonlinear variables
  auto fe_type = AddVariableAction::feType(_pars);
  auto type = AddVariableAction::determineType(fe_type, 1);
  auto var_params = _factory.getValidParams(type);
  //var_params.set<MooseEnum>("order") = "FIRST";
  var_params.set<MooseEnum>("order") = getParam<MooseEnum>("order");
  //var_params.set<MooseEnum>("order") = "SECOND";
  var_params.set<MooseEnum>("family") = "LAGRANGE";
  var_params.set<std::vector<SubdomainName>>("block") =
      getParam<std::vector<SubdomainName>>("block");

  // The variable type for the aux variables
  auto aux_params = _factory.getValidParams(type);
  aux_params.set<MooseEnum>("order") = "CONSTANT";
  aux_params.set<MooseEnum>("family") = "MONOMIAL";
  aux_params.set<std::vector<SubdomainName>>("block") =
      getParam<std::vector<SubdomainName>>("block");

  if (_current_task == "add_kernel")
  {
    if (em_present)
    {
      addElectronKernels(em_name, potential_name, mean_en_name);
    }
  }

  if (_current_task == "add_bc")
  {
    addElectronBoundaries(em_name, potential_name, mean_en_name);
  }


}

void AddElectronAction::addElectronKernels(const std::string & em_name,
                                           const std::string & potential_name,
                                           const std::string & mean_en_name
                                           )
{

  InputParameters params = _factory.getValidParams("ADEFieldAdvection");
  params.set<NonlinearVariableName>("variable") = {em_name};
  params.set<std::vector<VariableName>>("potential") = {potential_name};
  params.set<Real>("position_units") = getParam<Real>("position_units");
  params.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
  _problem->addKernel("ADEFieldAdvection", em_name + "_advection", params);

  InputParameters params1 = _factory.getValidParams("ADTimeDerivativeLog");
  params1.set<NonlinearVariableName>("variable") = {em_name};
  params1.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
  _problem->addKernel("ADTimeDerivativeLog", em_name + "_time_deriv", params1);

  InputParameters params2 = _factory.getValidParams("ADCoeffDiffusion");
  params2.set<NonlinearVariableName>("variable") = {em_name};
  //params2.set<std::vector<VariableName>>("mean_en") = {mean_en_name};
  params2.set<Real>("position_units") = getParam<Real>("position_units");
  params2.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
  _problem->addKernel("ADCoeffDiffusion", em_name + "_diffusion", params2);

  InputParameters params3 = _factory.getValidParams("ADTimeDerivativeLog");
  params3.set<NonlinearVariableName>("variable") = {mean_en_name};
  params3.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
  _problem->addKernel("ADTimeDerivativeLog", mean_en_name + "time_deriv", params3);

  InputParameters params4 = _factory.getValidParams("ADEFieldAdvection");
  params4.set<NonlinearVariableName>("variable") = {mean_en_name};
  params4.set<std::vector<VariableName>>("potential") = {potential_name};
  params4.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
  params4.set<Real>("position_units") = getParam<Real>("position_units");
  _problem->addKernel("ADEFieldAdvection", mean_en_name + "_advection", params4);

  InputParameters params5 = _factory.getValidParams("ADCoeffDiffusion");
  params5.set<NonlinearVariableName>("variable") = {mean_en_name};
  params5.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
  params5.set<Real>("position_units") = getParam<Real>("position_units");
  _problem->addKernel("ADCoeffDiffusion", mean_en_name + "_diffusion", params5);

  InputParameters params6 = _factory.getValidParams("ADJouleHeating");
  params6.set<NonlinearVariableName>("variable") = {mean_en_name};
  params6.set<std::vector<VariableName>>("potential") = {potential_name};
  params6.set<std::vector<VariableName>>("em") = {em_name};
  params6.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
  params6.set<Real>("position_units") = getParam<Real>("position_units");
  params6.set<std::string>("potential_units") = getParam<std::string>("potential_units");
  _problem->addKernel("ADJouleHeating", mean_en_name + "_joule_heating", params6);


  InputParameters params7 = _factory.getValidParams("LogStabilizationMoles");
  params7.set<NonlinearVariableName>("variable") = {mean_en_name};
  params7.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
  params7.set<Real>("offset") = getParam<Real>("mean_offset");
  _problem->addKernel("LogStabilizationMoles", mean_en_name + "_log_stabilization", params7);

  InputParameters params8 = _factory.getValidParams("LogStabilizationMoles");
  params8.set<NonlinearVariableName>("variable") = {em_name}; //why the brackets?
  params8.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
  params8.set<Real>("offset") = getParam<Real>("offset");
  _problem->addKernel("LogStabilizationMoles", em_name + "_log_stabilization", params8);

}
void AddElectronAction::addElectronBoundaries(const std::string & em_name,
                                           const std::string & potential_name,
                                           const std::string & mean_en_name
                                           )
{
  InputParameters params = _factory.getValidParams("ADHagelaarElectronBC");
  params.set<NonlinearVariableName>("variable") = {em_name};
  params.set<std::vector<BoundaryName>>("boundary") = getParam<std::vector<BoundaryName>>("boundary");
  params.set<Real>("r") = getParam<Real>("r");
  params.set<std::vector<VariableName>>("potential") = {potential_name};
  params.set<std::vector<VariableName>>("mean_en") = {mean_en_name};
  params.set<Real>("position_units") = getParam<Real>("position_units");
  _problem->addBoundaryCondition("ADHagelaarElectronBC", em_name + "_bc", params);

  InputParameters params2 = _factory.getValidParams("ADHagelaarEnergyBC");
  params2.set<NonlinearVariableName>("variable") = {mean_en_name};
  params2.set<std::vector<BoundaryName>>("boundary") = getParam<std::vector<BoundaryName>>("boundary");
  params2.set<Real>("r") = getParam<Real>("r");
  params2.set<std::vector<VariableName>>("potential") = {potential_name};
  params2.set<std::vector<VariableName>>("em") = {em_name};
  params2.set<Real>("position_units") = getParam<Real>("position_units");
  _problem->addBoundaryCondition("ADHagelaarEnergyBC", mean_en_name + "_bc", params2);
}
