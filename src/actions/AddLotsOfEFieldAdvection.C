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

#include "AddLotsOfEFieldAdvection.h"
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

#include <sstream>
#include <stdexcept>

// libMesh includes
#include "libmesh/libmesh.h"
#include "libmesh/exodusII_io.h"
#include "libmesh/equation_systems.h"
#include "libmesh/nonlinear_implicit_system.h"
#include "libmesh/explicit_system.h"
#include "libmesh/string_to_enum.h"
#include "libmesh/fe.h"

registerMooseAction("ZapdosApp", AddLotsOfEFieldAdvection, "add_variable");
registerMooseAction("ZapdosApp", AddLotsOfEFieldAdvection, "add_kernel");
registerMooseAction("ZapdosApp", AddLotsOfEFieldAdvection, "add_bc");

template <>
InputParameters
validParams<AddLotsOfEFieldAdvection>()
{
  MooseEnum families(AddVariableAction::getNonlinearVariableFamilies());
  MooseEnum orders(AddVariableAction::getNonlinearVariableOrders());

  InputParameters params = validParams<AddVariableAction>();
  params.addRequiredParam<std::vector<NonlinearVariableName>>(
      "variables", "The names of the variables for which EFieldAdvection kernels should be added");
  // params.addRequiredParam<std::string>("potential", "The potential that will be responsible for
  // advecting the species.");
  params.addRequiredParam<std::vector<VariableName>>(
      "potential", "A dummy vector that holds the potential to couple in for advection");

  return params;
}

AddLotsOfEFieldAdvection::AddLotsOfEFieldAdvection(InputParameters params)
  : AddVariableAction(params)
{
}

void
AddLotsOfEFieldAdvection::act()
{
  MooseSharedPointer<Action> action;
  MooseSharedPointer<MooseObjectAction> moose_object_action;

  std::vector<NonlinearVariableName> variables =
      getParam<std::vector<NonlinearVariableName>>("variables");
  // std::string potential = getParam<std::string>("potential");
  std::vector<VariableName> potential = getParam<std::vector<VariableName>>("potential");

  unsigned int number = variables.size();

  if (_current_task == "add_kernel")
  {
    for (unsigned int cur_num = 0; cur_num < number; cur_num++)
    {
      std::string var_name = variables[cur_num];
      // std::vector<std::string> fictional_vec_variables;
      // std::vector<VariableName> vel_vec_variable;
      // fictional_vec_varables.push_back(potential[0]);
      // vel_vec_variable.push_back(potential[0]);
      InputParameters params = _factory.getValidParams("EFieldAdvection");
      params.set<NonlinearVariableName>("variable") = var_name;
      params.set<std::string>("var_name_string") = var_name;
      params.set<std::vector<VariableName>>("potential") = potential;
      _problem->addKernel("EFieldAdvection", var_name, params);
    }
  }
}
