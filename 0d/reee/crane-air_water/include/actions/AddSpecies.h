#pragma once

#include "AddVariableAction.h"
#include "Action.h"

class AddSpecies;

template <>
InputParameters validParams<AddSpecies>();

class AddSpecies : public AddVariableAction
{
public:
  AddSpecies(const InputParameters & params);

  virtual void act() override;

  void createInitialConditions(const std::string & var_name, const Real & value);

private:
  /// Primary species to add
  const std::vector<NonlinearVariableName> _vars;
  const std::vector<Real> _vals;
  bool _use_scalar;
  bool _add_time_derivatives;
  bool _use_log;
  /// Variable scaling
  const std::vector<Real> _scale_factor;
};
