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


Argon::Argon(const std::string & name, InputParameters parameters) :
    Material(name, parameters),

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
  _mip(declareProperty<Real>("mip"))
{}

void
Argon::computeQpProperties()
{  
  _muem[_qp] = 4.32e-2;
  _diffem[_qp] = 3.24e-1;
  _muip[_qp] = _muem[_qp]/100;
  _diffip[_qp] = _diffem[_qp]/100;
  _rate_coeff_ion[_qp] = 5e-14;
  _Eiz[_qp] = 12.78;
  _Ar[_qp] = 1.01e5/(300*1.38e-23);
  _muel[_qp] = 5.0/3.0*_muem[_qp];
  _diffel[_qp] = 5.0/3.0*_diffem[_qp];
  _rate_coeff_elastic[_qp] = 1e-13;
  _mem[_qp] = 9.11e-31;
  _mip[_qp] = 40.0*1.66e-27;
}
