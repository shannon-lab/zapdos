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
#include "ArgonConstTD.h"

template<>
InputParameters validParams<ArgonConstTD>()
{
  InputParameters params = validParams<Material>();

  params.addParam<Real>("user_relative_permittivity", 1.0, "Multiplies the permittivity of free space.");
  params.addParam<bool>("townsend",false,"Whether to use the townsend formulation for the ionization term.");
  params.addCoupledVar("potential", "The potential for calculating the electron velocity");
  params.addCoupledVar("em", "Species concentration needed to calculate the poisson source");
  params.addCoupledVar("Te", "The electron temperature.");
  params.addCoupledVar("ip", "The ion density.");
  return params;
}


ArgonConstTD::ArgonConstTD(const InputParameters & parameters) :
    Material(parameters),
    _townsend(getParam<bool>("townsend")),

  _muem(declareProperty<Real>("muem")),
    _diffem(declareProperty<Real>("diffem")),
    _muip(declareProperty<Real>("muip")),
    _diffip(declareProperty<Real>("diffip")),
    _rate_coeff_ion(declareProperty<Real>("rate_coeff_ion")),
    _Eiz(declareProperty<Real>("Eiz")),
    _Ar(declareProperty<Real>("Ar")),
    _muel(declareProperty<Real>("muel")),
    _diffel(declareProperty<Real>("diffel")),
    _rate_coeff_elastic(declareProperty<Real>("rate_coeff_elastic")),
    _mem(declareProperty<Real>("mem")),
  _mip(declareProperty<Real>("mip")),
  _se_coeff(declareProperty<Real>("se_coeff")),
  _ElectronTotalFluxMag(declareProperty<Real>("ElectronTotalFluxMag")),
  _ElectronTotalFluxMagSizeForm(declareProperty<Real>("ElectronTotalFluxMagSizeForm")),
  _ElectronTotalFlux(declareProperty<Real>("ElectronTotalFlux")),
  _ElectronAdvectiveFlux(declareProperty<Real>("ElectronAdvectiveFlux")),
  _ElectronDiffusiveFlux(declareProperty<Real>("ElectronDiffusiveFlux")),
  _IonTotalFlux(declareProperty<Real>("IonTotalFlux")),
  _IonAdvectiveFlux(declareProperty<Real>("IonAdvectiveFlux")),
  _IonDiffusiveFlux(declareProperty<Real>("IonDiffusiveFlux")),
  _EField(declareProperty<Real>("EField")),
  _Source_term(declareProperty<Real>("Source_term")),
  _Source_term_coeff(declareProperty<Real>("Source_term_coeff")),
  _e(declareProperty<Real>("e")),
  _eps(declareProperty<Real>("eps")),
  _Tem_lfa(declareProperty<Real>("Tem_lfa")),
  _Tip_lfa(declareProperty<Real>("Tip_lfa")),
  _k_boltz(declareProperty<Real>("k_boltz")),
  _vthermal_em(declareProperty<Real>("vthermal_em")),
  _vthermal_ip(declareProperty<Real>("vthermal_ip")),
  _iz_coeff_efield_a(declareProperty<Real>("iz_coeff_efield_a")),
  _iz_coeff_efield_b(declareProperty<Real>("iz_coeff_efield_b")),
  _iz_coeff_efield_c(declareProperty<Real>("iz_coeff_efield_c")),
  _iz_coeff_energy_a(declareProperty<Real>("iz_coeff_energy_a")),
  _iz_coeff_energy_b(declareProperty<Real>("iz_coeff_energy_b")),
  _iz_coeff_energy_c(declareProperty<Real>("iz_coeff_energy_c")),
  _N_A(declareProperty<Real>("N_A")),

  _grad_potential(isCoupled("potential") ? coupledGradient("potential") : _grad_zero),
  _em(isCoupled("em") ? coupledValue("em") : _zero),
  _ip(isCoupled("ip") ? coupledValue("ip") : _zero),
  _grad_em(isCoupled("em") ? coupledGradient("em") : _grad_zero),
  _grad_ip(isCoupled("ip") ? coupledGradient("ip") : _grad_zero)

{
}

