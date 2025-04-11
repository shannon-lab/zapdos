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

/**
 * This class allows us to have a section of the input file like the
 * following which automatically adds variables, kernels, aux kernels, bcs
 * for setting up the drift-diffusion equation for multiple plasma species
 * and automatically adds the Poisson's equation for electrostatic cases.
 *
 * [DriftDiffusionAction]
 *   [Plasma]
 *   []
 * []
 */
class AddDriftDiffusionAction : public Action
{
public:
  AddDriftDiffusionAction(const InputParameters & params);

  static InputParameters validParams();

  virtual void act();

protected:
  /**
   *  Helper function that supplies the potentials charge sources
   *  when the electrostatic field solver is used
   *  @param field_name The name of the electric field
   *  @param charged_particle_name The name of the charge particle density
   *  @param field_solver The state of the field solver (either: ELECTROSTATIC or ELECTROMAGNETIC)
   */
  virtual void addChargeSourceKernels(const std::string & field_name,
                                      const std::string & charged_particle_name,
                                      const MooseEnum & field_solver);

  /**
   *  Helper function that supplies the Kernels for drift-diffusion for the electrons,
   *  energy independent charged particles, neutral particles, and
   *  electron mean energy density
   *  @param name The name of the density variable
   *  @param field_name The name of the electric field
   *  @param Using_offset True if the LogStabilizationMoles Kernel being used
   *  @param charged True if the density variable has a charge
   *  @param energy True if the density is a mean energy density variable
   */
  virtual void addADKernels(const std::string & name,
                            const std::string & field_name,
                            const bool & Using_offset,
                            const bool & charged,
                            const bool & energy);

  /**
   *  Helper function that supplies the Aux kernels to convert scaled position units
   *  when the user sets position_units to non-unity value
   *  @param position_name The name of the position variable in the format of {component +
   * "_position" + block}
   *  @param component The spatial component defined as x=0, y=1, and z=2
   */
  virtual void addPosition(const std::string & position_name, const int & component);

  /**
   *  Helper function that supplies the Aux kernels to convert densities from logarithmic form
   *  @param particle_name The name of the density variable
   */
  virtual void addDensityLog(const std::string & particle_name);

  /**
   *  Helper function that supplies the Aux kernels for current
   *  @param particle_name The name of the charge density variable
   *  @param field_property_name The name of the electric field as a material property
   */
  virtual void addCurrent(const std::string & particle_name,
                          const std::string & field_property_name);

  /**
   *  Helper function that supplies the Aux kernels for the electric field
   *  @param Efield_name The name of the electric field variable in the format of {"Efield" +
   * component + block}
   *  @param field_property_name The name of the electric field as a material property
   *  @param component The spatial component defined as x=0, y=1, and z=2
   */
  virtual void addEfield(const std::string & Efield_name,
                         const std::string & field_property_name,
                         const int & component);
  /**
   *  Helper function that supplies ...
   *  @param field_name The name of the electric field
   *  @param field_property_name The name of the electric field as a material property
   *  @param field_solver The state of the field solver (either: ELECTROSTATIC or ELECTROMAGNETIC)
   *  @param effective_field True if the field is the effective electric field
   */
  virtual void addFieldSolverMaterial(const std::string & field_name,
                                      const std::string & field_property_name,
                                      const MooseEnum & field_solver,
                                      const bool & effective_field);
};
