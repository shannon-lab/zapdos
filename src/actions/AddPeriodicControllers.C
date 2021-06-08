//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "AddPeriodicControllers.h"
#include "Parser.h"
#include "FEProblem.h"
#include "Factory.h"
#include "MooseEnum.h"
#include "AddVariableAction.h"
#include "Conversion.h"
#include "ActionFactory.h"
#include "MooseObjectAction.h"
#include "MooseApp.h"
#include "Control.h"
#include "AddControlAction.h"

#include "libmesh/vector_value.h"

#include "pcrecpp.h"

#include <sstream>
#include <stdexcept>

// libmesh includes
#include "libmesh/libmesh.h"
#include "libmesh/exodusII_io.h"
#include "libmesh/equation_systems.h"
#include "libmesh/nonlinear_implicit_system.h"
#include "libmesh/explicit_system.h"
#include "libmesh/string_to_enum.h"
#include "libmesh/fe.h"

registerMooseAction("ZapdosApp", AddPeriodicControllers, "add_control");

InputParameters
AddPeriodicControllers::validParams()
{
  InputParameters params = AddVariableAction::validParams();

  params.addParam<std::vector<std::string>>(
      "Enable_at_cycle_start",
      std::vector<std::string>(),
      "A list of objects names to enable at the start of the cycle.");
  params.addParam<std::vector<std::string>>("Enable_during_cycle",
                                            std::vector<std::string>(),
                                            "A list of objects names to enable during the cycle.");
  params.addParam<std::vector<std::string>>(
      "Enable_at_cycle_end",
      std::vector<std::string>(),
      "A list of objects names to enable at the end of the cycle.");

  params.addParam<std::vector<std::string>>(
      "Disable_at_cycle_start",
      std::vector<std::string>(),
      "A list of objects names to disable at the start of the cycle.");
  params.addParam<std::vector<std::string>>("Disable_during_cycle",
                                            std::vector<std::string>(),
                                            "A list of objects names to disable during the cycle.");
  params.addParam<std::vector<std::string>>(
      "Disable_at_cycle_end",
      std::vector<std::string>(),
      "A list of objects names to disable at the end of the cycle.");

  params.addParam<Real>(
      "starting_cycle", 0.0, "The number of the cycles before starting the control scheme");
  params.addRequiredParam<Real>("cycle_frequency", "The cycle's frequency in Hz");
  params.addParam<Real>("cycles_per_controls",
                        1.0,
                        "The number of cycles that occurs during the controllers"
                        "(e.g. the number of cycles during the accelerations)");
  params.addParam<Real>("cycles_between_controls",
                        1.0,
                        "The number of cycles between controllers"
                        "(e.g. the number of cycles between accelerations)");
  params.addRequiredParam<Real>("num_controller_set",
                                "The number of controller sets"
                                "(e.g. the number of accelerations)");
  params.addRequiredParam<std::string>("name", "Custom name for the 'PeriodicControllers'.");

  params.addClassDescription(
      "This Action automatically adds multiply 'TimePeriod' controllers for"
      "the purpose of enabling and disabling multiple objects during multiple cycles."
      "(Ideally for periodic accelerations)");

  return params;
}

AddPeriodicControllers::AddPeriodicControllers(const InputParameters & params)
  : Action(params),
    _enable_start(getParam<std::vector<std::string>>("Enable_at_cycle_start")),
    _enable_during(getParam<std::vector<std::string>>("Enable_during_cycle")),
    _enable_end(getParam<std::vector<std::string>>("Enable_at_cycle_end")),

    _disable_start(getParam<std::vector<std::string>>("Disable_at_cycle_start")),
    _disable_during(getParam<std::vector<std::string>>("Disable_during_cycle")),
    _disable_end(getParam<std::vector<std::string>>("Disable_at_cycle_end")),

    _start_time((1. / getParam<Real>("cycle_frequency")) * getParam<Real>("starting_cycle")),
    _period(1. / getParam<Real>("cycle_frequency")),
    _cycles_per_controls(getParam<Real>("cycles_per_controls")),
    _cycles_between_controls(getParam<Real>("cycles_between_controls")),
    _num_controller_set(getParam<Real>("num_controller_set")),
    _name(getParam<std::string>("name"))
{
}

