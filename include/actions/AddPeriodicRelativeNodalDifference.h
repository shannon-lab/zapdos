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

/*
 *  This Action automatically adds the necessary objects to calculate the relative
 *  periodic difference. Relative Difference will be outputted as a Postprocessor named:
 *  'var'_periodic_difference
 */
class AddPeriodicRelativeNodalDifference : public Action
{
public:
  AddPeriodicRelativeNodalDifference(const InputParameters & params);

  static InputParameters validParams();

  virtual void act();

protected:
  /**
   *  Function for setting ICs for the previous and sudo previous solutions
   *  @param variable_name The name of the variable
   *  @param initial The inital value of the variable
   */
  virtual void addPerviousSolutionsIC(const std::string & variable_name, const Real & initial);
  /**
   *  Function for setting AuxKernels for the previous and sudo previous solutions
   *  @param variable_name The name of the auxvariable to stores the previous cycle solution
   *  @param var_old_name The name of the variable storing the solution at the beginning of the time
   * step
   */
  virtual void addPerviousSolutionsKernels(const std::string & variable_name,
                                           const std::string & var_old_name);
  /**
   *  Function for setting AuxKernels to normalize solutions
   *  @param variable_name The name of the auxvariable to stores normalization value
   *  @param source The name of the variable to be normalizated
   *  @param averaged The name of the postprocessor that calculates the spatial average
   *  @param log True if the source is in a logarithmic form
   */
  virtual void addNormalizationKernels(const std::string & variable_name,
                                       const std::string & source,
                                       const std::string & averaged,
                                       const bool & log);
  /**
   *  Function for setting Postprocessor to take to nodal average
   *  @param variable_name The name of the variable to be averaged
   *  @param log True if the variable is in a logarithmic form
   */
  virtual void addAverageNodalPP(const std::string & variable_name, const bool & log);
  /**
   *  Function for setting Postprocessor to take to average nodal difference
   *  @param variable_name The name of the variable that stores the current average
   *  @param var_old_name The name of the variable that stores the average from the previous cycle
   *  @param name The name of the variable that was averaged
   */
  virtual void addRelativePeriodicDiffPP(const std::string & variable_name,
                                         const std::string & var_old_name,
                                         const std::string & name);
  /**
   *  Function that adds a 'TimePeriod' controller to begin calculating the relative periodic
   * difference
   *  @param objects The name of objects that are either being enabled or disabled
   *  @param start_times The time values to start the controller
   *  @param end_times The time values to stop the controller
   *  @param name_num The current number of the controller for the naming of the controller object
   *  @param first_controller True if this is the first controller object being set
   */
  virtual void AddTimePeriod(const std::vector<std::string> & objects,
                             const std::vector<Real> & start_times,
                             const std::vector<Real> & end_times,
                             const std::string & name_num,
                             const bool & first_controller);

  /// The starting time to begin calculating the relative periodic difference
  Real _start_time;
  /// The period of the cycle
  Real _period;
  /// The number of cycles this object, PeriodicRelativeNodalDifference, is active
  Real _num_controller_set;

  /// The name of objects to enable at the start of the cycle
  std::vector<std::string> _enable_start;
  /// The name of objects to enable at the end of the cycle
  std::vector<std::string> _enable_end;

  /// The array that holds the start times for objects that are enable at the start of the cycle
  std::vector<Real> _enable_start_start_time_index;
  /// The array that holds the end times for objects that are enable at the start of the cycle
  std::vector<Real> _enable_start_end_time_index;
  /// The array that holds the start times for objects that are enable at the end of the cycle
  std::vector<Real> _enable_end_start_time_index;
  /// The array that holds the end times for objects that are enable at the end of the cycle
  std::vector<Real> _enable_end_end_time_index;
};
