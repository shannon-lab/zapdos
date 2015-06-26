/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/
#ifndef ARGON_H_
#define ARGON_H_

#include "Material.h"

class Argon;

template<>
InputParameters validParams<Argon>();

class Argon : public Material
{
public:
  Argon(const std::string & name, InputParameters parameters);

protected:
  virtual void computeQpProperties();

  // Input parameters
  
  const Real & _user_relative_permittivity;

  // Coupled Variables

  VariableGradient & _grad_potential;
  VariableValue & _em;
  VariableGradient & _grad_em;
  VariableValue & _Te;
  VariableValue & _Arp;
  VariableGradient & _grad_Arp;

  // Material properties
  MaterialProperty<Real> &  _N_A;
  MaterialProperty<Real> &  _eps_r;
  MaterialProperty<Real> &  _eps_0;
  MaterialProperty<Real> &  _permittivity;
  MaterialProperty<Real> &  _e;
  MaterialProperty<Real> &  _k_boltz;
  MaterialProperty<Real> &  _zem;
  MaterialProperty<Real> &  _muem;
  MaterialProperty<Real> &  _muAr;
  MaterialProperty<Real> &  _muArp;
  MaterialProperty<Real> &  _EFieldAdvectionCoeff_em;
  MaterialProperty<Real> &  _EFieldAdvectionCoeff_Arp;
  MaterialProperty<Real> &  _T_gas;
  MaterialProperty<Real> &  _D_Ar;
  MaterialProperty<Real> &  _D_Ars;
  MaterialProperty<Real> &  _D_Arp;
  MaterialProperty<Real> &  _m_em;
  MaterialProperty<Real> &  _mAr;
  MaterialProperty<Real> &  _mArp;
  MaterialProperty<Real> &  _muTe;
  MaterialProperty<Real> &  _EFieldAdvectionCoeff_Te;
  MaterialProperty<Real> &  _k6;
  MaterialProperty<Real> &  _k7;
  MaterialProperty<Real> &  _pressure;
  MaterialProperty<Real> &  _R_const;
  MaterialProperty<Real> &  _Ar;
  MaterialProperty<Real> &  _el_energy_gain_excitation;
  MaterialProperty<Real> &  _el_energy_gain_deexcitation;
  MaterialProperty<Real> &  _el_energy_gain_ionization;
  MaterialProperty<Real> &  _el_energy_gain_meta_ionization;
  MaterialProperty<RealVectorValue> &   _advective_ion_flux;
  MaterialProperty<RealVectorValue> &   _diffusive_ion_flux;
  MaterialProperty<RealVectorValue> &   _total_ion_flux;
  MaterialProperty<RealVectorValue> &   _advective_electron_flux;
  MaterialProperty<RealVectorValue> &   _diffusive_electron_flux;
  MaterialProperty<RealVectorValue> &   _total_electron_flux;
  MaterialProperty<RealVectorValue> &   _Electric_Field;
};

#endif //ARGON_H
