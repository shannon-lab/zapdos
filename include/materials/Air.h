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
#ifndef AIR_H_
#define AIR_H_

#include "Material.h"

// A helper class from MOOSE that linear interpolates x,y data
#include "LinearInterpolation.h"

class Air;

template<>
InputParameters validParams<Air>();

/**
 * Material objects inherit from Material and override computeQpProperties.
 *
 * Their job is to declare properties for use by other objects in the
 * calculation such as Kernels and BoundaryConditions.
 */
class Air : public Material
{
public:
  Air(const InputParameters & parameters);

protected:
  /**
   * Necessary override.  This is where the values of the properties
   * are computed.
   */
  virtual void computeQpProperties();

  // Input parameters
  
  //  const Real & _velocity_multiplier;
  const Real & _user_relative_permittivity;
  //const Real & _ionization_multiplier;
  const Real & _user_potential_mult;
  const Real & _user_density_mult;
//  const Real & _user_diffusivity;
//  const Real & _delta;
//  const bool & _consistent;
//  bool  _coupling;

  // Coupled Variables

  VariableGradient & _grad_potential;
  VariableValue & _em;
  VariableValue & _ip;
  VariableGradient & _grad_em;
  VariableGradient & _grad_ip;

  // Functions
  
  //  Function & _velocity_function;

  // Material properties
  
//  MaterialProperty<Real> & _velocity_coeff;
//  MaterialProperty<Real> & _permittivity;
//  MaterialProperty<Real> & _coulomb_charge;
//  MaterialProperty<Real> & _ionization_coeff;
//  MaterialProperty<Real> & _ion_activation_energy;
  MaterialProperty<Real> & _potential_mult;
  MaterialProperty<Real> & _density_mult;
//  MaterialProperty<Real> & _peclet_num;
//  MaterialProperty<Real> & _alpha; 
//  MaterialProperty<RealVectorValue> & _velocity;
//  MaterialProperty<RealVectorValue> & _velocity_norm;
//  MaterialProperty<Real> & _diffusivity;
//  MaterialProperty<Real> & _tau;
  MaterialProperty<Real> & _N_A;
  MaterialProperty<Real> & _eps_r;
  MaterialProperty<Real> & _eps_0;
  MaterialProperty<Real> & _e;
  MaterialProperty<Real> & _Dem;
  MaterialProperty<Real> & _Dip;
  MaterialProperty<Real> & _zem;
  MaterialProperty<Real> & _zip;
  MaterialProperty<Real> & _muem;
  MaterialProperty<Real> & _muip;
  MaterialProperty<Real> & _alpha_0;
  MaterialProperty<Real> & _E_0;
  MaterialProperty<Real> & _s;
  MaterialProperty<Real> & _sem;
  MaterialProperty<Real> & _sip;
  MaterialProperty<Real> & _spotential;
  MaterialProperty<Real> & _Jac_em;
  MaterialProperty<Real> & _Jac_ip;
  MaterialProperty<Real> & _Jac_potential;
  MaterialProperty<RealVectorValue> & _EField;
  MaterialProperty<RealVectorValue> & _gamma_em;
  MaterialProperty<RealVectorValue> & _gamma_ip;
  MaterialProperty<Real> & _k_boltz;
  MaterialProperty<Real> & _T_em;
  MaterialProperty<Real> & _T_ip;
  MaterialProperty<Real> & _m_em;
  MaterialProperty<Real> & _m_ip;
  MaterialProperty<Real> & _v_thermal_em;
  MaterialProperty<Real> & _v_thermal_ip;
  MaterialProperty<RealVectorValue> & _advection_velocity_em;
  MaterialProperty<RealVectorValue> & _advection_velocity_ip;
  MaterialProperty<Real> & _h_size;
};

#endif //AIR_H
