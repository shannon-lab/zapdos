//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef SakiyamaEnergySecondaryElectronBC_H
#define SakiyamaEnergySecondaryElectronBC_H

#include "IntegratedBC.h"

class SakiyamaEnergySecondaryElectronBC;

template <>
InputParameters validParams<SakiyamaEnergySecondaryElectronBC>();

class SakiyamaEnergySecondaryElectronBC : public IntegratedBC
{
public:
  SakiyamaEnergySecondaryElectronBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  Real _r_units;
  bool Te_dependent;

  // Coupled variables

  const VariableGradient & _grad_potential;
  unsigned int _potential_id;

  const VariableValue & _em;
  unsigned int _em_id;

  MooseVariable & _ip_var;
  const VariableValue & _ip;
  unsigned int _ip_id;

  const MaterialProperty<Real> & _sgnip;
  const MaterialProperty<Real> & _muip;
  Real _se_coeff;
  Real _user_se_energy;

  Real _a;
  Real _se_energy;
  Real _d_se_energy_d_u;
  Real _d_se_energy_d_em;
  RealVectorValue _ion_flux;
  RealVectorValue _d_ion_flux_d_potential;
  RealVectorValue _d_ion_flux_d_ip;
};

#endif // SakiyamaEnergySecondaryElectronBC_H
