#pragma once

#include "AddVariableAction.h"
#include "Action.h"
#include "ChemicalReactionsBase.h"

class AddScalarReactions;

template <>
InputParameters validParams<AddScalarReactions>();

// class ChemicalReactions : public AddVariableAction
class AddScalarReactions : public ChemicalReactionsBase
{
public:
  AddScalarReactions(InputParameters params);
  // AddScalarReactions(InputParameters params) : ChemicalReactionsBase(params) {};

  virtual void act();

protected:
  std::vector<std::string> _aux_species;
};
