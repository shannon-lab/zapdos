#pragma once

#include "Action.h"

class AddPeriodicControllers;

template <>
InputParameters validParams<AddPeriodicControllers>();

//class AddPeriodicControllers : public AddControlAction
class AddPeriodicControllers : public Action
{
public:
  AddPeriodicControllers(InputParameters params);

  virtual void act();

protected:

  std::vector<std::string> _enable_start;
  std::vector<std::string> _enable_during;
  std::vector<std::string> _enable_end;

  std::vector<std::string> _disable_start;
  std::vector<std::string> _disable_during;
  std::vector<std::string> _disable_end;

  Real _start_time;
  Real _period;
  Real _cycles_per_controls;
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
