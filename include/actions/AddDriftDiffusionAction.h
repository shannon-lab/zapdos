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

class AddDriftDiffusionAction;

template <>
InputParameters validParams<AddDriftDiffusionAction>();

class AddDriftDiffusionAction : public Action
{
public:
  AddDriftDiffusionAction(InputParameters params);

  virtual void act();

protected:
  virtual void addElectronKernels(const std::string & em_name,
                                  const std::string & potential_name,
                                  const std::string & mean_en_name,
                                  const bool & Using_offset);
  virtual void addChargedParticlesKernels(const std::string & ion_name,
                                          const std::string & potential_name,
                                          const bool & Using_offset);
  virtual void addNeutralParticlesKernels(const std::string & neutral_name,
                                          const bool & Using_offset);
  virtual void addMeanEnergyKernels(const std::string & em_name,
                                    const std::string & potential_name,
                                    const std::string & mean_en_name,
                                    const bool & Using_offset);
  virtual void addChargeSourceKernels(const std::string & potential_name,
                                      const std::string & charged_particle_name);
  virtual void addPosition(const std::string & position_name, const int & component);

  virtual void addDensityLog(const std::string & particle_name);
  virtual void addCurrent(const std::string & particle_name, const std::string & potential_name);
  virtual void addEfield(const std::string & Efield_name,
                         const std::string & potential_name,
                         const int & component);

  // virtual void addEEDFCoefficient(const unsigned & reaction_num);
};