void
ArgonConstTD::computeQpProperties()
{  
  // From bolos at atmospheric pressure and an EField of 2e5 V/m
  _muem[_qp] = 0.0352103411399;
  _diffem[_qp] = 0.297951680159;

  // Crude assumption: 100x less than electrons
  _muip[_qp] = _muem[_qp]/100.0;
  _diffip[_qp] = _diffem[_qp]/100.0;

  // From curve fitting with bolos
  _iz_coeff_efield_a[_qp] = 1.43171672e-1;
  _iz_coeff_efield_b[_qp] = 9.05925536e-1;
  _iz_coeff_efield_c[_qp] = 3.04958892e+6;

  if (_townsend) {
    _iz_coeff_energy_a[_qp] = 1.52165930e+8;
    _iz_coeff_energy_b[_qp] = -2.87277596e-1;
    _iz_coeff_energy_c[_qp] = 5.51972192e+1;
  }
  else {
    _iz_coeff_energy_a[_qp] = 1.43878529e-11;
    _iz_coeff_energy_b[_qp] = -2.70610234e-1;
    _iz_coeff_energy_c[_qp] = 7.64727794e+1;
  }

  _N_A[_qp] = 6.02e23;
  _Ar[_qp] = 1.01e5/(300*1.38e-23);
  _Eiz[_qp] = 15.76;

  _muel[_qp] = 5.0/3.0*_muem[_qp];
  _diffel[_qp] = 5.0/3.0*_diffem[_qp];
  _rate_coeff_elastic[_qp] = 1e-13;
  _mem[_qp] = 9.11e-31;
  _mip[_qp] = 40.0*1.66e-27;
  _se_coeff[_qp] = 0.1;
  _e[_qp] = 1.6e-19;
  _eps[_qp] = 8.85e-12;
  // _Tem_lfa[_qp] = 1.0; // Volts
  // _Tip_lfa[_qp] = 300; // Kelvin
  _k_boltz[_qp] = 1.38e-23;
  // _vthermal_em[_qp] = 1.6*sqrt(_e[_qp]*_Tem_lfa[_qp]/_mem[_qp]);
  // _vthermal_ip[_qp] = 1.6*sqrt(_k_boltz[_qp]*_Tip_lfa[_qp]/_mip[_qp]);

  _ElectronTotalFluxMag[_qp] = std::sqrt((-_muem[_qp]*-_grad_potential[_qp]*std::exp(_em[_qp])-_diffem[_qp]*std::exp(_em[_qp])*_grad_em[_qp])*(-_muem[_qp]*-_grad_potential[_qp]*std::exp(_em[_qp])-_diffem[_qp]*std::exp(_em[_qp])*_grad_em[_qp]));
  _ElectronTotalFluxMagSizeForm[_qp] = (-_muem[_qp]*-_grad_potential[_qp]*std::exp(_em[_qp])-_diffem[_qp]*std::exp(_em[_qp])*_grad_em[_qp]).size();
  _ElectronTotalFlux[_qp] = -_muem[_qp]*-_grad_potential[_qp](0)*std::exp(_em[_qp])-_diffem[_qp]*std::exp(_em[_qp])*_grad_em[_qp](0);
  _ElectronAdvectiveFlux[_qp] = -_muem[_qp]*-_grad_potential[_qp](0)*std::exp(_em[_qp]);
  _ElectronDiffusiveFlux[_qp] = -_diffem[_qp]*std::exp(_em[_qp])*_grad_em[_qp](0);
  _IonTotalFlux[_qp] = -_muip[_qp]*-_grad_potential[_qp](0)*std::exp(_ip[_qp])-_diffip[_qp]*std::exp(_ip[_qp])*_grad_ip[_qp](0);
  _IonAdvectiveFlux[_qp] = -_muip[_qp]*-_grad_potential[_qp](0)*std::exp(_ip[_qp]);
  _IonDiffusiveFlux[_qp] = -_diffip[_qp]*std::exp(_ip[_qp])*_grad_ip[_qp](0);
  _EField[_qp] = -_grad_potential[_qp](0);
  _Source_term[_qp] = _rate_coeff_ion[_qp]*std::exp(-_Eiz[_qp]/_grad_potential[_qp].size())*(-_muem[_qp]*-_grad_potential[_qp]*std::exp(_em[_qp])-_diffem[_qp]*std::exp(_em[_qp])*_grad_em[_qp]).size();
  _Source_term_coeff[_qp] = _rate_coeff_ion[_qp]*std::exp(-_Eiz[_qp]/_grad_potential[_qp].size());
}
