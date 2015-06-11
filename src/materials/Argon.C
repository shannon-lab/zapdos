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
#include "Argon.h"

template<>
InputParameters validParams<Argon>()
{
  InputParameters params = validParams<Material>();

  params.addParam<Real>("user_relative_permittivity", 1.0, "Multiplies the permittivity of free space.");
  params.addCoupledVar("potential", "The potential for calculating the electron velocity");
  params.addCoupledVar("em", "Species concentration needed to calculate the poisson source");
  params.addCoupledVar("mean_electron_energy", "The mean electron energy.");
  return params;
}


Argon::Argon(const std::string & name, InputParameters parameters) :
    Material(name, parameters),

    // Input parameters

    _user_relative_permittivity(getParam<Real>("user_relative_permittivity")),

    // Coupled variables
    
    _grad_potential(isCoupled("potential") ? coupledGradient("potential") : _grad_zero),
    _em(isCoupled("em") ? coupledValue("em") : _zero),
    _grad_em(isCoupled("em") ? coupledGradient("em") : _grad_zero),
    _mean_electron_energy(isCoupled("mean_electron_energy") ? coupledValue("mean_electron_energy") : _zero),

// Declare material properties.  This returns references that we
// hold onto as member variables

  _N_A(declareProperty<Real>("N_A")),
  _eps_r(declareProperty<Real>("eps_r")),
  _eps_0(declareProperty<Real>("eps_0")),
  _e(declareProperty<Real>("e")),
  _D_em(declareProperty<Real>("D_em")),
  _zem(declareProperty<Real>("zem")),
  _muem(declareProperty<Real>("muem")),
  _EFieldAdvectionCoeff_em(declareProperty<Real>("EFieldAdvectionCoeff_em")),
  _EField(declareProperty<RealVectorValue>("EField")),
  _gamma_em(declareProperty<RealVectorValue>("gamma_em")),
  _k_boltz(declareProperty<Real>("k_boltz")),
  _T_em(declareProperty<Real>("T_em")),
  _m_em(declareProperty<Real>("m_em")),
  _v_thermal_em(declareProperty<Real>("v_thermal_em")),
  _advection_velocity_em(declareProperty<RealVectorValue>("advection_velocity_em")),
  _mu_mean_electron_energy(declareProperty<Real>("mu_mean_electron_energy")),
  _EFieldAdvectionCoeff_mean_electron_energy(declareProperty<Real>("EFieldAdvectionCoeff_mean_electron_energy")),
  _D_mean_electron_energy(declareProperty<Real>("D_mean_electron_energy"))
{
}

void
Argon::computeQpProperties()
{  
  _N_A[_qp] = 6.02e23;
  _eps_r[_qp]   = _user_relative_permittivity;
  _eps_0[_qp]   = 8.85e-12;
  _e[_qp]	= 1.6e-19;  // coulombic charge
  _zem[_qp] = -1.0;
  _muem[_qp] = 380.0/(1.0e4); // Ebert article
  _EFieldAdvectionCoeff_em[_qp] = _muem[_qp]*-1.0;
  _T_em[_qp] = _mean_electron_energy[_qp]*2.0/(3.0*_em[_qp]);
  _D_em[_qp] = _muem[_qp]*_T_em[_qp];
  _EField[_qp] = -_grad_potential[_qp];
  _gamma_em[_qp] = _muem[_qp]*_EField[_qp]*_em[_qp]-_D_em[_qp]*_grad_em[_qp];
  _k_boltz[_qp] = 1.38e-23;
  _m_em[_qp] = 9.11e-31;
  _v_thermal_em[_qp] = 1.6*std::sqrt(_k_boltz[_qp]*_T_em[_qp]/_m_em[_qp]);
  _advection_velocity_em[_qp] = _muem[_qp]*_EField[_qp];
  _mu_mean_electron_energy[_qp] = 5.0/3.0*_muem[_qp];
  _EFieldAdvectionCoeff_mean_electron_energy[_qp] = _mu_mean_electron_energy[_qp]*-1.0;
  _D_mean_electron_energy[_qp] = _mu_mean_electron_energy[_qp]*_T_em[_qp];
}
