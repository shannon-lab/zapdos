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
  VariableValue & _mean_electron_energy;

  // Material properties
  
  MaterialProperty<Real> & _N_A;
  MaterialProperty<Real> & _eps_r;
  MaterialProperty<Real> & _eps_0;
  MaterialProperty<Real> & _e;
  MaterialProperty<Real> & _D_em;
  MaterialProperty<Real> & _zem;
  MaterialProperty<Real> & _muem;
  MaterialProperty<Real> & _EFieldAdvectionCoeff_em;
  MaterialProperty<RealVectorValue> & _EField;
  MaterialProperty<RealVectorValue> & _gamma_em;
  MaterialProperty<Real> & _k_boltz;
  MaterialProperty<Real> & _T_em;
  MaterialProperty<Real> & _m_em;
  MaterialProperty<Real> & _v_thermal_em;
  MaterialProperty<RealVectorValue> & _advection_velocity_em;
  MaterialProperty<Real> & _mu_mean_electron_energy;
  MaterialProperty<Real> & _EFieldAdvectionCoeff_mean_electron_energy;
  MaterialProperty<Real> & _D_mean_electron_energy;
};

#endif //ARGON_H
