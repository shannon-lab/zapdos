//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "TM0Cylindrical.h"

registerMooseObject("ZapdosApp", TM0Cylindrical);

InputParameters
TM0Cylindrical::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addRequiredParam<Real>("f", "The drive frequency.");
  params.addClassDescription(
      "The axisymmetric wave equation for the azimuth component of the magnetizing field.");
  return params;
}

TM0Cylindrical::TM0Cylindrical(const InputParameters & parameters)
  : ADKernel(parameters),

    _omega(2. * libMesh::pi * getParam<Real>("f")),
    _eps_r(getADMaterialProperty<Real>("eps_r")),
    _mu0(4. * libMesh::pi * 1e-7),
    _eps0(8.85e-12)
{
}

ADReal
TM0Cylindrical::computeQpResidual()
{
  return -_grad_test[_i][_qp] * _grad_u[_qp] -
         _test[_i][_qp] * _u[_qp] / std::pow(_q_point[_qp](0), 2) +
         _test[_i][_qp] * std::pow(_omega, 2) * _mu0 * _eps_r[_qp] * _eps0 * _u[_qp];
}
