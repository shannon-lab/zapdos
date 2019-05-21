//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "AddLotsOfTimeDerivatives.h"
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

registerMooseAction("ZapdosApp", AddLotsOfTimeDerivatives, "add_variable");
registerMooseAction("ZapdosApp", AddLotsOfTimeDerivatives, "add_kernel");
registerMooseAction("ZapdosApp", AddLotsOfTimeDerivatives, "add_bc");

template <>
InputParameters
validParams<AddLotsOfTimeDerivatives>()
{
  MooseEnum families(AddVariableAction::getNonlinearVariableFamilies());
  MooseEnum orders(AddVariableAction::getNonlinearVariableOrders());

  InputParameters params = validParams<AddVariableAction>();
  params.addRequiredParam<std::vector<NonlinearVariableName>>(
      "variables", "The names of the variables for which TimeDerivative kernels should be added");

  return params;
}

AddLotsOfTimeDerivatives::AddLotsOfTimeDerivatives(InputParameters params)
  : AddVariableAction(params)
{
}

void
AddLotsOfTimeDerivatives::act()
{
  MooseSharedPointer<Action> action;
  MooseSharedPointer<MooseObjectAction> moose_object_action;

  std::vector<NonlinearVariableName> variables =
      getParam<std::vector<NonlinearVariableName>>("variables");

  unsigned int number = variables.size();

  if (_current_task == "add_kernel")
  {
    for (unsigned int cur_num = 0; cur_num < number; cur_num++)
    {
      std::string var_name = variables[cur_num];
      InputParameters params = _factory.getValidParams("TimeDerivative");
      params.set<NonlinearVariableName>("variable") = var_name;
      _problem->addKernel("TimeDerivative", var_name, params);
    }
  }
}
