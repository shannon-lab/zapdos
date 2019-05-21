//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef HPHIRADIALINTERFACE_H
#define HPHIRADIALINTERFACE_H

#include "InterfaceKernel.h"

// Forward Declarations
class HphiRadialInterface;

template <>
InputParameters validParams<HphiRadialInterface>();

/**
 * DG kernel for interfacing diffusion between two variables on adjacent blocks
 */
class HphiRadialInterface : public InterfaceKernel
{
public:
  HphiRadialInterface(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual(Moose::DGResidualType type);
  virtual Real computeQpJacobian(Moose::DGJacobianType type);

  const MaterialProperty<Real> & _eps_r_neighbor;
  const MaterialProperty<Real> & _eps_r;
};

#endif
