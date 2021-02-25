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
//registerMooseAction("ZapdosApp", AddHeavySpeciesTransportAction, "add_materials");
registerMooseAction("ZapdosApp", AddHeavySpeciesTransportAction, "add_variable");

template <>
InputParameters
validParams<AddHeavySpeciesTransportAction>()
{
MooseEnum families(AddVariableAction::getNonlinearVariableFamilies());
MooseEnum orders(AddVariableAction::getNonlinearVariableOrders());

InputParameters params = validParams<AddVariableAction>();

params.addRequiredParam<std::string>("name", "The name of the heavy species");
params.addRequiredParam<Real>("mass", "Mass of the heavy species");
params.addRequiredParam<std::string>("potential_units", "The potential units.");
params.addRequiredParam<Real>("charge", "Charge of heavy species.");
params.addParam<Real>("time_units", 1, "Units of time");
params.addParam<Real>("mobility", "The species mobility (if applicable).");
params.addParam<Real>("diffusivity", "The species diffusivity (if applicable).");

params.addParam<std::vector<SubdomainName>>("block",
                                            "The subdomain that this action applies to.");

return params;
}
AddHeavySpeciesTransportAction::AddHeavySpeciesTransportAction(InputParameters params)
: Action(params){}

void AddHeavySpeciesTransportAction::act()
{
  MooseSharedPointer<Action> action;
  MooseSharedPointer<MooseObjectAction> moose_object_action;


  if (_current_task == "add_kernel") //there is no register moose action add_material
  {
    addADHeavySpeciesMaterial();
  }

}

void AddHeavySpeciesTransportAction::addADHeavySpeciesMaterial()
{
  InputParameters params = _factory.getValidParams("ADHeavySpeciesMaterial");
  params.set<std::string>("heavy_species_name") = getParam<std::string>("name");
  params.set<Real>("heavy_species_mass") = getParam<Real>("mass");
  params.set<std::string>("potential_units") = getParam<std::string>("potential_units");
  params.set<Real>("heavy_species_charge") = getParam<Real>("charge");
  if (isParamValid("block") ? true : false)
    params.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
  if (isParamValid("diffusivity") ? true : false)
    params.set<Real>("diffusivity") = getParam<Real>("diffusivity");
  //if necessary We can do the same if statements for
  //time_units and mobility, but it looks like we dont use it so
  //we can save some processing (not really that much more efficient tho)
  _problem->addMaterial("ADHeavySpeciesMaterial", getParam<std::string>("name")+ "_mat", params);

}