void
AddPeriodicControllers::act()
{
  _enable_start_start_time_index.resize(_enable_start.size());
  _enable_start_end_time_index.resize(_enable_start.size());

  _enable_during_start_time_index.resize(_enable_during.size());
  _enable_during_end_time_index.resize(_enable_during.size());

  _enable_end_start_time_index.resize(_enable_end.size());
  _enable_end_end_time_index.resize(_enable_end.size());

  _disable_start_start_time_index.resize(_disable_start.size());
  _disable_start_end_time_index.resize(_disable_start.size());

  _disable_during_start_time_index.resize(_disable_during.size());
  _disable_during_end_time_index.resize(_disable_during.size());

  _disable_end_start_time_index.resize(_disable_end.size());
  _disable_end_end_time_index.resize(_disable_end.size());

  std::string name_num;
  bool first_controller;

  if (_current_task == "add_control")
  {
    for (unsigned int i = 0; i < _num_controller_set; ++i)
    {
      // Setting up the start and end times for the TimePeriod Controller.
      // The end time is start time plus 0.0001 times the period
      for (MooseIndex(_enable_start) j = 0; j < _enable_start.size(); ++j)
      {
        _enable_start_start_time_index[j] = _start_time + (_cycles_between_controls + _cycles_per_controls) * _period * i;
        _enable_start_end_time_index[j] =
            _start_time + (_cycles_between_controls + _cycles_per_controls) * _period * i + (_period * 0.0001);
      }

      for (MooseIndex(_enable_during) j = 0; j < _enable_during.size(); ++j)
      {
        _enable_during_start_time_index[j] = _start_time + (_cycles_between_controls + _cycles_per_controls) * _period * i;
        _enable_during_end_time_index[j] =
            (_start_time + _period * _cycles_per_controls) + (_cycles_between_controls + _cycles_per_controls) * _period * i + (_period * 0.0001);
      }

      // If control cycles are back to back, then enable_start and enable_end times would be the
      // same, To avoid this, if cycles are back to back, then the enable_end starts at +
      // 0.0001*period.
      if (_cycles_between_controls == 1.0)
      {
        for (MooseIndex(_enable_end) j = 0; j < _enable_end.size(); ++j)
        {
          _enable_end_start_time_index[j] =
              (_start_time + _period * _cycles_per_controls) + (_cycles_between_controls + _cycles_per_controls) * _period * i + (_period * 0.0001);
          _enable_end_end_time_index[j] =
              (_start_time + _period * _cycles_per_controls) + (_cycles_between_controls + _cycles_per_controls) * _period * i + (_period * 0.0002);
        }
      }
      else
      {
        for (MooseIndex(_enable_end) j = 0; j < _enable_end.size(); ++j)
        {
          _enable_end_start_time_index[j] =
              (_start_time + _period * _cycles_per_controls) + (_cycles_between_controls + _cycles_per_controls) * _period * i;
          _enable_end_end_time_index[j] =
              (_start_time + _period * _cycles_per_controls) + (_cycles_between_controls + _cycles_per_controls) * _period * i + (_period * 0.0001);
        }
      }

      for (MooseIndex(_disable_start) j = 0; j < _disable_start.size(); ++j)
      {
        _disable_start_start_time_index[j] = _start_time + (_cycles_between_controls + _cycles_per_controls) * _period * i;
        _disable_start_end_time_index[j] =
            _start_time + (_cycles_between_controls + _cycles_per_controls) * _period * i + (_period * 0.0001);
      }

      for (MooseIndex(_disable_during) j = 0; j < _disable_during.size(); ++j)
      {
        _disable_during_start_time_index[j] = _start_time + (_cycles_between_controls + _cycles_per_controls) * _period * i;
        _disable_during_end_time_index[j] =
            (_start_time + _period * _cycles_per_controls) + (_cycles_between_controls + _cycles_per_controls) * _period * i + (_period * 0.0001);
      }

      // If control cycles are back to back, then disable_start and disable_end times would be the
      // same, To avoid this, if cycles are back to back, then the disable_end starts at +
      // 0.0001*period
      if (_cycles_between_controls == 1.0)
      {
        for (MooseIndex(_disable_end) j = 0; j < _disable_end.size(); ++j)
        {
          _disable_end_start_time_index[j] =
              (_start_time + _period * _cycles_per_controls) + (_cycles_between_controls + _cycles_per_controls) * _period * i + (_period * 0.0001);
          _disable_end_end_time_index[j] =
              (_start_time + _period * _cycles_per_controls) + (_cycles_between_controls + _cycles_per_controls) * _period * i + (_period * 0.0002);
        }
      }
      else
      {
        for (MooseIndex(_disable_end) j = 0; j < _disable_end.size(); ++j)
        {
          _disable_end_start_time_index[j] =
              (_start_time + _period * _cycles_per_controls) + (_cycles_between_controls + _cycles_per_controls) * _period * i;
          _disable_end_end_time_index[j] =
              (_start_time + _period * _cycles_per_controls) + (_cycles_between_controls + _cycles_per_controls) * _period * i + (_period * 0.0001);
        }
      }

      // Adding the multiple TimePeriod controllers
      if (_enable_start.size() > 0)
      {
        name_num = "Enable_Begin_" + std::to_string(i);

        if (i == 0)
        {
          first_controller = true;
        }
        else
        {
          first_controller = false;
        }

        AddTimePeriod("enable_objects",
                      _enable_start,
                      _enable_start_start_time_index,
                      _enable_start_end_time_index,
                      name_num,
                      first_controller);
      }

      if (_enable_during.size() > 0)
      {
        name_num = "Enable_During_" + std::to_string(i);

        if (i == 0)
        {
          first_controller = true;
        }
        else
        {
          first_controller = false;
        }

        AddTimePeriod("enable_objects",
                      _enable_during,
                      _enable_during_start_time_index,
                      _enable_during_end_time_index,
                      name_num,
                      first_controller);
      }

      if (_enable_end.size() > 0)
      {
        name_num = "Enable_End_" + std::to_string(i);

        if (i == 0)
        {
          first_controller = true;
        }
        else
        {
          first_controller = false;
        }

        AddTimePeriod("enable_objects",
                      _enable_end,
                      _enable_end_start_time_index,
                      _enable_end_end_time_index,
                      name_num,
                      first_controller);
      }

      if (_disable_start.size() > 0)
      {
        name_num = "Disable_Begin_" + std::to_string(i);

        if (i == 0)
        {
          first_controller = true;
        }
        else
        {
          first_controller = false;
        }

        AddTimePeriod("disable_objects",
                      _disable_start,
                      _disable_start_start_time_index,
                      _disable_start_end_time_index,
                      name_num,
                      first_controller);
      }

      if (_disable_during.size() > 0)
      {
        name_num = "Disable_During_" + std::to_string(i);

        if (i == 0)
        {
          first_controller = true;
        }
        else
        {
          first_controller = false;
        }

        AddTimePeriod("disable_objects",
                      _disable_during,
                      _disable_during_start_time_index,
                      _disable_during_end_time_index,
                      name_num,
                      first_controller);
      }

      if (_disable_end.size() > 0)
      {
        name_num = "Disable_End_" + std::to_string(i);

        if (i == 0)
        {
          first_controller = true;
        }
        else
        {
          first_controller = false;
        }

        AddTimePeriod("disable_objects",
                      _disable_end,
                      _disable_end_start_time_index,
                      _disable_end_end_time_index,
                      name_num,
                      first_controller);
      }
    }
  }
}

void
AddPeriodicControllers::AddTimePeriod(const std::string & enableORdisable,
                                      const std::vector<std::string> & objects,
                                      const std::vector<Real> & start_times,
                                      const std::vector<Real> & end_times,
                                      const std::string & name_num,
                                      const bool & first_controller)
{
  InputParameters params = _factory.getValidParams("TimePeriod");
  params.set<std::vector<std::string>>(enableORdisable) = objects;
  params.set<std::vector<Real>>("start_time") = start_times;
  params.set<std::vector<Real>>("end_time") = end_times;
  params.set<ExecFlagEnum>("execute_on", true) = {EXEC_INITIAL, EXEC_TIMESTEP_BEGIN};
  params.set<bool>("reverse_on_false") = first_controller;
  params.set<bool>("set_sync_times") = true;
  std::shared_ptr<Control> control =
      _factory.create<Control>("TimePeriod", _name + name_num, params);
  _problem->getControlWarehouse().addObject(control);
}
