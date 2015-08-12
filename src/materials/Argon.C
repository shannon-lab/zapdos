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
  params.addCoupledVar("Te", "The electron temperature.");
  params.addCoupledVar("Arp", "The argon ion density.");
  return params;
}


Argon::Argon(const InputParameters & parameters) :
    Material(parameters),

    // Input parameters

    _user_relative_permittivity(getParam<Real>("user_relative_permittivity")),

    // Coupled variables
    
    _grad_potential(isCoupled("potential") ? coupledGradient("potential") : _grad_zero),
    _em(isCoupled("em") ? coupledValue("em") : _zero),
    _grad_em(isCoupled("em") ? coupledGradient("em") : _grad_zero),
    _Te(isCoupled("Te") ? coupledValue("Te") : _zero),
    _Arp(isCoupled("Arp") ? coupledValue("Arp") : _zero),
    _grad_Arp(isCoupled("Arp") ? coupledGradient("Arp") : _grad_zero),

// Declare material properties.  This returns references that we
// hold onto as member variables

    _tc(declareProperty<Real>("tc")),
  _rc(declareProperty<Real>("rc")),
  _emc(declareProperty<Real>("emc")),
  _Arpc(declareProperty<Real>("Arpc")),
  _Tec(declareProperty<Real>("Tec")),
  _Vc(declareProperty<Real>("Vc")),
  _eps_r(declareProperty<Real>("eps_r")),
  _eps_0(declareProperty<Real>("eps_0")),
  _permittivity(declareProperty<Real>("permittivity")),
  _e(declareProperty<Real>("e")),
  _k_boltz(declareProperty<Real>("k_boltz")),
  _muem(declareProperty<Real>("muem")),
  _T_gas(declareProperty<Real>("T_gas")),
  _pressure(declareProperty<Real>("pressure")),
  _Ar(declareProperty<Real>("Ar")),
  _k1_const(declareProperty<Real>("k1_const")),
  _k4_const(declareProperty<Real>("k4_const")),
  _muAr(declareProperty<Real>("muAr")),
  _muArp(declareProperty<Real>("muArp")),
  _mem(declareProperty<Real>("mem")),
  _mAr(declareProperty<Real>("mAr")),
  _mArp(declareProperty<Real>("mArp")),
  _muel(declareProperty<Real>("muel"))
/*  _k6(declareProperty<Real>("k6")),
  _k7(declareProperty<Real>("k7")),
  _R_const(declareProperty<Real>("R_const")),
  _el_energy_gain_excitation(declareProperty<Real>("el_energy_gain_excitation")),
  _el_energy_gain_deexcitation(declareProperty<Real>("el_energy_gain_deexcitation")),
  _el_energy_gain_ionization(declareProperty<Real>("el_energy_gain_ionization")),
  _el_energy_gain_meta_ionization(declareProperty<Real>("el_energy_gain_meta_ionization")),
  _advective_ion_flux(declareProperty<RealVectorValue>("advective_ion_flux")),
  _diffusive_ion_flux(declareProperty<RealVectorValue>("diffusive_ion_flux")),
  _total_ion_flux(declareProperty<RealVectorValue>("total_ion_flux")),
  _advective_electron_flux(declareProperty<RealVectorValue>("advective_electron_flux")),
  _diffusive_electron_flux(declareProperty<RealVectorValue>("diffusive_electron_flux")),
  _total_electron_flux(declareProperty<RealVectorValue>("total_electron_flux")),
  _Electric_Field(declareProperty<RealVectorValue>("Electric_Field"))*/
{
}

void
Argon::computeQpProperties()
{  
  _tc[_qp] = .001;
  _rc[_qp] = .01;
  _emc[_qp] = 1e18;
  _Arpc[_qp] = 1e18;
  _Tec[_qp] = 1;
  _Vc[_qp] = 1000;
  _eps_r[_qp]   = _user_relative_permittivity;
  _eps_0[_qp]   = 8.85e-12;
  _permittivity[_qp] = _eps_r[_qp]*_eps_0[_qp];
  _e[_qp]	= 1.6e-19;  // coulombic charge
  _k_boltz[_qp] = 1.38e-23; 
  _muem[_qp] = 380.0/(1.0e4); // Ebert article. Units of m^2/(V*second)
  _T_gas[_qp] = 300; // Kelvin
  _pressure[_qp] = 1.01e5; // Pascals
  _Ar[_qp] = _pressure[_qp]/(_T_gas[_qp]*_k_boltz[_qp]);
  _k1_const[_qp] = 1e-13;
  _k4_const[_qp] = 5e-14;
  _muAr[_qp] = 1.54/(1.0e4); // Physics Letter A. Volume 25, Issue 5, September 11, 1967, Pgs 407-408. Units of m^2/(V*second)
  _muArp[_qp] = _muAr[_qp];
  _mem[_qp] = 9.11e-31;
  _mAr[_qp] = 40.0*1.66e-27;
  _mArp[_qp] = _mAr[_qp];
  _muel[_qp] = 5.0/3.0*_muem[_qp];
  /*  _k6[_qp] = 1807.0/_N_A[_qp]; // m^3/s
  _k7[_qp] = 2.3e7/_N_A[_qp]; // m^3/s
  _el_energy_gain_excitation[_qp] = -11.5; // eV
  _el_energy_gain_deexcitation[_qp] = 11.5; // eV
  _el_energy_gain_ionization[_qp] = -15.8; // eV
  _el_energy_gain_meta_ionization[_qp] = -4.24; // eV
  _advective_ion_flux[_qp] = _muArp[_qp]*-_grad_potential[_qp]*_Arp[_qp];
  _diffusive_ion_flux[_qp] = -_D_Arp[_qp]*_grad_Arp[_qp];
  _total_ion_flux[_qp] = _advective_ion_flux[_qp] + _diffusive_ion_flux[_qp];
  _advective_electron_flux[_qp] = -_muem[_qp]*-_grad_potential[_qp]*_em[_qp];
  _diffusive_electron_flux[_qp] = -_muem[_qp]*_Te[_qp]*_grad_em[_qp];
  _total_electron_flux[_qp] = _advective_electron_flux[_qp] + _diffusive_electron_flux[_qp];  
  _Electric_Field[_qp] = -_grad_potential[_qp]; */
}
