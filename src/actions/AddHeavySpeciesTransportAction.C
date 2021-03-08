#include "AddHeavySpeciesTransportAction.h"
#include "Parser.h"
#include "FEProblem.h"
#include "Factory.h"
#include "MooseEnum.h"
#include "AddVariableAction.h"
#include "Conversion.h"
#include "ActionFactory.h"
#include "MooseObjectAction.h"
#include "MooseApp.h"
//#include "addMaterialAction.h"

#include "libmesh/vector_value.h"

#include "pcrecpp.h"

#include <sstream>
#include <stdexcept>
#include <iostream>

// libmesh includes
#include "libmesh/libmesh.h"
#include "libmesh/exodusII_io.h"
#include "libmesh/equation_systems.h"
#include "libmesh/nonlinear_implicit_system.h"
#include "libmesh/explicit_system.h"
#include "libmesh/string_to_enum.h"
#include "libmesh/fe.h"


registerMooseAction("ZapdosApp", AddHeavySpeciesTransportAction, "add_kernel");
registerMooseAction("ZapdosApp", AddHeavySpeciesTransportAction, "add_aux_kernel");
registerMooseAction("ZapdosApp", AddHeavySpeciesTransportAction, "add_material");
registerMooseAction("ZapdosApp", AddHeavySpeciesTransportAction, "add_variable");

template <>
InputParameters
validParams<AddHeavySpeciesTransportAction>()
{
MooseEnum families(AddVariableAction::getNonlinearVariableFamilies());
MooseEnum orders(AddVariableAction::getNonlinearVariableOrders());

InputParameters params = validParams<AddVariableAction>();

params.addRequiredParam<NonlinearVariableName>("name", "The name of the heavy species");
params.addRequiredParam<Real>("mass", "Mass of the heavy species");
params.addRequiredParam<std::string>("potential_units", "The potential units.");
params.addRequiredParam<Real>("charge", "Charge of heavy species.");
params.addParam<Real>("time_units", 1, "Units of time");
params.addParam<Real>("mobility", "The species mobility (if applicable).");
params.addParam<Real>("diffusivity", "The species diffusivity (if applicable).");

params.addParam<std::vector<SubdomainName>>("block",
                                            "The subdomain that this action applies to.");
params.addParam<NonlinearVariableName>("potential",  "The gives the potential a variable name");
params.addRequiredParam<Real>("position_units", "Units of position");
params.addParam<std::string>("transport_properties", "Describes calculation for transport expression");
params.addParam<bool>("aux_var", true,  "boolean to describe whether the material is an auxiliary variable");
return params;
}
AddHeavySpeciesTransportAction::AddHeavySpeciesTransportAction(InputParameters params)
: Action(params){}

void AddHeavySpeciesTransportAction::act()
{
  MooseSharedPointer<Action> action;
  MooseSharedPointer<MooseObjectAction> moose_object_action;
  NonlinearVariableName name_ = getParam<NonlinearVariableName>("name");
  NonlinearVariableName potential_name_ = getParam<NonlinearVariableName>("potential");
  Real mass_ = getParam<Real>("mass");
  Real charge_ = getParam<Real>("charge");

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
  bool is_aux_var = getParam<bool>("aux_var");

  bool charged = false;
  if (charge_ != 0)
    charged = true;





  if (_current_task == "add_material") //there is no register moose action add_material
  {
    addADHeavySpeciesMaterial(name_, mass_, charge_);
  }
  if (_current_task == "add_kernel")
  {
    if (charged)
    {
      addADHeavySpeciesChargedKernels(name_, potential_name_);
    }
    else
    {
      addADHeavySpeciesNeutralKernels(name_);
    }
  }
  if (_current_task == "add_variable")
  {
    if (is_aux_var)
    {
      std::cout << "nice " << name_ << std::endl;
      _problem->addAuxVariable(type, name_ + "_density_", var_params);
    }
    else
    {
      _problem->addVariable(type, name_, var_params);
    }
  }

}

void AddHeavySpeciesTransportAction::addADHeavySpeciesMaterial(const std::string & name,
                                                               const Real & mass,
                                                               const Real & charge)
{
  //const std::string & potential_name = getParam<NonlinearVariableName>("potential");
  InputParameters params = _factory.getValidParams("ADHeavySpeciesMaterial");
  params.set<std::string>("heavy_species_name") = name;
  params.set<Real>("heavy_species_mass") = mass;
  params.set<std::string>("potential_units") = getParam<std::string>("potential_units");
  params.set<Real>("heavy_species_charge") = charge;
  if (isParamValid("block") ? true : false)
    params.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
  if (isParamValid("diffusivity") ? true : false)
    params.set<Real>("diffusivity") = getParam<Real>("diffusivity");
  if (isParamValid("mobility") ? true : false)
    params.set<Real>("mobility") = getParam<Real>("mobility");
  if (isParamValid("time_units") ? true : false)
    params.set<Real>("time_units") = getParam<Real>("time_units");
  //if necessary We can do the same if statements for
  //time_units and mobility, but it looks like we dont use it so
  //we can save some processing (not really that much more efficient tho)
  _problem->addMaterial("ADHeavySpeciesMaterial", name + "_mat", params);
}

void AddHeavySpeciesTransportAction::addADHeavySpeciesChargedKernels(const std::string & name,
                                                                     const std::string & potential_name)
{
  if (isParamValid("block") ? true : false)
  {
    InputParameters params = _factory.getValidParams("ADTimeDerivativeLog");
    params.set<NonlinearVariableName>("variable") = {name};
    params.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
    _problem->addKernel("ADTimeDerivativeLog", name + "_time_deriv_", params);

    InputParameters params2 = _factory.getValidParams("ADCoeffDiffusion");
    params2.set<NonlinearVariableName>("variable") = {name};
    params2.set<Real>("position_units") = getParam<Real>("position_units");
    params2.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
    _problem->addKernel("ADCoeffDiffusion", name + "_diffusion_", params2);
  }

  InputParameters params3 = _factory.getValidParams("ADEFieldAdvection");
  params3.set<NonlinearVariableName>("variable") = {name};
  params3.set<std::vector<VariableName>>("potential") = {potential_name};
  params3.set<Real>("position_units") = getParam<Real>("position_units");
  params3.set<std::vector<SubdomainName>>("block") =
      getParam<std::vector<SubdomainName>>("block");
  _problem->addKernel("ADEFieldAdvection", name + "_advection_", params3);

  InputParameters params4 = _factory.getValidParams("ChargeSourceMoles_KV");
  params4.set<NonlinearVariableName>("variable") = {potential_name};
  params4.set<std::vector<VariableName>>("charged") = {name};
  params4.set<std::string>("potential_units") = getParam<std::string>("potential_units");
  params4.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
  _problem->addKernel("ChargeSourceMoles_KV", name + "_charge_source_", params4);

}
void AddHeavySpeciesTransportAction::addADHeavySpeciesNeutralKernels(const std::string & name)
{
  if (isParamValid("block") ? true : false)
  {
    InputParameters params = _factory.getValidParams("ADTimeDerivativeLog");
    params.set<NonlinearVariableName>("variable") = {name};
    params.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
    _problem->addKernel("ADTimeDerivativeLog", name + "_time_deriv_", params);

    InputParameters params2 = _factory.getValidParams("ADCoeffDiffusion");
    params2.set<NonlinearVariableName>("variable") = {name};
    params2.set<Real>("position_units") = getParam<Real>("position_units");
    params2.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
    _problem->addKernel("ADCoeffDiffusion", name + "_diffusion_", params2);
  }
}
