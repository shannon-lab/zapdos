//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef LYMBEROPOULOSELECTRONBC_H
#define LYMBEROPOULOSELECTRONBC_H

#include "IntegratedBC.h"

class LymberopoulosElectronBC;

template <>
InputParameters validParams<LymberopoulosElectronBC>();

class LymberopoulosElectronBC : public IntegratedBC
{
public:
  LymberopoulosElectronBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  Real _r_units;
  Real _ks;
  Real _gamma;

  // Coupled variables

  const VariableGradient & _grad_potential;
  unsigned int _potential_id;
  const VariableValue & _Arp;
  const VariableGradient & _grad_Arp;
  unsigned int _Arp_id;

  const MaterialProperty<Real> & _muion;
  const MaterialProperty<Real> & _diffion;
  Real _sign;
};

#endif // LymberopoulosElectronBC_H
