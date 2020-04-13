//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "AddVariableAction.h"
#include "Action.h"

class AddPeriodicRelativeNodalDifference;

template <>
InputParameters validParams<AddPeriodicRelativeNodalDifference>();

class AddPeriodicRelativeNodalDifference : public Action
{
public:
  AddPeriodicRelativeNodalDifference(InputParameters params);

  virtual void act();

protected:
  virtual void addPerviousSolutionsIC(const std::string & variable_name, const Real & initial);
  virtual void addPerviousSolutionsKernels(const std::string & variable_name,
                                           const std::string & var_old_name);
  virtual void addNormalizationKernels(const std::string & variable_name,
                                       const std::string & source,
                                       const std::string & averaged,
                                       const bool & log);

  virtual void addAverageNodalPP(const std::string & variable_name, const bool & log);

  virtual void addRelativePeriodicDiffPP(const std::string & variable_name,
                                         const std::string & var_old_name,
                                         const std::string & name);

  Real _start_time;
  Real _period;
  Real _num_controller_set;

  std::vector<std::string> _enable_start;
  std::vector<std::string> _enable_end;
  std::vector<Real> _enable_start_start_time_index;
  std::vector<Real> _enable_start_end_time_index;
  std::vector<Real> _enable_end_start_time_index;
  std::vector<Real> _enable_end_end_time_index;
};
