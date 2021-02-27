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

#include "ShapeSideUserObject.h"

class CurrentDensityShapeSideUserObject : public ShapeSideUserObject
{
public:
  CurrentDensityShapeSideUserObject(const InputParameters & parameters);

  static InputParameters validParams();

  virtual ~CurrentDensityShapeSideUserObject() {}

  virtual void initialize();
  virtual void execute();
  virtual void executeJacobian(unsigned int jvar);
  virtual void finalize();
  virtual void threadJoin(const UserObject & y);

  ///@{ custom UserObject interface functions
  const Real & getIntegral() const { return _integral; }
  const std::vector<Real> & getJacobian() const { return _jacobian_storage; }
  ///@}

protected:
  Real _integral;
  std::vector<Real> _jacobian_storage;

  const VariableValue & _em;
  unsigned int _em_id;
  const VariableGradient & _grad_em;
  const MooseVariable & _ip_var;
  const VariableValue & _ip;
  unsigned int _ip_id;
  const VariableGradient & _grad_ip;
  const VariableGradient & _grad_potential;
  unsigned int _potential_id;
  const VariableValue & _mean_en;
  unsigned int _mean_en_id;
  const ADMaterialProperty<Real> & _muip;
  const ADMaterialProperty<Real> & _diffip;
  const ADMaterialProperty<Real> & _muem;
  const ADMaterialProperty<Real> & _diffem;
  Real _e;
  bool _use_moles;
  Real _avogadro;
};
