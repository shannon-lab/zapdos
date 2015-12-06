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
#include "JacMat.h"

template<>
InputParameters validParams<JacMat>()
{
  InputParameters params = validParams<Material>();
  return params;
}


JacMat::JacMat(const InputParameters & parameters) :
    Material(parameters),
    _muu(declareProperty<Real>("muu")),
    _muv(declareProperty<Real>("muv")),
    _sgnu(declareProperty<Real>("sgnu")),
    _sgnv(declareProperty<Real>("sgnv")),
    _diffu(declareProperty<Real>("diffu")),
    _diffem(declareProperty<Real>("diffem")),
    _muem(declareProperty<Real>("muem")),
    _iz_coeff_efield_a(declareProperty<Real>("iz_coeff_efield_a")),
    _iz_coeff_efield_b(declareProperty<Real>("iz_coeff_efield_b")),
    _iz_coeff_efield_c(declareProperty<Real>("iz_coeff_efield_c")),
    _ku(declareProperty<Real>("ku")),
  _kuu(declareProperty<Real>("kuu")),
  _N_A(declareProperty<Real>("N_A")),
  _e(declareProperty<Real>("e")),
    _kv(declareProperty<Real>("kv")),
  _kvv(declareProperty<Real>("kvv")),
  _diffu1(declareProperty<Real>("diffu1")),
  _diffu2(declareProperty<Real>("diffu2")),
  _se_coeff(declareProperty<Real>("se_coeff")),
  _eps(declareProperty<Real>("eps")),
  _mem(declareProperty<Real>("mem"))

{
}

void
JacMat::computeQpProperties()
{
  _muu[_qp] = 1.1;
  _muv[_qp] = 1.1;
  _sgnu[_qp] = 1.;
  _sgnv[_qp] = 1.;
  _diffu[_qp] = 1.1;
  _diffem[_qp] = 1.1;
  _muem[_qp] = 1.1;
  _iz_coeff_efield_a[_qp] = 1.1;
  _iz_coeff_efield_b[_qp] = 1.1;
  _iz_coeff_efield_c[_qp] = 1.1;
  _ku[_qp] = 1.1;
  _kuu[_qp] = 1.1;
  _N_A[_qp] = 1.1;
  _e[_qp] = 1.1;
  _kv[_qp] = 1.1;
  _kvv[_qp] = 1.1;
  _diffu1[_qp] = 1.1;
  _diffu2[_qp] = 1.1;
  _se_coeff[_qp] = 0.1;
  _eps[_qp] = 1.1;
  _mem[_qp] = 1.1;
}
