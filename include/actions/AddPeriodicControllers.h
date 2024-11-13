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

/*
 *  This Action automatically adds multiply 'TimePeriod' controllers for
 *  the purpose of enabling and disabling multiple objects during multiple cycles.
 */
class AddPeriodicControllers : public Action
{
public:
  AddPeriodicControllers(const InputParameters & params);

  static InputParameters validParams();

  virtual void act();

protected:
  /// Function that adds a 'TimePeriod' controller
  virtual void AddTimePeriod(const std::string & enableORdisable,
                             const std::vector<std::string> & objects,
                             const std::vector<Real> & start_times,
                             const std::vector<Real> & end_times,
                             const std::string & name_num,
                             const bool & first_controller);

  /// A list of objects names to enable at the start of the cycle
  std::vector<std::string> _enable_start;
  /// A list of objects names to enable during the cycle
  std::vector<std::string> _enable_during;
  /// A list of objects names to enable at the end of the cycle
  std::vector<std::string> _enable_end;

  /// A list of objects names to disable at the start of the cycle
  std::vector<std::string> _disable_start;
  /// A list of objects names to disable during the cycle
  std::vector<std::string> _disable_during;
  /// A list of objects names to disable at the end of the cycle
  std::vector<std::string> _disable_end;

  /// The starting time to begin adding 'TimePeriod' controllers
  Real _start_time;
  /// The period of the cycle
  Real _period;
  /// The number of cycles between enabling and disabling objects
  Real _cycles_per_controls;
  /// Total number of 'TimePeriod' controllers to add
  Real _num_controller_set;
  /// Name of the 'TimePeriod' controllers
  std::string _name;

  /// The array that holds the start times for objects that are enable at the start of the cycle
  std::vector<Real> _enable_start_start_time_index;
  /// The array that holds the end times for objects that are enable at the start of the cycle
  std::vector<Real> _enable_start_end_time_index;

  /// The array that holds the start times for objects that are enable at during the cycle
  std::vector<Real> _enable_during_start_time_index;
  /// The array that holds the end times for objects that are enable at during the cycle
  std::vector<Real> _enable_during_end_time_index;

  /// The array that holds the start times for objects that are enable at the end of the cycle
  std::vector<Real> _enable_end_start_time_index;
  /// The array that holds the end times for objects that are enable at the end of the cycle
  std::vector<Real> _enable_end_end_time_index;

  /// The array that holds the start times for objects that are disable at the start of the cycle
  std::vector<Real> _disable_start_start_time_index;
  /// The array that holds the end times for objects that are disable at the start of the cycle
  std::vector<Real> _disable_start_end_time_index;

  /// The array that holds the start times for objects that are disable at during the cycle
  std::vector<Real> _disable_during_start_time_index;
  /// The array that holds the end times for objects that are disable at during the cycle
  std::vector<Real> _disable_during_end_time_index;

  /// The array that holds the start times for objects that are disable at the end of the cycle
  std::vector<Real> _disable_end_start_time_index;
  /// The array that holds the end times for objects that are disable at the end of the cycle
  std::vector<Real> _disable_end_end_time_index;
};
