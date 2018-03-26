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

#include "AddLotsOfCoeffDiffusion.h"
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

registerMooseAction("ZapdosApp", AddLotsOfCoeffDiffusion, "add_variable");
registerMooseAction("ZapdosApp", AddLotsOfCoeffDiffusion, "add_kernel");
registerMooseAction("ZapdosApp", AddLotsOfCoeffDiffusion, "add_bc");

template <>
InputParameters
validParams<AddLotsOfCoeffDiffusion>()
{
  MooseEnum families(AddVariableAction::getNonlinearVariableFamilies());
  MooseEnum orders(AddVariableAction::getNonlinearVariableOrders());

  InputParameters params = validParams<AddVariableAction>();
  //  params.addRequiredParam<unsigned int>("number", "The number of variables to add");
  params.addRequiredParam<std::vector<NonlinearVariableName>>(
      "variables", "The names of the variables for which CoeffDiffusion kernels should be added");
  // params.addRequiredParam<std::vector<std::string> >("diffusion_coeffs", "The names of the
  // diffusion coefficients used in the kernels.");

  return params;
}

AddLotsOfCoeffDiffusion::AddLotsOfCoeffDiffusion(InputParameters params) : AddVariableAction(params)
{
}

void
AddLotsOfCoeffDiffusion::act()
{
  MooseSharedPointer<Action> action;
  MooseSharedPointer<MooseObjectAction> moose_object_action;
  //  unsigned int number = getParam<unsigned int>("number");

  std::vector<NonlinearVariableName> variables =
      getParam<std::vector<NonlinearVariableName>>("variables");
  // std::vector<std::string> diffusion_coeffs = getParam<std::vector<std::string> >
  // ("diffusion_coeffs");

  unsigned int number = variables.size();

  /*  if (_current_task == "add_variable")
    {
      for (unsigned int cur_num = 0; cur_num < number; cur_num++)
        {
          //      std::string var_name = getShortName() + Moose::stringify(cur_num);
          std::string var_name = variables[cur_num];
          addVariable(var_name);
        }
        } */
  //  else if (_current_task == "add_kernel")
  if (_current_task == "add_kernel")
  {
    for (unsigned int cur_num = 0; cur_num < number; cur_num++)
    {
      std::string var_name = variables[cur_num];
      // std::string indiv_diffusion_coeff = diffusion_coeffs[cur_num];
      InputParameters params = _factory.getValidParams("CoeffDiffusion");
      params.set<NonlinearVariableName>("variable") = var_name;
      params.set<std::string>("var_name_string") = var_name;
      _problem->addKernel("CoeffDiffusion", var_name, params);
    }
  }
  //  else if (_current_task == "add_bc")
  //    {
  //      for (unsigned int cur_num = 0; cur_num < number; cur_num++)
  //      {
  //        std::string var_name = variables[cur_num];
  //
  //        InputParameters params = _factory.getValidParams("DirichletBC");
  //        params.set<NonlinearVariableName>("variable") = var_name;
  //        params.set<std::vector<BoundaryName> >("boundary").push_back("left");
  //        params.set<Real>("value") = 0;
  //
  //        _problem->addBoundaryCondition("DirichletBC", var_name + "_left", params);
  //
  //        params.set<std::vector<BoundaryName> >("boundary")[0] = "right";
  //        params.set<Real>("value") = 1;
  //
  //        _problem->addBoundaryCondition("DirichletBC", var_name + "_right", params);
  //      }
  //    }
}
