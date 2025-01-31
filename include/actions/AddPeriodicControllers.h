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

#include "Action.h"

// class AddPeriodicControllers : public AddControlAction
class AddPeriodicControllers : public Action
{
public:
  AddPeriodicControllers(const InputParameters & params);

  static InputParameters validParams();

  virtual void act();

protected:
  virtual void AddTimePeriod(const std::string & enableORdisable,
                             const std::vector<std::string> & objects,
                             const std::vector<Real> & start_times,
                             const std::vector<Real> & end_times,
                             const std::string & name_num,
                             const bool & first_controller);

  std::vector<std::string> _enable_start;
  std::vector<std::string> _enable_during;
  std::vector<std::string> _enable_end;

  std::vector<std::string> _disable_start;
  std::vector<std::string> _disable_during;
  std::vector<std::string> _disable_end;

  Real _start_time;
  Real _period;
  Real _cycles_per_controls;
  Real _cycles_between_controls;
  Real _num_controller_set;
  std::string _name;

  std::vector<Real> _enable_start_start_time_index;
  std::vector<Real> _enable_start_end_time_index;

  std::vector<Real> _enable_during_start_time_index;
  std::vector<Real> _enable_during_end_time_index;

  std::vector<Real> _enable_end_start_time_index;
  std::vector<Real> _enable_end_end_time_index;

  std::vector<Real> _disable_start_start_time_index;
  std::vector<Real> _disable_start_end_time_index;

  std::vector<Real> _disable_during_start_time_index;
  std::vector<Real> _disable_during_end_time_index;

  std::vector<Real> _disable_end_start_time_index;
  std::vector<Real> _disable_end_end_time_index;
};
