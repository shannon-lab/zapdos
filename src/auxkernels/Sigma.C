//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "Sigma.h"
#include "Assembly.h"

registerMooseObject("ZapdosApp", Sigma);

template <>
InputParameters
validParams<Sigma>()
{
  InputParameters params = validParams<AuxKernel>();

  params.addRequiredCoupledVar("n", "The density of the ions.");
  params.addRequiredCoupledVar("potential", "The potential");
  return params;
}

Sigma::Sigma(const InputParameters & parameters)
  : AuxKernel(parameters),
    _u_old(uOld()),
    _n(coupledValue("n")),
    _grad_potential(coupledGradient("potential"))
{
}

Real
Sigma::computeValue()
{
  return _u_old[_qp] + _dt * -_grad_potential[_qp] * _n[_qp] * _assembly.normals()[_qp];
}
